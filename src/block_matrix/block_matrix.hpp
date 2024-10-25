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

    Matrix& getBlock(const size_t blockRow, const size_t blockCol) const;

    BlockMatrix();
    BlockMatrix(size_t rows, size_t cols);
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols);
    BlockMatrix(size_t rows, size_t cols, const Matrix<MatrixType>& matrix);
    BlockMatrix(const BlockMatrix& other);
    BlockMatrix(BlockMatrix&& other) noexcept;
    ~BlockMatrix() noexcept = default;

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
inline Matrix<MatrixType>& getBlock(const size_t blockRow, const size_t blockCol) {
    if (blockRow >= blockRows_ || blockCol >=  blockCols_  || blockRow < MIN_COUNT_BLOCK || blockCol < MIN_COUNT_BLOCK)
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
            for (size_t j = 0; j < numBlocksCol; ++j) data_[i][j] = other.data_[i][j];
        
    }
}

template<typename MatrixType>
BlockMatrix<MatrixType>::BlockMatrix() : rows_(MIN_SIZE_MATRIX), cols_(MIN_SIZE_MATRIX),\
                               blockRows_(MIN_COUNT_BLOCK), blockCols_(MIN_COUNT_BLOCK) {
    initMemory();
}

template<typename MatrixType>
BlockMatrix<MatrixType>::BlockMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols),\
                               blockRows_(MIN_COUNT_BLOCK), blockCols_(MIN_COUNT_BLOCK) {
    initMemory();
}



}
