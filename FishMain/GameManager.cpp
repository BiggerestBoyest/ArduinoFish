#include "GameManager.h"
#include "Arduino.h"


GameManager::GameManager(){}

void GameManager::StartGame(){
  delay(1000);
  //Might have some intro things occur here but for now it will simply allow for the sensors to work
  GameStarted = true;

  Serial.print("game init");

}

