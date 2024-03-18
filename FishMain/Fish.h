#ifndef fish_h
#define fish_h
#include "Arduino.h"

 class Fish{
  public:
    Fish();
   // Fish(String name, float points,float bStrength, float fbMultiplier);
     //String fishName;
     float test(float value);

private:
     float points;
     float biteStrength;
     float falseBiteMultiplier;

     float GetFishValue() {return points;}
     float GetBiteStrength() {return biteStrength;}
     float GetFalseBiteMultiplier(){return falseBiteMultiplier;}
};

#endif



