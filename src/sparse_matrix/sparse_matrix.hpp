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
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        rowsIndexes = other.rowsIndexes;
        colsIndexes = other.colsIndexes;
        values = other.values;
    }

    return *this;
}

template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator=(SparseMatrix&& other) noexcept {
    if (this != &other) {
        rows_ = std::exchange(other.rows_, 0);
        cols_ = std::exchange(other.cols_, 0);
        rowsIndexes = std::move(other.rowsIndexes);
        colsIndexes = std::move(other.colsIndexes);
        values = std::move(other.values);
    }
    
    return *this;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) 
        throw std::invalid_argument("Matrices have different dimensions");
    
    SparseMatrix result(rows_, cols_);

    size_t i = 0;
    size_t j = 0;

    while (i < values.size() || j < other.values.size()) {
        if (i < values.size() && (j >= other.values.size() || rowsIndexes[i] < other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] < other.colsIndexes[j]))) {
            result.addValue(rowsIndexes[i], colsIndexes[i], values[i]);
            ++i;
        } else if (j < other.values.size() && (i >= values.size() || rowsIndexes[i] > other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] > other.colsIndexes[j]))) {
            result.addValue(other.rowsIndexes[j], other.colsIndexes[j], other.values[j]);
            ++j;
        } else {
            T sum = values[i] + other.values[j];
            if (sum != T(0)) result.addValue(rowsIndexes[i], colsIndexes[i], sum); 

            ++i;
            ++j;
        }
    }

    return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator-(const SparseMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) 
        throw std::invalid_argument("Matrices have different dimensions");
    

    SparseMatrix result(rows_, cols_);

    size_t i = 0;
    size_t j = 0;

    while (i < values.size() || j < other.values.size()) {
        if (i < values.size() && (j >= other.values.size() || rowsIndexes[i] < other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] < other.colsIndexes[j]))) {
            result.addValue(rowsIndexes[i], colsIndexes[i], values[i]);
            ++i;
        } else if (j < other.values.size() && (i >= values.size() || rowsIndexes[i] > other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] > other.colsIndexes[j]))) {
            result.addValue(other.rowsIndexes[j], other.colsIndexes[j], -other.values[j]);
            ++j;
        } else {
            T diff = values[i] - other.values[j];
            if (diff != T(0)) result.addValue(rowsIndexes[i], colsIndexes[i], diff);
    
            ++i;
            ++j;
        }
    }

    return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix& other) const {
    if (cols_ != other.rows_) 
        throw std::invalid_argument("Matrices have incompatible dimensions for multiplication");
    
    SparseMatrix result(rows_, other.cols_);

    for (size_t i = 0; i < values.size(); ++i) {
        int row = rowsIndexes[i];
        T value = values[i];

        for (size_t j = 0; j < other.values.size(); ++j) {
            if (other.rowsIndexes[j] == colsIndexes[i]) { 
                int col = other.colsIndexes[j];
                T product = value * other.values[j];
                result.addValue(row, col, result.getValue(row, col) + product);
            }
        }
    }

    return result;
}

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
inline size_t SparseMatrix<T>::getNonZeroCount() const { return values.size(); }

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