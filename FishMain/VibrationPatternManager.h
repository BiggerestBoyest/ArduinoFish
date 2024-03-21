#ifndef vibrationPatternManager_h
#define vibrationPatternManager_h
#include "Arduino.h"
#include "Sensors.h"


 class VibrationPatternManager{
  public:
   VibrationPatternManager();
   void SLRunBasicVibration(Sensors *sensor, int delays[], size_t arraySize, int timeBetweenVibrate);  //SL meaning single loop (the function is made in mind that it is being run inside a loop) not the best naming convention but should be fine
   void SLRunMediumVibration();
   void SLRunDifficultVibration();
   int* PickRandomDelay(); // lazy function to pick a delay based on switch case
};

#endif



