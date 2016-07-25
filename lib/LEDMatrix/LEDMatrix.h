#ifndef LEDMATRIX_H
#define LEDMATRIX_H

class LEDMatrix {
public:
  int x;

  LEDMatrix();

  void setup(int cols[], int rows[], int colNum, int rowNum);

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

  static const int charWidth = 6; // 5 Actually, 1 should be padding
  static const int charOffset= 2;

  char *text;
  int textLength;
  int maxCol;
};

#endif
