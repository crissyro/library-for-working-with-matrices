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
    SparseMatrix() : rows_(0), cols_(0) {};
    SparseMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {};
    SparseMatrix(const SparseMatrix& other) = default;
    SparseMatrix(const SparseMatrix&& other) noexcept = default;
    ~SparseMatrix() = default;

    size_t getRows() const { return rows_; }
    size_t getCols() const { return cols_; }

    SparseMatrix& operator=(const SparseMatrix& other);
    SparseMatrix& operator=(SparseMatrix&& other) noexcept;
    SparseMatrix operator+(const SparseMatrix& other) const;
    SparseMatrix operator-(const SparseMatrix& other) const;
    SparseMatrix operator*(const SparseMatrix& other) const;
    SparseMatrix operator*(const T scalar) const;
    SparseMatrix& operator+=(const SparseMatrix& other);
    SparseMatrix& operator-=(const SparseMatrix& other);
    SparseMatrix& operator*=(const SparseMatrix& other);
    bool operator==(const SparseMatrix& other) const;
    bool operator!=(const SparseMatrix& other) const;

    bool isZeroSparseMatrix() const;
    bool isSquareSparseMatrix() const;
    bool isIdentitySparseMatrix() const;
    bool isDiagonalSparseMatrix() const;

    void addValue(const size_t row, const size_t col, const T value);   // Добавить ненулевое значение
    T getValue(const size_t row, const size_t col) const;         // Получить значение по индексу
    void printSparseMatrix() const;                         // Вывести все ненулевые элементы
    size_t getNonZeroCount() const;             // Получить количество ненулевых элементов
    SparseMatrix<T> transpose() const;          // Транспонирование матрицы

}; // class SparseMatrix

template <typename T>
inline SparseMatrix<T> SparseMatrix<T>::operator*(const T scalar) const {
    SparseMatrix result(*this);

    for (T& element : result.values) element *= scalar;
    
    return result;
}

template <typename T>
void SparseMatrix<T>::addValue(const size_t row, const size_t col, const T value) {
    if (row >= rows_ || col >= columns_)
        throw std::out_of_range("Index out of range");
    
    if (value != static_cast<T>(0)) {
        rowsIndexes.push_back(row);
        colsIndexes.push_back(col);
        values.push_back(value);
    }
}

template<typename T>
T SparseMatrix<T>::getValue(const size_t row, const size_t col) const {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Index out of range");

    for (size_t i = 0; i < values.size(); ++i) 
        if (rowsIndexes[i] == row && colsIndexes[i] == col) return values[i];
    
    return static_cast<T>(0);
}

template <typename T>
void SparseMatrix<T>::printSparseMatrix() const {
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << "Value: " << values[i] << " at (" 
                  << rowsIndexes[i] << ", " << colsIndexes[i] << ")\n";
    }
}

template <typename T>
inline bool SparseMatrix<T>::isZeroSparseMatrix() const { return values.empty(); }

template <typename T>
inline bool SparseMatrix<T>::isSquareSparseMatrix() const { return rows_ == cols_; }

template <typename T>
SparseMatrix<T> SparseMatrix<T>::transpose() const {
    SparseMatrix result(cols_, rows_);

    result.rowsIndexes = colsIndexes;
    result.colsIndexes = rowsIndexes;
    result.values = values;

    return result;
}


} // namespace matrix_lib