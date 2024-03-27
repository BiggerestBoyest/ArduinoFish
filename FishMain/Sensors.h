#ifndef Sensors_h
#define Sensors_h
#include "Arduino.h"
#include "rgb_lcd.h"
#include <SoftwareI2C.h>
#include <TimerOne.h>
#include "Updatable.h"
#include "old_rgb_lcd.h"
#include "Fish.h"

class Sensors : public Updatable
{
  public:
    
    void SetupSensors();
    int GetLighSensorValue();
    void WriteToLCD();
    void Update() override;
    void Init() override;
    void Control() override;
    void UpdateVibrationMotor(bool isOn);
    uint8_t GetVibrationMotorPin();
    uint8_t GetLightSensorPin();
    uint8_t GetFourDigitDisplayPin();
    bool GetCurrentSensorState(unsigned char sensitivity);
    bool IsLineIn;
    void UpdateLCDScreen(String playerName, int points);
    void UpdateFishLCDScreen(Fish* fish);
    //void UpdateTimer(unsigned char *second, unsigned char *minute);
    rgb_lcd lcd;
    old_rgb_lcd lcd2;

    Sensors();


  private:
    uint8_t pin1 = 0;
    uint8_t fourDigitDisplay = 7;
    uint8_t pin3 = 0;
    uint8_t vibrationMotorPin = 4;
    uint8_t lightSensorPin = 3;
   // void SetupFourDigitDisplay();


};

#endif



