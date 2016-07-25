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

char text[] = "Hello 123! ";
int textLength = 11;
LEDMatrix ledMatrix;

#define nChars 6
#define nRows  8
#define nCols  8

// 2-dimensional array of pixels:
boolean pixels[nChars][nRows][nCols] = {
  { // A
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0}
  },
  { // Y
    {1, 1, 1, 0, 0, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  { // A
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0}
  },
  { // A
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0}
  },
  { // N
    {0, 1, 0, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 1, 0}
  },
  { // .
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  }
};

// cursor position:
int x = 0;
int y = 5;

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

}

void loop() {
  int maxCol = nCols * textLength;

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
      int tempChar = tempCol / nCols;
      char c = text[tempChar];
      if (tempCol < 0 || tempCol >= maxCol) continue;
      tempCol %= nCols;
      int thisPixel = ledMatrix.getBit(c, thisRow, tempCol); //pixels[tempChar][thisRow][tempCol];
      thisPixel = (thisPixel == 0)? HIGH : LOW;
      digitalWrite(col[thisCol], thisPixel);
    }
    digitalWrite(row[thisRow], HIGH);
    delay(2);
    digitalWrite(row[thisRow], LOW);
  }
}
