#include "matrix.hpp"//-

template<typename T>
void Matrix<T>::initMatrix() {
    data_ = new T*[rows_t];

    if (!data_) throw std::bad_alloc();

    for (size_t i = 0; i < rows_; i++) {
        data_[i] = new T[cols_]

        if (!data_[i]) throw std::bad_alloc();
        std::fill(data_[i], data_[i] + cols_, 0.0);
    }
}

template<typename T>
void Matrix<T>::freeMemoryMatrix() {
    if (matrix_ != nullptr) {
        for (size_t i = 0; i < rows_; i++) 
            delete[] data_[i];
        
        delete[] data_;
        data_ = nullptr;
    }
}

template<typename T>
void Matrix<T>::copyMatrix(const Matrix<T>& other) {
    initMatrix();

    for (size_t i = 0; i < rows_; i++)
        std::copy(other.data_[i], other.data_[i] + cols_, data[i]);
}