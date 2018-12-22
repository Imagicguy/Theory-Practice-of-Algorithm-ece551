#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[numRows]();
  for (int i = 0; i < numRows; i++)
    rows[i] = new IntArray(numColumns);
}

IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new IntArray *[numRows]();
  for (int i = 0; i < numRows; i++)
    rows[i] = new IntArray(rhs[i]);  // row[i] points to IntAttay
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++)
    delete rows[i];
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {  //why *this != rhs doesn't work
    for (int j = 0; j < numRows; j++) {
      delete rows[j];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows =
        new IntArray *[numRows]();  //same as malloc ,rows is **,so new should followed by a dereference one ,aka *
    for (int i = 0; i < numRows; i++) {
      rows[i] =
          new IntArray(*rhs.rows[i]);  //rows[i] is IntArray pointer,so dereference is IntArray
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix newMatrix(*this);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*newMatrix.rows[i])[j] += (*rhs.rows[i])[j];
    }
  }
  return newMatrix;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1)
      s << ",\n";
  }
  s << " ]";
  return s;
}
