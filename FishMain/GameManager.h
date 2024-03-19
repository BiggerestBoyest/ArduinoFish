#ifndef GameManager_h
#define GameManager_h
#include "Arduino.h"
#include "Player.h"
#include "Fish.h"
#include <List.hpp>

 class GameManager{
  public:
    GameManager();
    List<Player> players;
    void EndGame();
    void StartGame();
    Fish GetFish();
    Fish GenerateFish(); // maybe generate random fish values sometimes idk with our predefined fish
    Fish GetRandomFish();
    bool HasGameEnded();
    void WaitForSensors();
    bool GameStarted = false;



private:
  float playerCount;



};

#endif



