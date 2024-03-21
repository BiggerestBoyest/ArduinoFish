#include "Player.h"
#include "Arduino.h"


Player::Player(){}
 


void Player::AddPoints(int points){
  currentPoints += points;
}

void Player::SetPlayerName(String newName){
  playerName = newName;
}