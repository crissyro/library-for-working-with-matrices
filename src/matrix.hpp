#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

#define MIN_SIZE_MATRIX 2

// Исключение для неподдерживаемых типов данных
class MatrixTypeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Matrix type error: matrix does not support this type.";
    }
};

template<typename T>
class Matrix {
    static_assert(std::is_arithmetic<T>::value, "Matrix only supports numeric types.");

private:
    size_t rows_, cols_;
    std::unique_ptr<std::unique_ptr<T[]>[]> data_; 

    void initMatrix() noexcept;
    void freeMemoryMatrix() noexcept;
    void copyMatrix(const Matrix<T>& other) noexcept;

public:
    size_t getRows() const noexcept;
    size_t getCols() const noexcept;

    Matrix() noexcept;
    Matrix(const size_t size) noexcept;
    Matrix(const size_t rows, const size_t cols) noexcept;
    Matrix(const size_t rows, const size_t cols, T** array) noexcept;
    Matrix(const Matrix& other) noexcept;
    Matrix(Matrix&& other) noexcept;
    ~Matrix() noexcept = default; 

    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const T scalar) const;
    T& operator()(const size_t row, const size_t col);
    const T& operator()(const size_t row, const size_t col) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const T scalar);

    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
    std::istream& operator>>(std::istream& is, Matrix<T>& matrix);
    
    bool isEqualMatrix(const Matrix& other) const noexcept;
    bool isSquareMatrix() const noexcept;
    bool isSymetricMatrix() const noexcept;
    bool isIdentityMatrix() const;
    bool isZeroMatrix() const;
    bool isSingular() const;
    bool isDiagonalMatrix() const;
    bool isTriangularMatrix() const;
    bool isUpperTriangularMatrix() const;
    bool isLowerTriangularMatrix() const;
    bool isOrthogonalMatrix() const;
    bool isDiagonalizable() const;
    bool isNormalMatrix() const;

    void makeMatrixFromArray(const T** array);
    void printMatrix() const;
    void sumMatrix(const Matrix& other);
    void subMatrix(const Matrix& other);
    void mulMatrix(const Matrix& other);
    void mulScalar(const T scalar);
    void transposeMatrix();
    Matrix transposeMatrix(const Matrix& other) const;
    void transposeSquareMatrix();
    Matrix transposeSquareMatrix(const Matrix& other) const;

    T determinant() const;
    Matrix cofactorMatrix() const;
    Matrix adjugateMatrix() const;
    Matrix inverseMatrix() const;
    Matrix inverseMatrix(const Matrix& other) const;
    Matrix calcComplementsMatrix() const;

};