#include "Fish.h"
#include "Arduino.h"

Fish::Fish(String name, int points, int bStrength, int fbPercentage, enum FishType fishType)
{
  fishName = name;
  Fish::points = points;
  biteStrength = bStrength;
  falseBitePercentage = fbPercentage;
  CurrentFishType = fishType;
}

float Fish::GetFalseBitPercentage(int currentCatchChance)
{
  return (falseBitePercentage/100) * (100 - currentCatchChance);
}

