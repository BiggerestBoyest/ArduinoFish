#include "Fish.h"
#include "Arduino.h"


Fish::Fish(String name, int points, int bStrength, int fbPercentage ){
  fishName = name;
  Fish::points = points;
  biteStrength = bStrength;
  falseBitePercentage = fbPercentage;
}


float Fish::GetFalseBitPercentage(int currentCatchChance){
  return (falseBitePercentage/100) * (100 - currentCatchChance);
}
// Fish::Fish(String name, int points, float bStrength, float fbMultiplier){
//   fishName = name;
// }

