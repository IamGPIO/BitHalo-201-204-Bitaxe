// v2 - Written by IamGPIO - BitHalo for the Bitaxe
#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 8
#define FADE_SPEED 5
#define MAX_INPUT_LENGTH 200  // Maximum length of input buffer

CRGB leds[NUM_LEDS];
String inputString = "";        
unsigned long previousMillis = 0;           // Stores last time LEDs were updated
int count = 0;                              // Stores count for incrementing up to the NUM_LEDs
int bootLoopCount = 0; // Initialize a counter to keep track of the number of BootLoops

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(115200);
  inputString.reserve(MAX_INPUT_LENGTH); 
}

void loop() {
  // Actively check for serial data
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;

    // Check for newline character or buffer overflow
    if (inChar == '\n' || inputString.length() >= MAX_INPUT_LENGTH) {
      processInput();
    }
  }
}

void processInput() {
  if (inputString.indexOf("accepted") >= 0) {
    pulseLeds();
  }
  
  if (inputString.indexOf("BLOCK FOUND") >= 0) {
    BuyLambo();
  }

  if (inputString.indexOf("Initializing serial") >= 0) {
    for (int i = 0; i < 250; i++) { // Run BootLoops 250 times
      BootLoops(0, 100, 255, 30, 30, 1000, 1);
      bootLoopCount++;
      if (bootLoopCount >= 250) {
        break; // Exit the loop after 250 iterations
      }
    }
  }

  // Clear the input string for new data
  inputString = "";
}

void pulseLeds() {
  // Set all LEDs to a color (e.g., dark orange) and then show them
  CRGB darkOrange = CRGB(50, 200, 0);
  fill_solid(leds, NUM_LEDS, darkOrange);
  FastLED.show();
  delay(200); // Wait for a short period

  // Gradually fade out all LEDs while maintaining the color
  for (int brightness = 255; brightness >= 0; brightness -= FADE_SPEED) {
    CRGB fadedColor = darkOrange;
    fadedColor.nscale8(brightness);
    fill_solid(leds, NUM_LEDS, fadedColor);

    FastLED.show();
    delay(20); // Delay to control the speed of the fade out
  }
}




void BuyLambo() {
  CRGB WHITE = CRGB(255, 255, 255);
  int flashCount = 0;

  while (flashCount < 1000) {
    // Turn on all LEDs to white
    fill_solid(leds, NUM_LEDS, WHITE);
    FastLED.show();
    delay(100); // Wait for a short period

    // Turn off all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(100); // Wait for a short period

    flashCount++;
  }
}


void BootLoops(int red, int green, int blue, int tail_length, int delay_duration, int interval, int direction){
  unsigned long currentMillis = millis();   // Get the time
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;         // Save the last time the LEDs were updated
    count = 0;                              // Reset the count to 0 after each interval
  }
  if (direction == -1) {        // Reverse direction option for LEDs
    if (count < NUM_LEDS) {
      leds[NUM_LEDS - (count % (NUM_LEDS+1))].setRGB(red, green, blue);    // Set LEDs with the color value
      count++;
    }
  }
  else {
    if (count < NUM_LEDS) {     // Forward direction option for LEDs
      leds[count % (NUM_LEDS+1)].setRGB(red, green, blue);    // Set LEDs with the color value
      count++;
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, tail_length);                 // Fade the tail LEDs to black
  FastLED.show();
  delay(delay_duration);                                      // Delay to set the speed of the animation
}
