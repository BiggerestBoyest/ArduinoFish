#ifndef Sensors_h
#define Sensors_h
#include "Arduino.h"
#include "rgb_lcd.h"
#include <Wire.h>
#include <TimerOne.h>

 class Sensors{
  public:
    void SetupSensors();
    int GetLighSensorValue();
    void WriteToLCD();
    void UpdateVibrationMotor(bool isOn);
    uint8_t GetVibrationMotorPin();
    uint8_t GetLightSensorPin();
    uint8_t GetFourDigitDisplayPin();
    //void UpdateTimer(unsigned char *second, unsigned char *minute);

    rgb_lcd lcd;

    Sensors();


  private:
    uint8_t pin1 = 0;
    uint8_t fourDigitDisplay = 2;
    uint8_t pin3 = 0;
    uint8_t vibrationMotorPin = 4;
    uint8_t lightSensorPin = 5;
   // void SetupFourDigitDisplay();


private:
};

#endif



