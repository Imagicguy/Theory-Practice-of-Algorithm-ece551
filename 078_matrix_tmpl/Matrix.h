#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>

class Matrix
{
 private:
  int numRows;
  int numColumns;
  vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new vector<T> *[numRows]();
    for (int i = 0; i < numRows; i++) {
      rows[i] = new vector<T>(numColumns);
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new vector<T> *[numRows]();
    for (int i = 0; i < numRows; i++) {
      rows[i] = new vector<T>(rhs[i]);
    }
  }
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      for (int j = 0; j < numRows; j++) {
        delete rows[j];
      }
      delete[] rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = new vector<T> *[numRows]();
      for (int i = 0; i < numRows; i++) {
        rows[i] = new vector<T>(rhs[i]);
      }
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const vector<T> & operator[](int index) const {
    assert(index < numRows && index >= 0);
    return *rows[index];
  }

  vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return *rows[index];
  }

  bool operator==(const Matrix & rhs) const {
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

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix newMatrix(*this);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*newMatrix.rows[i])[j] += (*rhs.rows[i])[j];
      }
    }
    return newMatrix;
  }
};

template<typename T>
ostream & operator<<(ostream & s, const vector<T> & rhs) {
  s << "{";
  int numC = rhs.size();
  for (int i = 0; i < numC; i++) {
    s << rhs[i];
    if (i != numC - 1)
      s << ", ";
  }
  s << "}";
  return s;
}

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1)
      s << ",\n";
  }
  s << " ]";
  return s;
}
//YOUR CODE GOES HERE!

#endif
