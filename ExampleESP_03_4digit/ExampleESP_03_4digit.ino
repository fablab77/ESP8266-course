#include <QuadDisplay.h>

//Constants
#define DISPLAY_PIN D1   // what pin QuadDisplay is connected to

//Variables
unsigned long ms = 0;

void setup()
{
  displayDigits(DISPLAY_PIN, QD_L, QD_O, QD_a, QD_d); // off
  delay(500);
}

void loop()
{
  if (ms > millis()) {  // rollover handling issue
    displayDigits(DISPLAY_PIN, QD_MINUS, QD_MINUS, QD_MINUS, QD_MINUS);
    delay(1000);
  }
  
  if(millis() - ms > 1000) {
    ms = millis();
    int seconds = ms / 1000;
    int minutes = seconds / 60;
    displayTime(DISPLAY_PIN, minutes, seconds % 60);
  }
}
