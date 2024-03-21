#include "HardwareSerial.h"
#include "GameManager.h"
#include "Arduino.h"
#include "VibrationPatternManager.h"

VibrationPatternManager vbManager;
Fish testFish = Fish("testFish",10,1500,30);

bool FLAG_HASPUTINLINE;
bool FLAG_HASFALSEBITE = false;

int microsecond = 0;
Fish *CurrentFish;

GameManager::GameManager(){}

void GameManager::StartGame(){
  delay(1000);
  //Might have some intro things occur here but for now it will simply allow for the sensors to work
  GameStarted = true;
  currentCatchChance = 5;
  catchPenalty = 10;

  Serial.print("game init");

}

void GameManager::EndGame(){
  
}

void GameManager::WaitForFish(){
  if (hasFishOnLine || FLAG_HASFALSEBITE)
    return;

    if (!FLAG_HASPUTINLINE){ // first time the line is in, generate a fish
      CurrentFish = &testFish; // always set current fish to test fish, however a system should be able to check what fish it should be
    }

  FLAG_HASPUTINLINE = true;

  microsecond++;
  if(microsecond == 1000)
  { 
    currentLineTime++;

    float rand = random(0,100);

    if (rand < currentCatchChance){
      hasFishOnLine = true;
      Serial.println("hasFish");
      BiteVibration();
      //FISH IS CURRENTLY ON THE LINE
    } else if (rand > currentCatchChance && rand < CurrentFish->GetFalseBitPercentage(currentCatchChance)) {
      Serial.println("FALSE BITE");
      FLAG_HASFALSEBITE = true;
      FalseBiteVibration();
      //CALCULATE IF A FALSE BITE IS DONE, WILL NEED TO HAVE A COOLDOWN WHEN FALSE BITES CAN OCCUR (SUCH AS NO FALSE BITES FOR THE FIRST 10-20 SECONDS AND YOU MIGHT NOT BE ABLE TO GET LIKE 4-5 FALSE BITES IN A ROW)
    }
    //IF AN ACTUAL BITE OCCUR CHECK IF THE USER HAS CAUGHT IT.
      if (currentLineTime % 15 == 0){
        currentCatchChance+= 10;
      }

          microsecond = 0;
  }
}
void GameManager::FalseBiteVibration(){

  int delays[] = {750,750,100};
  vbManager.SLRunBasicVibration(sensors, delays,sizeof(delays) / sizeof(delays[0]), 1000);
  // delay(100);
  // sensors->UpdateVibrationMotor(true);
  //   delay(100);
  // sensors->UpdateVibrationMotor(false);
  //   delay(100);
  // sensors->UpdateVibrationMotor(true);
  //   delay(100);
  // sensors->UpdateVibrationMotor(false);
  //   delay(100);
  // sensors->UpdateVibrationMotor(true);
  //   delay(100);
  // sensors->UpdateVibrationMotor(false);
  FLAG_HASFALSEBITE = false;
}

void GameManager::BiteVibration(){
  sensors->UpdateVibrationMotor(true);
  int elapsedTime = 0;
  while(elapsedTime < CurrentFish->GetBiteStrength()){
    delay(1);//frame buffer not sure why needed but it works
    elapsedTime++;

    if(!sensors->GetCurrentSensorState(25)){ // checks if the user has pulled out the rod in time
      sensors->UpdateVibrationMotor(false); 
      return;
    }
  }
      sensors->UpdateVibrationMotor(false);
      currentCatchChance = currentCatchChance - catchPenalty < 5 ? 5 : currentCatchChance - catchPenalty;// if the player missed the 
      hasFishOnLine = false;

}

void GameManager::CheckIfCaughtFish(){
  if(FLAG_HASPUTINLINE){
  FLAG_HASPUTINLINE = false;
  FLAG_HASFALSEBITE = false;

  if(hasFishOnLine){
    Serial.println("caught fish");
    currentCatchChance = 5;

  } else {
    Serial.println("did not catch fish");
  }
  hasFishOnLine = false;
  } else if (FLAG_HASFALSEBITE){
        Serial.println("did not catch fish false bite");
        hasFishOnLine = false;
        FLAG_HASPUTINLINE = false;
        FLAG_HASFALSEBITE = false;
  }
}

