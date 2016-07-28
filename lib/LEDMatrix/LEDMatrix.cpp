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
  nShiftReg = 0;

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

void LEDMatrix::setup(int rows[], int rowNum, int latch, int clock, int data) {
  rowPins = rows;
  nRows = rowNum;
  nCols = 8;
  latchPin = latch;
  clockPin = clock;
  dataPin = data;

  x = 0;
  nShiftReg = 1;

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Set everything HIGH on col as default
  writeToShiftReg(255);

  for (int thisPin = 0; thisPin < nRows; thisPin++) {
    pinMode(rowPins[thisPin], OUTPUT);
    //    digitalWrite(row[thisPin], LOW);
  }
}

int LEDMatrix::getRow(char c, int row) {
  if (c >= ' ' && c <= '~') {
    int index = c - ' ';
    int col = pgm_read_byte(&(Font8x8CharSet[index][row]));
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

    if (nShiftReg > 0) tempShiftData = 0;

    for (int thisCol = 0; thisCol < nCols; thisCol++) {
      int tempCol = thisCol - x;
      if (tempCol < 0) tempCol += maxCol;

      int tempChar = tempCol / charWidth;
      char c = text[tempChar];

      if (tempCol < 0 || tempCol >= maxCol) continue;
      tempCol %= charWidth;

      bool thisPixel = getBit(c, thisRow, charOffset+tempCol);
      thisPixel = (thisPixel == 0)? HIGH : LOW;

      if (nShiftReg > 0) { bitWrite(tempShiftData, thisCol, thisPixel); }
      else digitalWrite(colPins[thisCol], thisPixel);
    }

    if (nShiftReg > 0) {
      writeToShiftReg(tempShiftData);
    }
    digitalWrite(rowPins[thisRow], HIGH);
    delay(2);
    writeToShiftReg(255); // To clear out
    digitalWrite(rowPins[thisRow], LOW);
  }
}

// This method sends bits to the shift register:

void LEDMatrix::writeToShiftReg(int bitsToSend) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
  digitalWrite(latchPin, HIGH);
}

void LEDMatrix::registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}
