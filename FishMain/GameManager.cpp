#include "HardwareSerial.h"
#include "GameManager.h"
#include "Arduino.h"
#include "VibrationPatternManager.h"
#include "Helper.h"
#include <elapsedMillis.h>

VibrationPatternManager vbManager;
Fish testFish = Fish("testFish",10,50,30);

bool FLAG_HASPUTINLINE;
bool FLAG_HASFALSEBITE = false;
bool FLAG_BITEVIBRATION = false;

unsigned long biteVibrationTime;

int microsecond = 0;
Fish *CurrentFish;

Helper helper;

//False Bite Delays
int delayOne[] = {100};
int delayTwo[] = {100,100,100};
int delayThree[] = {200};
int delayFour[] = {300};
int delayFive[] = {100,100};
int delaySix[] = {200,200,300};
int delaySeven[] = {100,400};
int delayEight[] = {300,100};

elapsedMillis test;
GameManager::GameManager(){}

void GameManager::StartGame(){
  //Might have some intro things occur here but for now it will simply allow for the sensors to work
  GameStarted = true;
  currentCatchChance = 10;
  catchPenalty = 10;
  helper.ReseedRandom();
  Serial.print("game init");

}
void GameManager::Update() 
{
    CheckIfCaughtFish();
    WaitForFish();
    UpdateVibration();
    BiteVibration(CurrentFish->GetBiteStrength());
}

void GameManager::Control() 
{
  
}

void GameManager::Init() 
{
  Serial.print("testsssss");
}

void GameManager::EndGame(){
  HasGameEnded = true;
}

void GameManager::UpdateVibration(){

}

void GameManager::WaitForFish(){

  if(!sensors->GetCurrentSensorState(100)) return;
  if (hasFishOnLine || FLAG_HASFALSEBITE)
    return;

    if (!FLAG_HASPUTINLINE){ // first time the line is in, generate a fish
      CurrentFish = &testFish; // always set current fish to test fish, however a system should be able to check what fish it should be
    }

  FLAG_HASPUTINLINE = true;

  microsecond++;  
  if(microsecond == 20 && !hasFishOnLine)
  { 
    currentLineTime++;

    float rand = random(0,100);
    if (rand < currentCatchChance){
      hasFishOnLine = true;
      Serial.println("hasFish");
      FLAG_BITEVIBRATION = true;
      //BiteVibration(CurrentFish->GetBiteStrength());
      //FISH IS CURRENTLY ON THE LINE
    } else if (rand > currentCatchChance && rand < CurrentFish->GetFalseBitPercentage(currentCatchChance)) {
      Serial.println("FALSE BITE");
    //  FLAG_HASFALSEBITE = true;
      //FalseBiteVibration();
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

    int rand = random(0, 8); // hard coded cause lazy should fix

    Serial.print(rand);
    
    switch(rand){    //lets not speak of this

      case 0:
       vbManager.SLRunBasicVibration(sensors, delayOne,sizeof(delayOne) / sizeof(delayOne[0]), 500);
       break;
      case 1: 
       vbManager.SLRunBasicVibration(sensors, delayTwo,sizeof(delayTwo) / sizeof(delayTwo[0]), 500);
       break;
      case 2:
        vbManager.SLRunBasicVibration(sensors, delayThree,sizeof(delayThree) / sizeof(delayThree[0]), 500);
        break;
      case 3: 
        vbManager.SLRunBasicVibration(sensors, delayFour,sizeof(delayFour) / sizeof(delayFour[0]), 500);
        break;
      case 4:
        vbManager.SLRunBasicVibration(sensors, delayFive,sizeof(delayFive) / sizeof(delayFive[0]), 750);
        break;
      case 5:
        vbManager.SLRunBasicVibration(sensors, delaySix,sizeof(delaySix) / sizeof(delaySix[0]), 750);
        break;
      case 6: 
        vbManager.SLRunBasicVibration(sensors, delaySeven,sizeof(delaySeven) / sizeof(delaySeven[0]), 1000);
        break;
      case 7: 
        vbManager.SLRunBasicVibration(sensors, delayEight,sizeof(delayEight) / sizeof(delayEight[0]), 500);
        break;
    }

    

  FLAG_HASFALSEBITE = false;
}

void GameManager::BiteVibration(unsigned long timeDelay){

  if (!FLAG_BITEVIBRATION) return;
  biteVibrationTime++;
  Serial.print(biteVibrationTime);
  if (biteVibrationTime < timeDelay)
     sensors->UpdateVibrationMotor(true);
  else
  {
    sensors->UpdateVibrationMotor(false);
    currentCatchChance = currentCatchChance - catchPenalty < 5 ? 5 : currentCatchChance - catchPenalty;// if the player missed the 
    hasFishOnLine = false;
    FLAG_BITEVIBRATION = false;
    biteVibrationTime = 0;
  }

   if(!sensors->GetCurrentSensorState(100)){ // checks if the user has pulled out the rod in time
      sensors->UpdateVibrationMotor(false); 
      biteVibrationTime = 0;
      FLAG_BITEVIBRATION = false;
      return;
    }
  
  // while(elapsedTime < CurrentFish->GetBiteStrength()){

  //   if(!sensors->GetCurrentSensorState(25)){ // checks if the user has pulled out the rod in time
  //     sensors->UpdateVibrationMotor(false); 
  //     return;
  //   }
  // }
      // sensors->UpdateVibrationMotor(false);
      // currentCatchChance = currentCatchChance - catchPenalty < 5 ? 5 : currentCatchChance - catchPenalty;// if the player missed the 
      // hasFishOnLine = false;

}

void GameManager::CheckIfCaughtFish(){
  if(FLAG_HASPUTINLINE && !sensors->GetCurrentSensorState(100)){
  FLAG_HASPUTINLINE = false;
  FLAG_HASFALSEBITE = false;

  if(hasFishOnLine){
    Serial.println("caught fish");
    currentPlayer.currentPoints += CurrentFish->points;
        Serial.println(currentPlayer.currentPoints);
       currentPlayer.SetPlayerName("Josh");
    sensors->UpdateLCDScreen(currentPlayer.playerName,currentPlayer.currentPoints);
  } else {
    Serial.println("did not catch fish");
  }
      currentCatchChance = 10;
  hasFishOnLine = false;
  }
  // } else if (FLAG_HASFALSEBITE){
  //       Serial.println("did not catch fish false bite");
  //       hasFishOnLine = false;
  //       FLAG_HASPUTINLINE = false;
  //       FLAG_HASFALSEBITE = false;
  //     currentCatchChance = 10;
  //}
}

