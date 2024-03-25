#include "HardwareSerial.h"
#include "GameManager.h"
#include "Arduino.h"
#include "VibrationPatternManager.h"
#include "Helper.h"
#include <elapsedMillis.h>

VibrationPatternManager vbManager;
Fish testFish = Fish("testFish",10,20,30);

bool FLAG_HASPUTINLINE;
bool FLAG_HASFALSEBITE = false;
bool FLAG_BITEVIBRATION = false;
bool FLAG_TIMEBETWEENFALSEBITE = false;

//lets also not talk about it
unsigned long biteVibrationTime;
unsigned long falseBiteVibrationTime;
unsigned int falseBiteIncrementor; 
unsigned int falseBiteCooldown; 
unsigned int falseBiteSeed;


int microsecond = 0;
Fish *CurrentFish;

Helper helper;

//False Bite Delays
unsigned int delayOne[] = {5};
unsigned int delayTwo[] = {5,5,5};
unsigned int delayThree[] = {8};
unsigned int delayFour[] = {1,1};
unsigned int delayFive[] = {5,5};
unsigned int delaySix[] = {7,7,8};
unsigned int delaySeven[] = {5,5};
unsigned int delayEight[] = {6,8};

elapsedMillis test;
GameManager::GameManager(){}

void GameManager::StartGame(){
  //Might have some intro things occur here but for now it will simply allow for the sensors to work
  GameStarted = true;
  currentCatchChance = 10;
  catchPenalty = 10;
  helper.ReseedRandom();
  Serial.print("game init");
  falseBiteSeed = random(0,8);

}
void GameManager::Update() 
{
    CheckIfCaughtFish();
    WaitForFish();
    UpdateVibration();
    BiteVibration(CurrentFish->GetBiteStrength());
    FalseBiteVibration();
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

  if(!sensors->IsLineIn) return;

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
      //FISH IS CURRENTLY ON THE LINE
    } else if (rand > currentCatchChance && rand < CurrentFish->GetFalseBitPercentage(currentCatchChance)) {
      Serial.println("FALSE BITE");
      FLAG_HASFALSEBITE = true;
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

    if(!FLAG_HASFALSEBITE) return;
      Serial.print(falseBiteSeed);
    switch(falseBiteSeed){    //lets not speak of this
      case 0:
       SLVibration( delayOne,sizeof(delayOne) / sizeof(delayOne[0]), 3);
       break;
      case 1: 
       SLVibration( delayTwo,sizeof(delayTwo) / sizeof(delayTwo[0]), 3);
       break;
      case 2:
        SLVibration( delayThree,sizeof(delayThree) / sizeof(delayThree[0]), 5);
        break;
      case 3: 
        SLVibration( delayFour,sizeof(delayFour) / sizeof(delayFour[0]), 5);
        break;
      case 4:
        SLVibration( delayFive,sizeof(delayFive) / sizeof(delayFive[0]), 5);
        break;
      case 5:
        SLVibration( delaySix,sizeof(delaySix) / sizeof(delaySix[0]), 4);
        break;
      case 6: 
        SLVibration( delaySeven,sizeof(delaySeven) / sizeof(delaySeven[0]), 7);
        break;
      case 7: 
        SLVibration(delayEight,sizeof(delayEight) / sizeof(delayEight[0]), 3);
        break;
    }
}

void GameManager::SLVibration(unsigned int delays[], size_t arraySize, unsigned int timeBetweenDelay) 
{

   if (falseBiteIncrementor == arraySize){
        falseBiteIncrementor = 0;
        FLAG_HASFALSEBITE = false;
         FLAG_TIMEBETWEENFALSEBITE = false;
          falseBiteCooldown = 0;
          falseBiteVibrationTime = 0;
          sensors->UpdateVibrationMotor(false);
          UpdateFalseBiteSeed();
        sensors->UpdateVibrationMotor(false);
        return;
   }

   if (FLAG_TIMEBETWEENFALSEBITE)
    {
      sensors->UpdateVibrationMotor(false);
      if(falseBiteCooldown < timeBetweenDelay)
      {
        falseBiteCooldown++;
      }else
      {
        FLAG_TIMEBETWEENFALSEBITE = false;
        Serial.print("bite incremented by: ");
        Serial.print(falseBiteIncrementor);
        falseBiteIncrementor++;
        falseBiteCooldown = 0;
      }
    } else 
    {
      sensors->UpdateVibrationMotor(true);
      if (falseBiteVibrationTime < delays[falseBiteIncrementor])
      {
        falseBiteVibrationTime++;
      }
        else
        {
          FLAG_TIMEBETWEENFALSEBITE = true;
          falseBiteCooldown = 0;
          falseBiteVibrationTime = 0;
          sensors->UpdateVibrationMotor(false);
        }
    }

 if(!sensors->IsLineIn){ // checks if the user has pulled out the rod in time
      sensors->UpdateVibrationMotor(false); 
      falseBiteVibrationTime = 0;
      FLAG_HASFALSEBITE = false;
      FLAG_TIMEBETWEENFALSEBITE = false;
      falseBiteCooldown = 0;
      UpdateFalseBiteSeed();
      return;
    }


}

void GameManager::UpdateFalseBiteSeed()
{
  falseBiteSeed = random(0,8);
}

void GameManager::BiteVibration(unsigned long timeDelay){

  if (!FLAG_BITEVIBRATION) return;

    biteVibrationTime++;
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

   if(!sensors->IsLineIn){ // checks if the user has pulled out the rod in time
      sensors->UpdateVibrationMotor(false); 
      biteVibrationTime = 0;
      FLAG_BITEVIBRATION = false;
      return;
    }
}

void GameManager::CheckIfCaughtFish(){
  if(FLAG_HASPUTINLINE && !sensors->IsLineIn){
 biteVibrationTime = 0;
falseBiteVibrationTime = 0;
 falseBiteIncrementor = 0;
 falseBiteCooldown = 0;
  FLAG_HASPUTINLINE = false;
  FLAG_HASFALSEBITE = false;
   FLAG_BITEVIBRATION = false;
  FLAG_TIMEBETWEENFALSEBITE = false;
    sensors->UpdateVibrationMotor(false);
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
}

