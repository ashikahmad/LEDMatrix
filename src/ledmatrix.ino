/*

          C8 C7    C1    C6 C4
PIN-16->   │  │ R2  │ R4  │  │ R1    <-PIN-9
          ┌┴──┴──┴──┴──┴──┴──┴──┴──┐
          │                        │
          │     1088BS PIN-MAP     │
          │                        │
          └┬──┬──┬──┬──┬──┬──┬──┬──┘
PIN-1 ->  R5 R7  │  │ R8  │ R6 R3    <-PIN-8
                C2 C3    C5

*/

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
