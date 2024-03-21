#include "Sensors.h"
#include "Arduino.h"
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#include "Sensors.h"
#include "vibrationPatternManager.h"



VibrationPatternManager::VibrationPatternManager() {}

void VibrationPatternManager::SLRunBasicVibration(Sensors *sensor, int delays[], size_t arraySize, int timeBetweenVibrate) {
  int elapsedTime = 0;
  bool FLAG_STOPVIBRATION = false;

  for (byte i = 0; i < arraySize; i++) {
    elapsedTime = 0;
    Serial.println(delays[i]);
    sensor->UpdateVibrationMotor(true);

    
    while (elapsedTime < delays[i]) {
      delay(1);
      if (!sensor->GetCurrentSensorState(25)) {
        FLAG_STOPVIBRATION = true;
        break;
      }
      elapsedTime++;
    }
      sensor->UpdateVibrationMotor(false);

  if (FLAG_STOPVIBRATION) 
      break;

      int timeDelay = 0;
      while(timeDelay < timeBetweenVibrate)
      {
        delay(1);
        if (!sensor->GetCurrentSensorState(25)) 
          break;

        timeDelay++;
      }
    
  }
}

void VibrationPatternManager::SLRunMediumVibration() {
}

void VibrationPatternManager::SLRunDifficultVibration() {
}
