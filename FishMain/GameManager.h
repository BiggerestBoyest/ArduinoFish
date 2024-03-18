#ifndef GameManager_h
#define GameManager_h
#include "Arduino.h"
#include "Player.h"
#include "Fish.h"
#include "Dictionary.h"

 class GameManager{
  public:
    GameManager();
    
    List<> players;
    map <int,Fish>* FishCollection;

    void EndGame();
    void StartGame();
    Fish GetFish();
    Fish GenerateFish(); // maybe generate random fish values sometimes idk with our predefined fish
    Fish GetRandomFish();
    bool HasGameEnded();
     WaitForSensors();



private:
  float playerCount;



};

#endif



