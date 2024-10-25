#pragma once

#include "../matrix/matrix.hpp"
#include <limits>

#define MIN_COUNT_BLOCK 2

#define MIN_VALUE(T) (std::numeric_limits<T>::min())

#define MAX_VALUE(T) (std::numeric_limits<T>::max())

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
    BlockMatrix& operator+=(const BlockMatrix& other);
    BlockMatrix& operator-=(const BlockMatrix& other);
    BlockMatrix& operator*=(const BlockMatrix& other);
    BlockMatrix& operator*=(const MatrixType& scalar);
    bool operator==(const BlockMatrix& other) const;
    bool operator!=(const BlockMatrix& other) const;
    void printBlockMatrix() const;
    void sumBlockMatrix(const BlockMatrix& other);
    void subBlockMatrix(const BlockMatrix& other);
    void mulBlockMatrix(const BlockMatrix& other);
    void mulBlockScalar(const MatrixType& scalar);
    BlockMatrix sumBlockMatrix(const BlockMatrix& mat1, const BlockMatrix& mat2) const;
    BlockMatrix subBlockMatrix(const BlockMatrix& mat1, const BlockMatrix& mat2) const;
    BlockMatrix mulBlockMatrix(const BlockMatrix& mat1, const BlockMatrix& mat2) const;
    BlockMatrix mulBlockScalar(const BlockMatrix& mat, const MatrixType& scalar) const;
    void transposeBlockMatrix();
    bool isSymmetric() const;
    bool isSquare() const;
    double frobeniusNorm() const;
    size_t getBlockCount() const;
    BlockMatrix concat(const BlockMatrix& other, bool horizontal = true) const;
    MatrixType findMaxElementBlockMamtrix() const noexcept;
    Matrix<MatrixType> findMaxElementBlockMamtrixBlock() const noexcept;
    MatrixType findMinElementBlockMatrix() const noexcept;
    Matrix<MatrixType> findMinElementBlockMatrixBlock() const noexcept;
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
inline BlockMatrix<MatrixType>& BlockMatrix<MatrixType>::operator+=(const BlockMatrix<MatrixType>& other) {
    (*this) = (*this) + other;
    return *this;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>& BlockMatrix<MatrixType>::operator-=(const BlockMatrix<MatrixType>& other) {
    (*this) = (*this) - other;
    return *this;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>& BlockMatrix<MatrixType>::operator*=(const BlockMatrix<MatrixType>& other) {
    (*this) = (*this) * other;
    return *this;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType>& BlockMatrix<MatrixType>::operator*=(const MatrixType& scalar) {
    (*this) = (*this) * scalar;
    return *this;
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

template<typename MatrixType>
inline void BlockMatrix<MatrixType>::sumBlockMatrix(const BlockMatrix<MatrixType>& other) { this += other; }

template<typename MatrixType>
inline void BlockMatrix<MatrixType>::subBlockMatrix(const BlockMatrix<MatrixType>& other) { this -= other; }

template<typename MatrixType>
inline void BlockMatrix<MatrixType>::mulBlockMatrix(const BlockMatrix<MatrixType>& other) { this *= other; }

template<typename MatrixType>
inline void BlockMatrix<MatrixType>::mulBlockScalar(const MatrixType& scalar) { this *= scalar; }

template<typename MatrixType>
inline BlockMatrix<MatrixType> BlockMatrix<MatrixType>::sumBlockMatrix(const BlockMatrix<MatrixType>& mat1, const BlockMatrix<MatrixType>& mat2) const {
    return mat1 + mat2;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType> BlockMatrix<MatrixType>::subBlockMatrix(const BlockMatrix<MatrixType>& mat1, const BlockMatrix<MatrixType>& mat2) const {
    return mat1 - mat2;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType> BlockMatrix<MatrixType>::mulBlockMatrix(const BlockMatrix<MatrixType>& mat1, const BlockMatrix<MatrixType>& mat2) const {
    return mat1 * mat2;
}

template<typename MatrixType>
inline BlockMatrix<MatrixType> BlockMatrix<MatrixType>::mulBlockScalar(const BlockMatrix<MatrixType>& mat, const MatrixType& scalar) const {
    return mat * scalar;
}

template <typename MatrixType>
bool BlockMatrix<MatrixType>::isSymmetric() const {
    if (rows_ != cols_) return false;

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = i + 1; j < cols_; ++j) 
            if (data_[i][j] != data_[j][i]) return false;
    }

    return true;
}

template <typename MatrixType>
bool BlockMatrix<MatrixType>::isSquare() const {
    return rows_ == cols_;
}

template<typename MatrixType>
double BlockMatrix<MatrixType>::frobeniusNorm() const {
    double sum = 0.0;

    for (size_t i = 0; i < getBlockCount(); ++i) 
        for (size_t j = 0; j < getBlockCount(); ++j) sum += data_[i][j].frobeniusNorm(); 
        
    return std::sqrt(sum);
}

template <typename MatrixType>
size_t BlockMatrix<MatrixType>::getBlockCount() const {
    return (rows_ + blockRows_ - 1) / blockRows_ * (cols_ + blockCols_ - 1) / blockCols_;
}

template <typename MatrixType>
void BlockMatrix<MatrixType>::transposeBlockMatrix() {
    if (rows_ != cols_)
        throw std::invalid_argument("Only square block matrices can be transposed.");

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = i + 1; j < cols_; ++j) 
            std::swap(data_[i][j], data_[j][i]);
    }
}

template <typename MatrixType>
BlockMatrix<MatrixType> BlockMatrix<MatrixType>::concat(const BlockMatrix<MatrixType>& other, bool horizontal) const {
    if (horizontal) {

        if (rows_ != other.rows_)
            throw std::invalid_argument("Row counts must match for horizontal concatenation.");

        BlockMatrix result(rows_, cols_ + other.cols_, blockRows_, blockCols_);

        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) 
                result.data_[i][j] = data_[i][j];
            
            for (size_t j = 0; j < other.cols_; ++j) 
                result.data_[i][j + cols_] = other.data_[i][j];
        }

        return result;
        
    } else {

        if (cols_ != other.cols_)
            throw std::invalid_argument("Column counts must match for vertical concatenation.");

        BlockMatrix result(rows_ + other.rows_, cols_, blockRows_, blockCols_);

        for (size_t i = 0; i < rows_; ++i) 
            for (size_t j = 0; j < cols_; ++j) result.data_[i][j] = data_[i][j];
            
        
        for (size_t i = 0; i < other.rows_; ++i) 
            for (size_t j = 0; j < cols_; ++j) result.data_[i + rows_][j] = other.data_[i][j];
            
        
        return result;
    }
}

