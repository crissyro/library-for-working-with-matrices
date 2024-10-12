#include "matrix.hpp"//-

template<typename T>
void Matrix<T>::initMatrix() {
    data_ = std::make_unique<std::unique_ptr<T[]>[]>(rows_);
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = std::make_unique<T[]>(cols_);
        std::fill(data_[i].get(), data_[i].get() + cols_, static_cast<T>(0)); 
    }
}

template<typename T>
void Matrix<T>::freeMemoryMatrix() noexcept {
    data_.reset();
    rows_ = 0;
    cols_ = 0;
}

template<typename T>
void Matrix<T>::copyMatrix(const Matrix<T>& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;

    initMatrix();

    for (size_t i = 0; i < rows_; ++i) 
        std::copy(other.data_[i].get(), other.data_[i].get() + cols_, data_[i].get());
}

template<typename T>
Matrix<T>::Matrix() noexcept : rows_(MIN_SIZE_MATRIX), cols_(MIN_SIZE_MATRIX) {
    initMatrix();
}

template<typename T>
Matrix<T>::Matrix(const size_t size) noexcept : rows_(size), cols_(size) {
    initMatrix();
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols) noexcept : rows_(rows), cols_(cols) {
    initMatrix();
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, T** array) noexcept : rows_(rows), cols_(cols) {
    initMatrix();
    for (size_t i = 0; i < rows_; ++i) 
        std::copy(array[i], array[i] + cols_, data_[i].get());
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) noexcept {
    copyMatrix(other);
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
    other.rows_ = 0;
    other.cols_ = 0;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        freeMemoryMatrix();
        copyMatrix(other);
    }

    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) return false;

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            if (data_[i][j] != other.data_[i][j]) return false;
    }

    return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (rows_!= other.rows_ || cols_!= other.cols_)
        throw std::invalid_argument("Matrices have different dimensions");

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (rows_!= other.rows_ || cols_!= other.cols_)
        throw std::invalid_argument("Matrices have different dimensions");

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            result.data_[i][j] = data_[i][j] - other.data_[i][j];
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols_!= other.rows_)
        throw std::invalid_argument("Matrices have incompatible dimensions for multiplication");

    Matrix result(rows_, other.cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < other.cols_; ++j) {
            result.data_[i][j] = static_cast<T>(0);
            for (size_t k = 0; k < cols_; ++k)
                result.data_[i][j] += data_[i][k] * other.data_[k][j];
        }
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T scalar) const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            result.data_[i][j] = data_[i][j] * scalar;
    }

    return result;
}

template<typename T>
T& Matrix<T>::operator()(const size_t row, const size_t col) {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix index out of range");

    return data_[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(const size_t row, const size_t col) const {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix index out of range");

    return data_[row][col];
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other);

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other);

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other);

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T scalar);