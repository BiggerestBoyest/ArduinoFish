#include "Arduino.h"
#include "Fish.h"
#include "Player.h"
#include "GameManager.h"
#include "Sensors.h"
#include <List.hpp>
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#include <elapsedMillis.h>
//PINS FOR THINGIES, D2 = 4 DIGIT DISPLAY, D4 = VIBRATION MOTOR, 12C = RGB LCD, A1 = LIGHT SENSOR

#define FRAME_TIME 33
#define TIME_THRESHOLD 1
#define CLK 2
#define DIO 3
TM1637 tm1637(CLK, DIO);

GameManager* manager;
Sensors sensors;

unsigned long currentFrameTime;
elapsedMillis frameTimer;

//4Digit Display Variables
int microSecond = 100;
int internalSecond = 5; // unsigned char cant go below zero, bit of a fix to get around it
unsigned char second = 5; // the number displayed on the 4 digit display
unsigned char minute = 2;
int8_t TimeDisplay[] = {0x00, 0x00, 0x00, 0x00}; 
bool FLAG_MINUTE = false;
int FLAG_MINUTE_BLINK_AMOUNT = 8;

int timerDelay = 100;

bool CanUpdateTimer = true;

Player firstPlayer;
//Player secondPlayer;

void setup(){
  Serial.begin(9600);

  manager = new GameManager();

  //STEP ONE: CHECK IF SENSORS ARE READY
  sensors.SetupSensors();
    Serial.print("game true");

  SetupFourDigitDisplay();
   Timer1.attachInterrupt(TimingISR);
  // //STEP TWO: Setup players
  // //currently only one player

  firstPlayer.SetPlayerName("Jim");
   manager->players.add(firstPlayer);
   manager->currentPlayer = firstPlayer;
   manager->sensors = &sensors;
   manager->sensors->UpdateLCDScreen(firstPlayer.playerName,firstPlayer.currentPoints);
  // //Step 3 Start the game
    manager->StartGame();


}

void loop() { 

    while(!manager->GameStarted){} // doesn't start the game until the manager is ready

    if ((currentFrameTime = frameTimer) >= FRAME_TIME)
    {
      frameTimer = 0;

      if(manager->HasGameEnded) return; // if the game has ended. do not do the game logic loop


      // HIGH_PRIO_UPDATES

      if(sensors.GetCurrentSensorState(100))
      {
        manager->WaitForFish();
      } else 
      {
        manager->CheckIfCaughtFish();
      }


      // LOW_PRIO_UPDATES

      if ((currentFrameTime - FRAME_TIME) > TIME_THRESHOLD) //TIMER OVERRUN checks if the frame timer is one second behind, if so it might break the game
        Serial.print("Warning: Timing error has occured");
      
    }

      //UPDATE_WITH_INTERNAL_TIMER

      // if(CanUpdateTimer)
      // {
      //   UpdateTimer();
      //   tm1637.display(TimeDisplay);
      // } else if (minute == 0 && second == 0 && microSecond == 0)
      // {
      //   tm1637.point(POINT_OFF);    
      //   TimeDisplay[2] = 0x49;   
      //   TimeDisplay[3] = 0x6E;
      //   TimeDisplay[0] = 0x99;
      //   TimeDisplay[1] = 0x46;
      //   tm1637.display(TimeDisplay);
      //   manager->EndGame();
      // }
}

void UpdateTimer(){

    tm1637.point(POINT_ON);    //POINT_ON = 1,POINT_OFF = 0;
    second = internalSecond < 0 ? 0 : internalSecond;

    if (FLAG_MINUTE == true && FLAG_MINUTE_BLINK_AMOUNT > 0){
      TimeDisplay[2] = 0x00;
      TimeDisplay[3] = 0x00;
      TimeDisplay[0] = 0x6;
      TimeDisplay[1] = 0x00;
      delay(200);
      tm1637.clearDisplay();
      delay(200);
      CanUpdateTimer = false;
      FLAG_MINUTE_BLINK_AMOUNT--;
      return;

    }    
    //displays the time, if its less than a minute left, switch to show the microseconds
    TimeDisplay[2] = minute == 0 ? microSecond / 10 : second / 10 ;
    TimeDisplay[3] = minute == 0 ? microSecond % 10 : second % 10 ;
    TimeDisplay[0] = minute == 0 ? second / 10 : minute / 10;
    TimeDisplay[1] = minute == 0 ? second % 10 : minute % 10;
    CanUpdateTimer = false;
}


void SetupFourDigitDisplay(){
        Serial.println("setting up timer");

      tm1637.set(BRIGHT_TYPICAL);
      tm1637.init();
      Timer1.initialize(10000);//timing for 10ms

}

void TimingISR(){
    if(minute == 0 && second == 0 && microSecond == 0){
      CanUpdateTimer = false;
          return;
        }

    microSecond--;

    
    CanUpdateTimer = true;

    if (microSecond < 0){
      internalSecond--;
        if (internalSecond == 0 && minute == 1){
          FLAG_MINUTE = true;
        }
        if (internalSecond < 0){
          internalSecond--;
          minute--;
          internalSecond = 59;
        }
        microSecond = 100;
    }
}





