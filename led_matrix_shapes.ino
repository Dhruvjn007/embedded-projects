// Arduino UNO R4 WiFi - LED Matrix Shapes
// Uses built-in 12x8 LED matrix on UNO R4 WiFi
// Library: Arduino_LED_Matrix (comes pre-installed with UNO R4 board package)

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Custom bitmaps - each row is a byte (12 cols packed into 3 bytes x 8 rows = 96 bits)
// Using the 96-bit frame format: 3 uint32_t values

// Smiley face
const uint32_t smiley[] = {
  0x000000,
  0x3c4299,
  0x99423c  // simplified - see note below
};

// Heart shape
const uint32_t heart[] = {
  0x00,
  0x66ff,
  0xff6600
};

// Arrow pointing right
const uint32_t arrow_right[] = {
  0x000000,
  0x183c7e,
  0x3c1800
};

// Full frame format for UNO R4 LED matrix (12x8 = 96 bits as 3x uint32_t)
// Each frame is defined as {row0-row2, row3-row5, row6-row7}

// Better approach - use the built-in frames from the library
// The library has pre-built animations and frames

void setup() {
  Serial.begin(9600);
  matrix.begin();
  Serial.println("LED Matrix started");
}

void loop() {
  // Display built-in animations from the library
  // These are named constants in the Arduino_LED_Matrix library

  Serial.println("Showing: Danger");
  matrix.loadFrame(LEDMATRIX_DANGER);
  delay(2000);

  Serial.println("Showing: Emoji basic");
  matrix.loadFrame(LEDMATRIX_EMOJI_BASIC);
  delay(2000);

  Serial.println("Showing: Heart big");
  matrix.loadFrame(LEDMATRIX_HEART_BIG);
  delay(2000);

  Serial.println("Showing: Heart small");
  matrix.loadFrame(LEDMATRIX_HEART_SMALL);
  delay(2000);

  Serial.println("Showing: Like");
  matrix.loadFrame(LEDMATRIX_LIKE);
  delay(2000);

  Serial.println("Showing: Sad face");
  matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
  delay(2000);

  Serial.println("Showing: Happy face");
  matrix.loadFrame(LEDMATRIX_EMOJI_HAPPY);
  delay(2000);

  Serial.println("Showing: Resistor symbol");
  matrix.loadFrame(LEDMATRIX_RESISTOR);
  delay(2000);

  Serial.println("Showing: Arduino logo");
  matrix.loadFrame(LEDMATRIX_ARDUINOUNO);
  delay(2000);

  Serial.println("Showing: Student");
  matrix.loadFrame(LEDMATRIX_STUDENT);
  delay(2000);
}

/*
  Full list of available built-in frames (LEDMATRIX_*):
  LEDMATRIX_DANGER, LEDMATRIX_EMOJI_BASIC, LEDMATRIX_EMOJI_HAPPY,
  LEDMATRIX_EMOJI_SAD, LEDMATRIX_HEART_BIG, LEDMATRIX_HEART_SMALL,
  LEDMATRIX_LIKE, LEDMATRIX_RESISTOR, LEDMATRIX_ARDUINOUNO,
  LEDMATRIX_STUDENT, LEDMATRIX_CLOUD, and more.

  To make your OWN shapes, use the LED Matrix Editor tool:
  https://ledmatrix-editor.arduino.cc/
  It generates the uint32_t array you can paste here.
*/
