#pragma once 

#include <iostream>

#define MIN_SIZE_MATRIX 2

template<typename T>
class Matrix {

private:
    size_t rows_, cols_;
    T **data_;

    void initMatrix(size_t rows, size_t cols);
    void freeMemoryMatrix();

public:
    size_t getRows() const { return rows_; };
    size_t getCols() const { return cols_; };
    void makeMatrixFromArray(const T** array);
    Matrix();
    Matrix(const size_t size);
    Matrix(const size_t rows, const size_t cols);
    Matrix(const size_t rows, const size_t cols, T** array);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();
 
};
