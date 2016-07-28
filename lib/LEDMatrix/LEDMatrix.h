#ifndef LEDMATRIX_H
#define LEDMATRIX_H

class LEDMatrix {
public:
  int x;

  LEDMatrix();

  void setup(int cols[], int rows[], int colNum, int rowNum);
  void setup(int rows[], int rowNum, int latch, int clock, int data);

  bool getBit(char c, int row, int col);
  int getRow(char c, int row);
  int getMaxCol();

  void setText(char *txt, int length);
  void refreshDisplay();

private:
  int *colPins;
  int *rowPins;
  int nCols;
  int nRows;

  int latchPin;
  int clockPin;
  int dataPin;
  int nShiftReg;
  int tempShiftData;

  static const int charWidth = 6; // 5 Actually, 1 should be padding
  static const int charOffset= 2;

  char *text;
  int textLength;
  int maxCol;

  void writeToShiftReg(int bitsToSend);
  void registerWrite(int whichPin, int whichState);
};

#endif
