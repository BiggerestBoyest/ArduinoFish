#include "Sensors.h"
#include "Arduino.h"
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#include "Sensors.h"
#include "vibrationPatternManager.h"



VibrationPatternManager::VibrationPatternManager() {}

void VibrationPatternManager::SLRunBasicVibration(Sensors *sensor, int delays[], unsigned int i, int timeBetweenVibrate) 
{


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
