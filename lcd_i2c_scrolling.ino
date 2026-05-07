#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// address, columns, rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

String message = "Hello I am Dhruv Jain";
int msgLen;
int scrollPos = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  msgLen = message.length();

  lcd.setCursor(0, 0);
  lcd.print("  Dhruv's Arduino  "); // static top line
}

void loop() {
  lcd.setCursor(0, 1);

  // Build the 16-char window to display
  String padded = message + "                "; // pad with spaces so it clears cleanly
  String display = (padded + padded).substring(scrollPos, scrollPos + 16);

  lcd.print(display);

  scrollPos++;
  if (scrollPos >= msgLen + 1) {
    scrollPos = 0;
  }

  delay(300);
}
