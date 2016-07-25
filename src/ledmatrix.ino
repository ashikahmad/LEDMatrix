#include <Arduino.h>
#include <LEDMatrix.h>

unsigned long lastScrollMillis = 0;
unsigned long scrollInterval = 100;

// Array of row pin numbers:
int row[8] = {
  10, 11, 12, 13, A0, A1, A2, A3
};

// Array of column pin numbers:
int col[8] = {
  2, 3, 4, 5, 6, 7, 8, 9
};

char text[] = "AYAAN AHMED *";
LEDMatrix ledMatrix = LEDMatrix();

void setup() {
  ledMatrix.setup(col, row, 8, 8);
  ledMatrix.setText(text, sizeof(text));
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastScrollMillis >= scrollInterval) {
    lastScrollMillis = currentMillis;
    ledMatrix.x--;
    if (ledMatrix.x < 0) ledMatrix.x += ledMatrix.getMaxCol();
  }

  ledMatrix.refreshDisplay();
}
