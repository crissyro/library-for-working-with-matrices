#pragma once 

#include <iostream>

#define MIN_SIZE_MATRIX 2

template<typename T>
class Matrix {

private:
    size_t rows_, cols_;
    T **data_;

    void initMatrix();
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

    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator*(const T scalar);
    T& operator()(const size_t row, const size_t col);
    const T& operator()(const size_t row, const size_t col) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const T scalar);

    void printMatrix() const;
    bool isEqualMatrix(const Matrix& other);
    bool isSquareMatrix(const Matrix& other);
    bool isSymmetricMatrix(const Matrix& other);
    bool isEMatrix(const Matrix& other);
    bool isIdentityMatrix(const Matrix& other);
    bool isZeroMatrix(const Matrix& other);
    bool isSingular();


    void sumMatrix(const Matrix& other);
    voud subMatrix(const Matrix& other);
    void mulMatrix(const Matrix& other);
    void mulScalar(const T scalar);
    void transposeMatrix();
    Matrix transposeMatrix(const Matrix& other);
    void transposeSquareMatrix();
    Matrix transposeSquareMatrix(const Matrix& other);

    T determinant();
    Matrix cofactorMatrix();
    Matrix adjugateMatrix();
    Matrix inverseMatrix();
    Matrix inverseMatrix(const Matrix& other);
    Matrix calcComplementsMatrix();

};
