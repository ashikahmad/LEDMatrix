#ifndef LEDMATRIX_H
#define LEDMATRIX_H

class LEDMatrix {
public:
  LEDMatrix();

  bool getBit(char c, int row, int col);
  int getCol(char c, int row);

private:

};

#endif
