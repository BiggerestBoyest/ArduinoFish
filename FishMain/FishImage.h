#ifndef fishImage_h
#define fishImage_h
#include "Arduino.h"
#include "rgb_lcd.h"
#include "old_rgb_lcd.h"
#include "Fish.h"


 class FishImage
 {
  public:
    void DisplayFishImage(rgb_lcd* lcd, Fish* fish);
    void DisplayFishImage(old_rgb_lcd* lcd, Fish* fish);
  private:
    void DisplaySmallFishImage(rgb_lcd* lcd);
    void DisplaySmallFishImage(old_rgb_lcd* lcd);

    void DisplayEalImage(rgb_lcd* lcd);
    void DisplayEalImage(old_rgb_lcd* lcd);

    void DisplaySharkImage(rgb_lcd* lcd);
    void DisplaySharkImage(old_rgb_lcd* lcd);

    void DisplaySunfishImage(rgb_lcd* lcd);
    void DisplaySunfishImage(old_rgb_lcd* lcd);
};




#endif



