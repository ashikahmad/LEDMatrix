#include <Arduino.h>
#include <LEDMatrix.h>

unsigned long lastScrollMillis = 0;
unsigned long scrollInterval = 100;

// 2-dimensional array of row pin numbers:
const int row[8] = {
  10, 11, 12, 13, A0, A1, A2, A3
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  2, 3, 4, 5, 6, 7, 8, 9
};

char text[] = "Ashik uddin Ahmad * 1234567890 WWW";
int textLength = 11;
LEDMatrix ledMatrix;

#define nChars 6
#define nRows  8
#define nCols  8
#define charW  6
#define charOffset 2

// cursor position:
int x = 0;

void setup() {
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(col[thisPin], HIGH);
//    digitalWrite(row[thisPin], LOW);
  }

  ledMatrix = LEDMatrix();
  Serial.begin(9600);
}

void loop() {
  int maxCol = charW * sizeof(text);

  unsigned long currentMillis = millis();
  if (currentMillis - lastScrollMillis >= scrollInterval) {
    lastScrollMillis = currentMillis;
    x--;
    if (x < 0) x += maxCol;
  }

  for(int thisRow = 0; thisRow < 8; thisRow++){
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      int tempCol = thisCol - x;
      if (tempCol < 0) tempCol += maxCol;
      int tempChar = tempCol / charW;//nCols;
      char c = text[tempChar];
      if (tempCol < 0 || tempCol >= maxCol) continue;
      tempCol %= charW;//nCols;
      bool thisPixel = ledMatrix.getBit(c, thisRow, charOffset+tempCol); //pixels[tempChar][thisRow][tempCol];
      thisPixel = (thisPixel == 0)? HIGH : LOW;
      digitalWrite(col[thisCol], thisPixel);
    }
    digitalWrite(row[thisRow], HIGH);
    delay(2);
    digitalWrite(row[thisRow], LOW);
  }
}
