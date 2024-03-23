#include "Sensors.h"
#include "Arduino.h"
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#include <Wire.h>
#include "rgb_lcd.h"



//Pins for 4 digit display
#define CLK 2
#define DIO 3
// TM1637 tm1637(CLK, DIO);
// int8_t TimeDisplay[] = {0x00, 0x00, 0x00, 0x00};


Sensors::Sensors(){}

void Sensors::SetupSensors(){

  Serial.println("setting up sensors");

  //Set up light sensor
  pinMode(lightSensorPin,OUTPUT);
  //Set up vibration sensor
  pinMode(vibrationMotorPin,OUTPUT);
  //Set up 4digitdisplay 
  pinMode(fourDigitDisplay,OUTPUT);
  //SetupFourDigitDisplay();
  //Set up LCD
  lcd.begin(16,2);
  Serial.println("setting up sensors");

}

void Sensors::UpdateLCDScreen(String name, int points){
  lcd.setCursor(0,0);
  lcd.print(name);
  lcd.setCursor(0,1);
    lcd.print("Points: ");
  lcd.print(points);
}

uint8_t Sensors::GetVibrationMotorPin(){
    return vibrationMotorPin;
}

uint8_t Sensors::GetLightSensorPin(){
    return lightSensorPin;
}

uint8_t Sensors::GetFourDigitDisplayPin(){
    return fourDigitDisplay;
}

void Sensors::UpdateVibrationMotor(bool isOn){
    if(isOn)
      digitalWrite(vibrationMotorPin, HIGH);
    else
      digitalWrite(vibrationMotorPin, LOW);
}


bool Sensors::GetCurrentSensorState(unsigned char sensitivity){

  int value = analogRead(lightSensorPin);

  if (value < sensitivity){
    return true;
  }

  return false;

}



// void Sensors::SetupFourDigitDisplay(){
//       tm1637.set(BRIGHT_TYPICAL);
//       tm1637.init();
//       Timer1.initialize(10000);//timing for 10ms

// }

// void Sensors::UpdateTimer(unsigned char second, unsigned char minute){

//     tm1637.point(POINT_ON);    //POINT_ON = 1,POINT_OFF = 0;

//     TimeDisplay[2] = second / 10 ;
//     TimeDisplay[3] = second % 10;
//     TimeDisplay[0] = minute;
//     TimeDisplay[1] = 5;

//     tm1637.display(TimeDisplay);

// }

// void TimingISR(){
//     second++;
//     CanUpdateTimer = true;

//     if (second >= 100){
//       second++;
//         if (second >= 60){
//           minute++;
//           second = 0;
//         }
      
//       second = 0;
//     }
// }


