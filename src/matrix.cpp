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
