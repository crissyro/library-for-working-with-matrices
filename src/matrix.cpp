#include "matrix.hpp"//-

template<typename T>
void Matrix<T>::initMatrix() {
    data_ = new T*[rows_];

    if (!data_) throw std::bad_alloc();

    for (size_t i = 0; i < rows_; i++) {
        data_[i] = new T[cols_];

        if (!data_[i]) throw std::bad_alloc();

        std::fill(data_[i], data_[i] + cols_, 0.0);
    }
}

template<typename T>
void Matrix<T>::freeMemoryMatrix() {
    if (data_ != nullptr) {
        for (size_t i = 0; i < rows_; i++) 
            delete[] data_[i];
        
        delete[] data_;
        data_ = nullptr;
    }

    rows_ = 0;
    cols_ = 0;
}

template<typename T>
void Matrix<T>::copyMatrix(const Matrix<T>& other) {
    initMatrix();

    for (size_t i = 0; i < rows_; i++)
        std::copy(other.data_[i], other.data_[i] + cols_, data_[i]);
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols): rows_(rows), cols_(cols), data_{nullptr} {
    initMatrix();
}

template<typename T>
Matrix<T>::Matrix(): rows_(MIN_SIZE_MATRIX), cols_(MIN_SIZE_MATRIX), data_{nullptr}{
    initMatrix();
}

template<typename T>
Matrix<T>::Matrix(const size_t size) {
    Matrix<T>::Matrix(size, size);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other): rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    initMatrix();
    copyMatrix(other);
}

template<typename T>
Matrix<T>::Matrix(Matrix&& other): rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.freeMemoryMatrix();
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, T** array): rows_(rows), cols_(cols), data_(array) { }

template<typename T>
Matrix<T>::~Matrix() { freeMemoryMatrix(); }

template<typename T>
void Matrix<T>::printMatrix() const {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (j == cols - 1)
                std::cout << data_[i][j] << std::endl;
            else
                std::cout << data_[i][j] << " ";
        }
    }
}