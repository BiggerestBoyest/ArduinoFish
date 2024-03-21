#ifndef GameManager_h
#define GameManager_h
#include "Arduino.h"
#include "Player.h"
#include "Fish.h"
#include <List.hpp>
#include "Sensors.h"

 class GameManager{
  public:
    GameManager();
    List<Player> players;
    Player currentPlayer;
    void EndGame();
    void StartGame();
    Fish GetFish();
    Fish GenerateFish(); // maybe generate random fish values sometimes idk with our predefined fish
    Fish GetRandomFish();
    bool HasGameEnded = false;
    void WaitForSensors();
    void WaitForFish(); // not sure what the method should be called, but essentially holds all the logic for when the line is in and the player is waiting for a fish 
    void CheckIfCaughtFish(); // also should have a different name but for now its fine
    bool hasFishOnLine = false;
    bool GameStarted = false;
    int currentCatchChance; // 
    int currentLineTime;
    float catchPenalty; // penalty to the catch chance if a player ignores a real bite
    Sensors *sensors;



private:
  float playerCount;
  void FalseBiteVibration();
  void BiteVibration();


};

#endif



