#include "FishImage.h"
#include "Arduino.h"
#include "Fish.h"

byte fish1[8] = 
{
    0b00000,
    0b00000,
    0b00111,
    0b01000,
    0b10000,
    0b10100,
    0b10000,
    0b01000
};

byte fish2[8] = {
      0b00000,
    0b00000,
    0b11000,
    0b00110,
    0b00001,
    0b00001,
    0b00001,
    0b00010
};

byte fish3[8] = 
{
    0b00000,
    0b00110,
    0b01000,
    0b01010,
    0b10100,
    0b00010,
    0b11000,
    0b00110
};

byte eal1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01111,
  0b10000,
  0b10100,
  0b10000,
  0b01111
};
byte eal2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00111,
  0b11000,
  0b00000,
  0b00111,
  0b11000
};
byte eal3[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00000,
  0b01110,
  0b10001
};
byte eal4[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10010,
  0b00100,
  0b01000,
  0b10000
};

byte shark1[8] = {
  0b00000,
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10101,
  0b01010,
  0b00100
};
byte shark2[8] = {
  0b00000,
  0b11100,
  0b00010,
  0b01001,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte shark3[8] = {
  0b00000,
  0b00000,
  0b00010,
  0b11100,
  0b10010,
  0b01010,
  0b01100,
  0b00100
};
byte shark4[8] = {
  0b00000,
  0b00000,
  0b00010,
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b10001
};
byte sunfish1[8] = {
  0b00001,
  0b00111,
  0b01000,
  0b10000,
  0b10110,
  0b10100,
  0b10000,
  0b10000
};
byte sunfish2[8] = {
  0b10000,
  0b11100,
  0b00010,
  0b00001,
  0b01001,
  0b10001,
  0b01001,
  0b00001
};
byte sunfish3[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b10000,
  0b01000,
  0b10000,
  0b01000
};


void FishImage::DisplayFishImage(rgb_lcd* lcd, Fish* fish)
{ 

  switch(fish->CurrentFishType)
  {
      case 0:
        DisplaySmallFishImage(lcd);
        break;
      case 1:
        DisplayEalImage(lcd);
        break;
      case 2:
        DisplaySharkImage(lcd);
        break;
      case 3:
        DisplaySunfishImage(lcd);
        break;
  }


}

void FishImage::DisplayEalImage(rgb_lcd* lcd)
{
  lcd->createChar(0, eal1);
  lcd->createChar(1, eal2);
  lcd->createChar(2, eal3);
  lcd->createChar(3, eal4);
  lcd->setCursor(0, 0);
  lcd->write((unsigned char)0);
  lcd->write(1);
  lcd->write(2);
   lcd->write(3);
}

void FishImage::DisplaySmallFishImage(rgb_lcd* lcd)
{
  lcd->createChar(0, fish1);
  lcd->createChar(1, fish2);
  lcd->createChar(2, fish3);
  lcd->setCursor(0, 0);
  lcd->write((unsigned char)0);
  lcd->write(1);
  lcd->write(2);
}



void FishImage::DisplaySharkImage(rgb_lcd* lcd)
{
  lcd->createChar(0, shark1);
  lcd->createChar(1, shark2);
  lcd->createChar(2, shark3);
  lcd->createChar(3, shark4);
  lcd->setCursor(0, 0);
  lcd->write((unsigned char)0);
  lcd->write(1);
  lcd->write(2);
  lcd->write(3);
}



void FishImage::DisplaySunfishImage(rgb_lcd* lcd)
{
  lcd->createChar(0, sunfish1);
  lcd->createChar(1, sunfish2);
  lcd->createChar(2, sunfish3);
  lcd->setCursor(0, 0);
  lcd->write((unsigned char)0);
  lcd->write(1);
  lcd->write(2);
}

