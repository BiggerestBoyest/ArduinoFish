#ifndef updatable_h
#define updatable_h
#include "Arduino.h"
#include "Sensors.h"

//abstract class to denote a class runs on the main frame loop
class Updatable{ 
  public:
    virtual void Init() const = 0;
    virtual void Update() const = 0; 
    virtual void Control() const = 0;
};

#endif



