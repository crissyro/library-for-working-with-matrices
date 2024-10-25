#pragma once

#include "../matrix/matrix.hpp"

#define MIN_COUNT_BLOCK 2

namespace matrix_lib {

template<typename MatrixType>
class BlockMatrix {

private:
    size_t rows_;
    size_t cols_;
    size_t blockRows_;
    size_t blockCols_;
    std::unique_ptr<std::unique_ptr<Matrix<MatrixType>[]>[]> data_;

    void initMemory();
    void freeMemory();
    void copy(const BlockMatrix& other) noexcept;

public:
    inline size_t getRows() const noexcept { return rows_; }
    inline size_t getCols() const noexcept { return cols_; }

    inline size_t getBlockRows() const noexcept { return blockRows_; }
    inline size_t getBlockCols() const noexcept { return blockCols_; }

    Matrix<MatrixType>& getBlock(const size_t blockRow, const size_t blockCol) const;

    BlockMatrix();
    BlockMatrix(size_t rows, size_t cols);
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols);
    BlockMatrix(size_t rows, size_t cols, const Matrix<MatrixType>& matrix);
    BlockMatrix(const BlockMatrix& other);
    BlockMatrix(BlockMatrix&& other) noexcept;
    ~BlockMatrix() noexcept = default;

    BlockMatrix& operator=(const BlockMatrix& other);
    BlockMatrix& operator=(BlockMatrix&& other) noexcept;
    Matrix<MatrixType> operator()(const size_t blockRow, const size_t blockCol) const;
    BlockMatrix operator+(const BlockMatrix& other) const;
    BlockMatrix operator-(const BlockMatrix& other) const;
    BlockMatrix operator*(const BlockMatrix& other) const;
    BlockMatrix operator*(const MatrixType& scalar) const;
    bool operator==(const BlockMatrix& other) const;
    bool operator!=(const BlockMatrix& other) const;

    void printBlockMatrix() const;
};

template<typename MatrixType>
void BlockMatrix<MatrixType>::initMemory() {
    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    data_ = std::make_unique<std::unique_ptr<Matrix<MatrixType>[]>[]>(numBlocksRow);

    for (size_t i = 0; i < numBlocksRow; ++i) {
        data_[i] = std::make_unique<Matrix<MatrixType>[]>(numBlocksCol);
        for (size_t j = 0; j < numBlocksCol; ++j) 
            data_[i][j] = Matrix<MatrixType>(blockRows_, blockCols_);     
    }
}

template<typename MatrixType>
inline void BlockMatrix<MatrixType>::freeMemory() { 
    data_.reset(); 
    rows_ = 0;
    cols_ = 0;
    blockRows_ = 0;
    blockCols_ = 0;
}

template<typename MatrixType>
inline Matrix<MatrixType>& BlockMatrix<MatrixType>::getBlock(const size_t blockRow, const size_t blockCol) const {
    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    if (blockRow >= numBlocksRow || blockCol >= numBlocksCol || blockRow < MIN_COUNT_BLOCK || blockCol < MIN_COUNT_BLOCK)
        throw std::out_of_range("Block index out of range");
        
    return data_[blockRow][blockCol];
}

