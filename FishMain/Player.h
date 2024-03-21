#ifndef player_h
#define player_h
#include "Arduino.h"

 class Player{
  public:
    Player();
    String playerName;
    void AddPoints(int points);
    void SetPlayerName(String newName);

    int currentPoints = 0;

};

#endif



