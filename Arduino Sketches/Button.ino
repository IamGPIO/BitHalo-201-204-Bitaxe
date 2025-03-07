// v2 - Written by IamGPIO - BitHalo for the Bitaxe
#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 8
#define BUTTON_PIN 6          // Button pin
#define FADE_SPEED 5
#define MAX_INPUT_LENGTH 200  // Maximum length of input buffer
#define MAX_NUMBER 8          // Maximum number for LED colors

CRGB leds[NUM_LEDS];
String inputString = "";        
unsigned long previousMillis = 0;           // Stores last time LEDs were updated
int count = 0;                              // Stores count for incrementing up to the NUM_LEDs
int bootLoopCount = 0;                      // Initialize a counter to keep track of the number of BootLoops
int currentNumber = 0;                      // Number to determine LED color
bool buttonPressed = false;                 // Flag to track button state

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // Set button pin as input with pull-up resistor
  Serial.begin(115200);
  inputString.reserve(MAX_INPUT_LENGTH); 
}

void loop() {
  // Check for button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!buttonPressed) { // Only act on the first button press
      buttonPressed = true;
      handleButtonPress();
    }
  } else {
    buttonPressed = false; // Reset flag when button is released
  }

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
    for (int i = 0; i < 25000; i++) { // Run BootLoops 25000 times
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
  // Get the color based on the current number
  CRGB color = getColorForNumber(currentNumber);

  // Set all LEDs to the color and then show them
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(200); // Wait for a short period

  // Gradually fade out all LEDs while maintaining the color
  for (int brightness = 255; brightness >= 0; brightness -= FADE_SPEED) {
    CRGB fadedColor = color;
    fadedColor.nscale8(brightness);
    fill_solid(leds, NUM_LEDS, fadedColor);

    FastLED.show();
    delay(20); // Delay to control the speed of the fade out
  }
}

void handleButtonPress() {
  // Increment the current number and wrap around if it exceeds MAX_NUMBER
  currentNumber++;
  if (currentNumber > MAX_NUMBER) {
    currentNumber = 0;
  }

  // Print the current number to Serial for debugging
  Serial.print("Current Number: ");
  Serial.println(currentNumber);

  // Pulse the LEDs to show the new color
  pulseLeds();
}

void BuyLambo() {
  CRGB WHITE = CRGB(255, 255, 255);
  int flashCount = 0;

  while (flashCount < 1000000000) {
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

void BootLoops(int red, int green, int blue, int tail_length, int delay_duration, int interval, int direction) {
  unsigned long currentMillis = millis();   // Get the time
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;         // Save the last time the LEDs were updated
    count = 0;                              // Reset the count to 0 after each interval
  }
  if (direction == -1) {        // Reverse direction option for LEDs
    if (count < NUM_LEDS) {
      leds[NUM_LEDS - (count % (NUM_LEDS + 1))].setRGB(red, green, blue);    // Set LEDs with the color value
      count++;
    }
  } else {
    if (count < NUM_LEDS) {     // Forward direction option for LEDs
      leds[count % (NUM_LEDS + 1)].setRGB(red, green, blue);    // Set LEDs with the color value
      count++;
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, tail_length);                 // Fade the tail LEDs to black
  FastLED.show();
  delay(delay_duration);                                      // Delay to set the speed of the animation
}

// Function to map numbers to colors
CRGB getColorForNumber(int number) {
  switch (number) {
    case 0: return CRGB(50, 255, 0);   // Orange (GRB: G=165, R=255, B=0)
    case 1: return CRGB(0, 255, 0);   // Red (GRB: G=255, R=0, B=0)
    case 2: return CRGB(255, 0, 0);   // Green (GRB: G=0, R=255, B=0)
    case 3: return CRGB(0, 0, 255);   // Blue (GRB: G=0, R=0, B=255)
    case 4: return CRGB(255, 0, 255); // Cyan (GRB: G=255, R=0, B=255)
    case 5: return CRGB(0, 255, 255); // Magenta (GRB: G=0, R=255, B=255)
    case 6: return CRGB(255, 255, 0); // Yellow (GRB: G=255, R=255, B=0)
    case 7: return CRGB(0, 128, 128); // Purple (GRB: G=128, R=0, B=128)
    case 8: return CRGB(150, 150, 150); // White (GRB: G=255, R=255, B=255)
    default: return CRGB(0, 0, 0);     // Black (off)
  }
}
