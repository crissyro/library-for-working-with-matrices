#pragma once 

#include <iostream>
#include <vector>
#include <memory>

namespace matrix_lib {

template <typename T>
class SparseMatrix {

private:
    std::vector<size_t> rowsIndexes;        // Индексы строк ненулевых элементов
    std::vector<size_t> colsIndexes;        // Индексы столбцов ненулевых элементов
    std::vector<T> values;        // Ненулевые значения
    size_t rows_;               // Количество строк
    size_t cols_;               // Количество столбцов

public:
    SparseMatrix();
    SparseMatrix(size_t rows, size_t cols);
    SparseMatrix(const std::vector<T>& values);
    SparseMatrix(const SparseMatrix& other);
    SparseMatrix(const SparseMatrix&& other);
    ~SparseMatrix();

    SparseMatrix& operator=(const SparseMatrix& other);
    SparseMatrix& operator=(SparseMatrix&& other) noexcept;

    size_t getRows() const { return rows_; }
    size_t getCols() const { return cols_; }

    SparseMatrix operator+(const SparseMatrix& other) const;
    SparseMatrix operator-(const SparseMatrix& other) const;
    SparseMatrix operator*(const SparseMatrix& other) const;
    SparseMatrix operator*(T scalar) const;
    SparseMatrix& operator+=(const SparseMatrix& other);
    SparseMatrix& operator-=(const SparseMatrix& other);
    SparseMatrix& operator*=(const SparseMatrix& other);

    bool operator==(const SparseMatrix& other) const;
    bool operator!=(const SparseMatrix& other) const;

    bool isZeroSparseMatrix() const;
    bool isSquareSparseMatrix() const;
    bool isIdentitySparseMatrix() const;
    bool isDiagonalSparseMatrix() const;

    void addValue(int row, int col, T value);   // Добавить ненулевое значение
    T getValue(int row, int col) const;         // Получить значение по индексу
    void print() const;                         // Вывести все ненулевые элементы
    size_t getNonZeroCount() const;             // Получить количество ненулевых элементов
    SparseMatrix<T> transpose() const;          // Транспонирование матрицы

}; // class SparseMatrix


} // namespace matrix_lib