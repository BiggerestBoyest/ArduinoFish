#ifndef fish_h
#define fish_h
#include "Arduino.h"

 class Fish{
  public:
    Fish(String name, int points,int bStrength, int fbMultiplier);
     //String fishName;
    float GetFalseBitPercentage(int currentCatchChance);
     String fishName;
     float GetBiteStrength() {return biteStrength;}
     int points;

private:
     int biteStrength;
     float falseBitePercentage; // false bite percentage is based on the current catch percentage (for example, falseBitePercentage(30 / 100) * (100 - currentCatchChance))
     float GetFishValue() {return points;}
    //  float GetBiteStrength() {return biteStrength;}
};

#endif



