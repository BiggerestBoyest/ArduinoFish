#include "HardwareSerial.h"
#include "GameManager.h"
#include "Arduino.h"

bool FLAG_HASPUTINLINE;
int microsecond = 0;

GameManager::GameManager(){}

void GameManager::StartGame(){
  delay(1000);
  //Might have some intro things occur here but for now it will simply allow for the sensors to work
  GameStarted = true;
  currentCatchChance = 15;

  Serial.print("game init");

}

void GameManager::EndGame(){

}

void GameManager::WaitForFish(){

  if (hasFishOnLine)
    return;

  FLAG_HASPUTINLINE = true;

  microsecond++;
  Serial.println(microsecond);

  if(microsecond == 100)
  {
    currentLineTime++;
    microsecond = 0;

    int rand = random(0,100);
          Serial.println(rand);

    if (rand < currentCatchChance){
      hasFishOnLine = true;
      Serial.println("hasFish");
      //FISH IS CURRENTLY ON THE LINE
    } else {
      //CALCULATE IF A FALSE BITE IS DONE, WILL NEED TO HAVE A COOLDOWN WHEN FALSE BITES CAN OCCUR (SUCH AS NO FALSE BITES FOR THE FIRST 10-20 SECONDS AND YOU MIGHT NOT BE ABLE TO GET LIKE 4-5 FALSE BITES IN A ROW)
    }
    //IF AN ACTUAL BITE OCCUR CHECK IF THE USER HAS CAUGHT IT.
      if (currentLineTime % 15 == 0){
        currentCatchChance+= 10;
      }
  }
}

void GameManager::CheckIfCaughtFish(){
  if(FLAG_HASPUTINLINE){
    

    
  FLAG_HASPUTINLINE = false;

  if(hasFishOnLine){
    Serial.println("caught fish");
  } else {
    Serial.println("did not catch fish");
  }

  FLAG_HASPUTINLINE = false;
  hasFishOnLine = false;
  }
}

