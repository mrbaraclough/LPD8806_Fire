#include "LPD8806.h"
#ifdef __AVR_ATtiny85__
  #include <avr/power.h>
#endif

// LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 8;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

// the setup routine runs once when you press reset:
void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();
}

// the loop routine runs over and over again forever:
void loop() {
  int r = 255;
  int g = r - 80;
  int b = 80;
  
  for(int x = 0; x < nLEDs; x++)
  {
    int flicker = random(0,150);
    int rFlicker = r - flicker;
    int gFlicker = g - flicker;
    int bFlicker = b - flicker;
    if (rFlicker < 0) rFlicker = 0;
    if (gFlicker < 0) gFlicker = 0;
    if (bFlicker < 0) bFlicker = 0;
    strip.setPixelColor(x, rFlicker, gFlicker, bFlicker);
  }
  strip.show();
  delay(random(50,150));
}
    