template<typename MatrixType>
void BlockMatrix<MatrixType>::copy(const BlockMatrix<MatrixType>& other) noexcept {
    if (this != &other) {
        freeMemory();
        
        rows_ = other.rows_;
        cols_ = other.cols_;
        blockRows_ = other.blockRows_;
        blockCols_ = other.blockCols_;
        
        initMemory();
        
        size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
        size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

        for (size_t i = 0; i < numBlocksRow; ++i) 
            for (size_t j = 0; j < numBlocksCol; ++j) 
                data_[i][j] = other.data_[i][j];
    }
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>::BlockMatrix() 
    : rows_(MIN_SIZE_MATRIX), cols_(MIN_SIZE_MATRIX),
      blockRows_(MIN_COUNT_BLOCK), blockCols_(MIN_COUNT_BLOCK) {
    initMemory();
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>::BlockMatrix(size_t rows, size_t cols) 
    : rows_(rows), cols_(cols),
      blockRows_(MIN_COUNT_BLOCK), blockCols_(MIN_COUNT_BLOCK) {
    initMemory();
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>::BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols) 
    : rows_(rows), cols_(cols),
      blockRows_(blockRows), blockCols_(blockCols) {
    initMemory();
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>::BlockMatrix(size_t rows, size_t cols, const Matrix<MatrixType>& matrix) 
    : rows_(rows), cols_(cols),
      blockRows_(MIN_COUNT_BLOCK), blockCols_(MIN_COUNT_BLOCK) {
    initMemory();

    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    for (size_t i = 0; i < numBlocksRow; ++i) 
        for (size_t j = 0; j < numBlocksCol; ++j) 
            data_[i][j] = matrix;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>::BlockMatrix(const BlockMatrix<MatrixType>& other) 
    : rows_(other.rows_), cols_(other.cols_), 
      blockRows_(other.blockRows_), blockCols_(other.blockCols_) {
    copy(other);
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>::BlockMatrix(BlockMatrix<MatrixType>&& other) noexcept
    : rows_(std::exchange(other.rows_, 0)), 
      cols_(std::exchange(other.cols_, 0)),
      blockRows_(std::exchange(other.blockRows_, 0)), 
      blockCols_(std::exchange(other.blockCols_, 0)),
      data_(std::move(other.data_)) {
    other.data_ = nullptr; 
}

template <typename MatrixType>
inline BlockMatrix<MatrixType>& BlockMatrix<MatrixType>::operator=(const BlockMatrix<MatrixType>& other) {
    if (this != &other) {
        BlockMatrix temp(other);  
        std::swap(*this, temp);   
    }

    return *this;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>& BlockMatrix<MatrixType>::operator=(BlockMatrix<MatrixType>&& other) noexcept {
    if (this != &other) {
        freeMemory();

        rows_ = std::exchange(other.rows_, 0);
        cols_ = std::exchange(other.cols_, 0);
        blockRows_ = std::exchange(other.blockRows_, 0);
        blockCols_ = std::exchange(other.blockCols_, 0);
        data_ = std::move(other.data_);

        other.data_ = nullptr;
    }

    return *this;
}

template<typename MatrixType>
inline Matrix<MatrixType> BlockMatrix<MatrixType>::operator()(const size_t blockRow, const size_t blockCol) const {
    return getBlock(blockRow, blockCol);
}

template<typename MatrixType>
BlockMatrix<MatrixType> BlockMatrix<MatrixType>::operator+(const BlockMatrix<MatrixType>& other) const {
    if (rows_!= other.rows_ || cols_!= other.cols_)
        throw std::invalid_argument("Matrices have different sizes");

    BlockMatrix result(rows_, cols_, blockRows_, blockCols_);template<typename MatrixType>

    for (size_t i = 0; i < numBlocksRow; ++i) {
        for (size_t j = 0; j < numBlocksCol; ++j) 
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
    }

    return result;
}

template<typename MatrixType>
BlockMatrix<MatrixType> BlockMatrix<MatrixType>::operator-(const BlockMatrix<MatrixType>& other) const {
    if (rows_!= other.rows_ || cols_!= other.cols_)
        throw std::invalid_argument("Matrices have different sizes");

    BlockMatrix result(rows_, cols_, blockRows_, blockCols_);

    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    for (size_t i = 0; i < numBlocksRow; ++i) {
        for (size_t j = 0; j < numBlocksCol; ++j) 
            result.data_[i][j] = data_[i][j] - other.data_[i][j];
    }

    return result;
}

template<typename MatrixType>
BlockMatrix<MatrixType> BlockMatrix<MatrixType>::operator*(const BlockMatrix<MatrixType>& other) const {
    if (cols_ != other.rows_)
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");

    BlockMatrix result(rows_, other.cols_, blockRows_, other.blockCols_);

    size_t numBlocksRowA = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksColA = (cols_ + blockCols_ - 1) / blockCols_;
    size_t numBlocksColB = (other.cols_ + other.blockCols_ - 1) / other.blockCols_;

    for (size_t i = 0; i < numBlocksRowA; ++i) {
        for (size_t j = 0; j < numBlocksColB; ++j) {
            for (size_t k = 0; k < numBlocksColA; ++k) {
                result.data_[i][j] += data_[i][k] * other.data_[k][j];
            }
        }
    }

    return result;
}

template<typename MatrixType>
BlockMatrix<MatrixType> BlockMatrix<MatrixType>::operator*(const MatrixType& scalar) const {
    BlockMatrix result(rows_, cols_, blockRows_, blockCols_);

    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    for (size_t i = 0; i < numBlocksRow; ++i) {
        for (size_t j = 0; j < numBlocksCol; ++j) 
            result.data_[i][j] = scalar * data_[i][j];
    }

    return result;
}

template<typename MatrixType>
bool BlockMatrix<MatrixType>::operator==(const BlockMatrix<MatrixType>& other) const {
    if (rows_!= other.rows_ || cols_!= other.cols_) return false;

    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    for (size_t i = 0; i < numBlocksRow; ++i) {
        for (size_t j = 0; j < numBlocksCol; ++j) 
            if (data_[i][j] != other.data_[i][j]) return false;
    }

    return true;
}

template<typename MatrixType>
bool BlockMatrix<MatrixType>::operator!=(const BlockMatrix<MatrixType>& other) const {
    return !(*this == other);
}

template<typename MatrixType>
void BlockMatrix<MatrixType>::printBlockMatrix() const {
    size_t numBlocksRow = (rows_ + blockRows_ - 1) / blockRows_;
    size_t numBlocksCol = (cols_ + blockCols_ - 1) / blockCols_;

    for (size_t i = 0; i < numBlocksRow; ++i) {
        for (size_t j = 0; j < numBlocksCol; ++j) {
            std::cout << "Block (" << i << ", " << j << "):\n";
            std::cout << data_[i][j] << "\n";  
        }
        std::cout << std::string(40, '-') << "\n";  
    }
}


} // namespace