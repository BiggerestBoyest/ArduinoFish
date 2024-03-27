#include "Sensors.h"
#include "Arduino.h"
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "SoftwareI2C.h"
 #include "old_rgb_lcd.h"
#include "FishImage.h"
#include "Fish.h"

FishImage image;

//Pins for 4 digit display
#define CLK = 7
#define DIO = 7
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
  //   lcd.createChar(0, fish1);
  // lcd.createChar(1, fish2);
  // lcd.createChar(2, fish3);
  // lcd.setCursor(0, 0);
  // lcd.write((unsigned char)0);
  // lcd.write(1);
  // lcd.write(2);
  // lcd2.initSoftwareI2C(&rgb_lcd_2,4,3);
  lcd2.begin(16, 2);
  lcd2.print("jimmy");

//  lcd.begin(16, 2, LCD_5x8DOTS);

}
void Sensors::UpdateLCDScreen(String name, int points)
{
  lcd2.setCursor(0,0);
  lcd2.print(name);
  lcd2.setCursor(0,1);
    lcd2.print("Points: ");
  lcd2.print(points);
}

void Sensors::UpdateFishLCDScreen(Fish* fish)
{
    image.DisplayFishImage(&lcd,fish);
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