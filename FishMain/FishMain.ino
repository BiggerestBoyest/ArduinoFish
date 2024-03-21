#include "Arduino.h"
#include "Fish.h"
#include "Player.h"
#include "GameManager.h"
#include "Sensors.h"
#include <List.hpp>
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"


#define CLK 2
#define DIO 3
TM1637 tm1637(CLK, DIO);

GameManager manager;
Sensors sensors;

//4Digit Display Variables
int microSecond = 100;
int internalSecond = 5; // unsigned char cant go below zero, bit of a fix to get around it
unsigned char second = 5; // the number displayed on the 4 digit display
unsigned char minute = 2;
int8_t TimeDisplay[] = {0x00, 0x00, 0x00, 0x00}; 
bool FLAG_MINUTE = false;
int FLAG_MINUTE_BLINK_AMOUNT = 8;

bool CanUpdateTimer = true;

Player firstPlayer;
//Player secondPlayer;

void setup(){
  Serial.begin(9600);

  //STEP ONE: CHECK IF SENSORS ARE READY
  sensors.SetupSensors();
  SetupFourDigitDisplay();
  Timer1.attachInterrupt(TimingISR);

  //STEP TWO: Setup players
  //currently only one player
  manager.players.add(firstPlayer);
  manager.sensors = &sensors;
  Serial.print("test");

  //Step 3 Start the game
  manager.StartGame();


}

void loop() { 

    while(!manager.GameStarted){} // doesn't start the game until the manager is ready
    delay(1); // frame buffer
    if(sensors.GetCurrentSensorState(75)){
      manager.WaitForFish();
    } else {
       manager.CheckIfCaughtFish();
       delay(100); // cooldown for checking fish (this is a bit of a hack since sometimes the light sensor will read outside the range for one frame so the 100 milisecond delay prevents those readings from occuring)
    }
    
    if(CanUpdateTimer){

        UpdateTimer();
        tm1637.display(TimeDisplay);
    } else if (minute == 0 && second == 0 && microSecond == 0){
          tm1637.point(POINT_OFF);    

          TimeDisplay[2] = 0x49;   
          TimeDisplay[3] = 0x6E;
          TimeDisplay[0] = 0x99;
          TimeDisplay[1] = 0x46;
          tm1637.display(TimeDisplay);
          delay(500);
          tm1637.clearDisplay();
          delay(500);
          manager.EndGame();
    }
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