template<typename MatrixType>
MatrixType findMaxElementBlockMamtrix() noexcept {
    MatrixType maxElement = MIN_VALUE(MatrixType);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            MatrixType maxInBlock = data_[i][j].findMaxElement()
            if (maxInBlock > maxElement) maxElement = maxInBlock;
        }
    }

    return maxElement;
}

template<typename MatrixType>
MatrixType findMinElementBlockMatrix() noexcept {
    MatrixType minElement = MAX_VALUE(MatrixType);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            MatrixType minInBlock = data_[i][j].findMinElement()
            if (minInBlock < minElement) minElement = minInBlock;
        }
    }

    return minElement;
}

template<typename MatrixType>
Matrix<MatrixType> BlockMatrix<MatrixType>::findMaxElementBlockMamtrixBlock() const noexcept {
    Matrix<MatrixType> res = data_[0][0];
    MatrixType resMaxElement = data_[0][0].findMaxElement();

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            Matrix<MatrixType> curBlock = data_[i][j];
            MatrixType curMaxElement = curBlock.findMaxElement();
            if (curMaxElement > resMaxElement) {
                res = curBlock;
                resMaxElement = curMaxElement;
            }
        }
    }

    return res;
}


template<typename MatrixType>
Matrix<MatrixType> BlockMatrix<MatrixType>::findMinElementBlockMatrixBlock() const noexcept {
    Matrix<MatrixType> res = data_[0][0];
    MatrixType resMinElement = data_[0][0].findMinElement();

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            Matrix<MatrixType> curBlock = data_[i][j];
            MatrixType curMinElement = curBlock.findMinElement();
            if (curMinElement < resMinElement) {
                res = curBlock;
                resMinElement = curMinElement;
            }
        }
    }

    return res;
}

} // namespace