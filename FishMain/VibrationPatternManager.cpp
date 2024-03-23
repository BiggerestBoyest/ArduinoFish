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
        if (!sensor->GetCurrentSensorState(25)) 
          break;

        timeDelay++;
      }
    
  }
}

//  VibrationPatternManager::PickRandomDelay(){
//     int rand = random(0, 6); // hard coded cause lazy should fix
    
//     switch(rand){
//       case 0:
//       return delayOne;
//       case 1:
//       return delayTwo;
//       case 2:
//       return delayThree
//       case 3:
//       return delayFour
//       case 4:
//       return delayFive
//       case 5:
//       return delaysix;
//       case 6:
//       return delaySeven;
//       case 7:
//       return
//       case 8:
//     }
// }


void VibrationPatternManager::SLRunMediumVibration() {
}

void VibrationPatternManager::SLRunDifficultVibration() {
}
