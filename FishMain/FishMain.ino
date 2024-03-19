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

Fish fish;
GameManager manager;
Sensors sensors;

unsigned char microSecond = 0;
unsigned char second = 5;
unsigned char minute = 2;
int8_t TimeDisplay[] = {0x00, 0x00, 0x00, 0x00};

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


  //Step 3 Start the game
  manager.StartGame();


}

void loop() { 

    while(!manager.GameStarted){} // doesn't start the game until the manager is ready
    
    if(CanUpdateTimer){
        UpdateTimer();
        tm1637.display(TimeDisplay);
    }
    
    Serial.print("test");
}


void UpdateTimer(){

    tm1637.point(POINT_ON);    //POINT_ON = 1,POINT_OFF = 0;

    TimeDisplay[2] = second / 10 ;
    TimeDisplay[3] = second % 10;
    TimeDisplay[0] = minute / 10;
    TimeDisplay[1] = minute % 10;
    CanUpdateTimer = false;
}


void SetupFourDigitDisplay(){
      tm1637.set(BRIGHT_TYPICAL);
      tm1637.init();
      Timer1.initialize(10000);//timing for 10ms

}

void TimingISR(){
    microSecond--;
    CanUpdateTimer = true;

    if (microSecond <= 0){
      second--;
        if (second <= 0){
          minute--;
          second = 59;
        }
        microSecond = 100;
    }
}





