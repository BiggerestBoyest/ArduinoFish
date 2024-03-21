#ifndef helper_h
#define helper_h
#include "Arduino.h"
#include "Sensors.h"


 class Helper{
  public:
    Helper();
    void ReseedRandom(void); // arduino's random func does not reseed itself, therefore it needs to be reseeded on init to actually make it random. temp fix.
};

#endif



