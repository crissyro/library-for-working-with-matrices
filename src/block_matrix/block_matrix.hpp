#pragma once

#include "../matrix/matrix.hpp"


namespace matrix_lib {

template<typename MatrixType>
class BlockMatrix {

private:
    size_t rows_;
    size_t cols_;
    size_t blockRows_;
    size_t blockCols_;
    std::unique_ptr<std::unique_ptr<Matrix<MatrixType>[]>[]> data_;

public:
    inline size_t getRows() const noexcept { return rows_; }
    inline size_t getCols() const noexcept { return cols_; }

    inline size_t getBlockRows() const noexcept { return blockRows_; }
    inline size_t getBlockCols() const noexcept { return blockCols_; }

    inline Matrix<MatrixType>& getBlock(const size_t blockRow, const size_t blockCol) const;

    BlockMatrix();
    BlockMatrix(size_t rows, size_t cols);
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols);
    BlockMatrix(size_t rows, size_t cols, const Matrix<MatrixType>& matrix);
    BlockMatrix(const BlockMatrix& other);
    BlockMatrix(BlockMatrix&& other) noexcept;
    ~BlockMatrix() noexcept = default;

};

}
