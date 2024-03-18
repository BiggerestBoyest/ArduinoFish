#include "Arduino.h"
#include "Fish.h"

Fish fish;

void setup(){
  Serial.begin(9600);
  Serial.print(fish.test(10));
}

void loop() { 
  // put your main code here, to run repeatedly:

}


