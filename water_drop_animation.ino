// Arduino UNO R4 WiFi - Water Drop Falling Animation
// Simulates water drops falling from top and filling at bottom
// LED Matrix is 12 columns x 8 rows

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Matrix is 8 rows x 12 cols
// We store it as bool grid[8][12]
bool grid[8][12];

// Each drop has a column and current row position
struct Drop {
  int col;
  int row;
  bool active;
};

#define MAX_DROPS 4
Drop drops[MAX_DROPS];

int fillLevel = 7; // bottom row index (fills upward, so this decreases)
int filledRows = 0;

void clearGrid() {
  for (int r = 0; r < 8; r++)
    for (int c = 0; c < 12; c++)
      grid[r][c] = false;
}

void drawFilledBottom() {
  // Draw the accumulated water at the bottom
  for (int r = 7; r >= (8 - filledRows); r--) {
    for (int c = 0; c < 12; c++) {
      grid[r][c] = true;
    }
  }
}

void renderGrid() {
  // Convert bool grid to the 3x uint32_t format the library expects
  // Matrix format: 96 bits = 12 cols x 8 rows
  // bit layout: row0 is MSB side

  uint32_t frame[3] = {0, 0, 0};

  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 12; c++) {
      if (grid[r][c]) {
        // Each row is 12 bits, packed into 96 bits across 3 uint32_t values
        int bitIndex = r * 12 + c;
        int wordIndex = bitIndex / 32;
        int bitPos = 31 - (bitIndex % 32);
        frame[wordIndex] |= (1UL << bitPos);
      }
    }
  }

  matrix.loadFrame(frame);
}

void spawnDrop() {
  // Find an inactive drop slot
  for (int i = 0; i < MAX_DROPS; i++) {
    if (!drops[i].active) {
      drops[i].col = random(0, 12);
      drops[i].row = 0;
      drops[i].active = true;
      break;
    }
  }
}

void setup() {
  Serial.begin(9600);
  matrix.begin();
  randomSeed(analogRead(A0));

  for (int i = 0; i < MAX_DROPS; i++) drops[i].active = false;

  Serial.println("Water drop animation starting...");
}

void loop() {
  clearGrid();

  // Randomly spawn new drops
  if (random(0, 5) == 0) {
    spawnDrop();
  }

  int bottomFill = 8 - filledRows; // row index where filled water starts

  // Move drops down
  for (int i = 0; i < MAX_DROPS; i++) {
    if (!drops[i].active) continue;

    drops[i].row++;

    // Check if drop hit the water surface or bottom
    if (drops[i].row >= bottomFill) {
      drops[i].active = false;

      // Add to fill level
      if (filledRows < 8) {
        // Count how many drops have hit - fill a row every few drops
        static int dropCount = 0;
        dropCount++;
        if (dropCount >= 12) { // 12 drops fill one row
          dropCount = 0;
          filledRows++;
          Serial.print("Water level: ");
          Serial.println(filledRows);
        }
      }
    } else {
      grid[drops[i].row][drops[i].col] = true;
    }
  }

  drawFilledBottom();

  // If fully filled, reset
  if (filledRows >= 8) {
    delay(1000);
    filledRows = 0;
    Serial.println("Resetting...");
  }

  renderGrid();
  delay(150);
}
