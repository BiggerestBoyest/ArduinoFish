#include "Sensors.h"
#include "Arduino.h"
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "SoftwareI2C.h"
 #include "old_rgb_lcd.h"



byte fish1[8] = {
    0b00000,
    0b00000,
    0b00111,
    0b01000,
    0b10000,
    0b10100,
    0b10000,
    0b01000
};
byte fish2[8] = {
      0b00000,
    0b00000,
    0b11000,
    0b00110,
    0b00001,
    0b00001,
    0b00001,
    0b00010
};
byte fish3[8] = {
      0b00000,
    0b00110,
    0b01000,
    0b01010,
    0b10100,
    0b00010,
    0b11000,
    0b00110
};


//Pins for 4 digit display
#define CLK 2
#define DIO 3
// TM1637 tm1637(CLK, DIO);
// int8_t TimeDisplay[] = {0x00, 0x00, 0x00, 0x00};
SoftwareI2C rgb_lcd_1;
SoftwareI2C rgb_lcd_2;

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
  lcd.initSoftwareI2C(&rgb_lcd_1,3,2);
    lcd.createChar(0, fish1);
  lcd.createChar(1, fish2);
  lcd.createChar(2, fish3);
  lcd.setCursor(0, 0);
  lcd.write((unsigned char)0);
  lcd.write(1);
  lcd.write(2);
  // lcd2.initSoftwareI2C(&rgb_lcd_2,4,3);
  lcd2.begin(16, 2);
  lcd2.print("jimmy");

//  lcd.begin(16, 2, LCD_5x8DOTS);

}
void Sensors::UpdateLCDScreen(String name, int points){
  // lcd.setCursor(0,0);
  // lcd.print(name);
  // lcd.setCursor(0,1);
  //   lcd.print("Points: ");
  // lcd.print(points);
  // lcd2.print("test");
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

void Sensors::Update() 
{
  IsLineIn = GetCurrentSensorState(75);
}

void Sensors::Init(){

}

void Sensors::Control(){
  
}

bool Sensors::GetCurrentSensorState(unsigned char sensitivity)
{
  int value = analogRead(lightSensorPin);

  if (value < sensitivity){
    return true;
  }

  return false;

}