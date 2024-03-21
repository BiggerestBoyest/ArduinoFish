#include "Helper.h"
#include "Arduino.h"
#include <EEPROM.h>

Helper::Helper(){}

void Helper::ReseedRandom(void)
{
  //Thanks to https://forum.arduino.cc/t/the-reliable-but-not-very-sexy-way-to-seed-random/65872
  static const uint32_t HappyPrime = 937;
  union
  {
    uint32_t i;
    uint8_t b[4];
  }

  raw;
  byte i;
  unsigned int seed;
  
  for (  i=0; i < sizeof(raw.b); ++i )
  {
    raw.b[i] = EEPROM.read( i );
  }

  do
  {
    raw.i += HappyPrime;
    seed = raw.i & 0x7FFFFFFF;
  }
  while ( (seed < 1) || (seed > 65534 ) );

  randomSeed( seed );  

  for ( i=0; i < sizeof(raw.b); ++i )
  {
    EEPROM.write( i, raw.b[i] );
  }
}

