#include <LEDMatrix.h>
#include <Font8x8.h>
#include <Arduino.h>

LEDMatrix::LEDMatrix() {
}

void LEDMatrix::setup(int *cols, int *rows, int colNum, int rowNum) {
  colPins = cols;
  rowPins = rows;
  nCols = colNum;
  nRows = rowNum;

  x = 0;

  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < nCols; thisPin++) {
    // initialize the output pins:
    pinMode(colPins[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(colPins[thisPin], HIGH);
  }
  for (int thisPin = 0; thisPin < nRows; thisPin++) {
    pinMode(rowPins[thisPin], OUTPUT);
    //    digitalWrite(row[thisPin], LOW);
  }
}

int LEDMatrix::getRow(char c, int row) {
  if (c >= ' ' && c <= '~') {
    int index = c - ' ';
    int col = charset[index][row];
    return col;
  }

  return 0;
}

bool LEDMatrix::getBit(char c, int row, int col) {
  int rowValues = getRow(c, row);
  if (rowValues == 0) return 0;

  int colMask = 1 << (7-col);
  int colValue = rowValues & colMask;
  return (colValue != 0);
}

int LEDMatrix::getMaxCol() {
  return maxCol;
}

void LEDMatrix::setText(char *txt, int length) {
  text = txt;
  textLength = length;
  maxCol = charWidth * textLength;
}

void LEDMatrix::refreshDisplay() {
  for(int thisRow = 0; thisRow < nRows; thisRow++){
    for (int thisCol = 0; thisCol < nCols; thisCol++) {
      int tempCol = thisCol - x;
      if (tempCol < 0) tempCol += maxCol;
      int tempChar = tempCol / charWidth;
      char c = text[tempChar];
      if (tempCol < 0 || tempCol >= maxCol) continue;
      tempCol %= charWidth;
      bool thisPixel = getBit(c, thisRow, charOffset+tempCol);
      thisPixel = (thisPixel == 0)? HIGH : LOW;
      digitalWrite(colPins[thisCol], thisPixel);
    }
    digitalWrite(rowPins[thisRow], HIGH);
    delay(2);
    digitalWrite(rowPins[thisRow], LOW);
  }
}
