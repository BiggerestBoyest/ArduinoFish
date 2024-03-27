#ifndef fish_h
#define fish_h
#include "Arduino.h"

class Fish {
public:

enum FishType 
{
  SmallFish,
  Eal,
  Shark,
  Sunfish
};

  Fish(String name, int points, int bStrength, int fbMultiplier, enum FishType fishType);
  FishType CurrentFishType;
  //String fishName;
  float GetFalseBitPercentage(int currentCatchChance);
  String fishName;
  unsigned long GetBiteStrength() {
    return biteStrength;
  }
  int points;




private:
  unsigned long biteStrength;
  float falseBitePercentage;  // false bite percentage is based on the current catch percentage (for example, falseBitePercentage(30 / 100) * (100 - currentCatchChance))
  float GetFishValue() {
    return points;
  }

  //  float GetBiteStrength() {return biteStrength;}
};



#endif
