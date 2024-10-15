#include "matrix.hpp"//-

template<typename T>
void Matrix<T>::initMatrix() noexcept {
    data_ = std::make_unique<std::unique_ptr<T[]>[]>(rows_);
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = std::make_unique<T[]>(cols_);
        std::fill(data_[i].get(), data_[i].get() + cols_, static_cast<T>(0)); 
    }
}

template<typename T>
inline void Matrix<T>::freeMemoryMatrix() noexcept {
    data_.reset();
    rows_ = 0;
    cols_ = 0;
}

template<typename T>
void Matrix<T>::copyMatrix(const Matrix<T>& other) noexcept {
    rows_ = other.rows_;
    cols_ = other.cols_;

    initMatrix();

    for (size_t i = 0; i < rows_; ++i) 
        std::copy(other.data_[i].get(), other.data_[i].get() + cols_, data_[i].get());
}

template <typename T>
inline size_t Matrix<T>::getRows() const noexcept { return rows_; }

template <typename T>
inline size_t Matrix<T>::getCols() const noexcept { return cols_; }

template<typename T>
inline Matrix<T>::Matrix() noexcept : rows_(MIN_SIZE_MATRIX), cols_(MIN_SIZE_MATRIX) {
    initMatrix();
}

template<typename T>
inline Matrix<T>::Matrix(const size_t size) noexcept : rows_(size), cols_(size) {
    initMatrix();
}

template<typename T>
inline Matrix<T>::Matrix(const size_t rows, const size_t cols) noexcept : rows_(rows), cols_(cols) {
    initMatrix();
}

template<typename T>
inline Matrix<T>::Matrix(const size_t rows, const size_t cols, T** array) noexcept : rows_(rows), cols_(cols) {
    initMatrix();
    for (size_t i = 0; i < rows_; ++i) 
        std::copy(array[i], array[i] + cols_, data_[i].get());
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix<T>& other) noexcept {
    copyMatrix(other);
}

template<typename T>
inline Matrix<T>::Matrix(Matrix<T>&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
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
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    *this = *this + *other
    return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    *this = *this - *other
    return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    *this = *this * *other
    return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const T scalar) {
    *this = *this * scalar
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows_; ++i) {
        for (size_t j = 0; j < matrix.cols_; ++j) 
            os << matrix.data_[i][j] << " ";
        os << std::endl;
    }

    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows_; ++i) {
        for (size_t j = 0; j < matrix.cols_; ++j) 
            is >> matrix.data_[i][j];
    }

    return is;
}

template<typename T>
inline bool Matrix<T>::isEqualMatrix(const Matrix& other) const noexcept {
    return *this == *other
}

template<typename T>
inline bool Matrix<T>::isSquareMatrix() const noexcept {
    return rows_ == columns_;
} 

template<typename T>
bool Matrix<T>::isSymetricMatrix() const noexcept {
    if (!isSquareMatrix()) return false;

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < i; ++j) 
            if (data_[i][j] != data_[j][i]) return false;
    }

    return true;
}

template <typename T>
bool Matrix<T>::isIdentityMatrix() const noexcept {
    if (!isSquareMatrix()) return false;

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            if (i == j && data_[i][j] != static_cast<T>(1)) 
                return false;

            else if (i != j && data_[i][j] != static_cast<T>(0)) 
                return false;
    }

    return true;
}

template <typename T>
bool Matrix<T>::isZeroMatrix() const noexcept {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            if (data_[i][j] != static_cast<T>(0)) return false;
    }

    return true;
}
template <typename T>
bool Matrix<T>::isSingular() const noexcept {
    if (!isSquareMatrix()) return false;

    T determinant = determinant();

    return determinant == static_cast<T>(0);
}

template <typename T>
bool Matrix<T>::isDiagonalMatrix() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            if (i != j && data_[i][j] != static_cast<T>(0)) 
                return false;

            else if (i == j && data_[i][j] == static_cast<T>(0)) 
                return false;
    }

    return true;
}

template<typename T>
inline bool Matrix<T>::isTriangularMatrix() const {
    return isUpperTriangularMatrix() || isLowerTriangularMatrix();
}

template<typename T>
bool Matrix<T>::isUpperTriangularMatrix() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < i; ++j) 
            if (data_[i][j] != static_cast<T>(0)) return false;
    }

    return true;
}

template<typename T>
bool Matrix<T>::isLowerTriangularMatrix() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = i + 1; j < cols_; ++j) 
            if (data_[i][j]!= static_cast<T>(0)) return false;
    }

    return true;
}

template<typename T>
bool Matrix<T>::isOrthogonalMatrix() const {
    if (!isSquareMatrix()) return false;

    Matrix<T> transpose = this->transpose();
    Matrix<T> identity = Matrix<T>::identity(rows_);

    return (*this * transpose == identity) || (transpose * this == identity);
}

template<typename T>
bool Matrix<T>::isNormalMatrix() const {
    if (!isSquareMatrix()) return false;

    Matrix<T> transpose = this->transposeMatrix();
    Matrix<T> identity = Matrix<T>::makeIdentityMatrix(rows_);

    return (*this * transpose == transpose * this) && (*this * identity == identity);
}

template<typename T>
Matrix<T> Matrix<T>::makeIdentityMatrix(const size_t size = 2) const {
    if (size < MIN_SIZE_MATRIX)
        throw std::invalid_argument("Matrix size must be greater than or equal to " + std::to_string(MIN_SIZE_MATRIX));

    Matrix<T> result(size, size);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result(i, j) = (i == j)? static_cast<T>(1) : static_cast<T>(0);
        }
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::makeZeroMatrix(const size_t rows = 2, const size_t cols = 2) const {
    if (rows < MIN_SIZE_MATRIX || cols < MIN_SIZE_MATRIX)
        throw std::invalid_argument("Matrix size must be greater than or equal to " + std::to_string(MIN_SIZE_MATRIX));

    Matrix<T> result(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = static_cast<T>(0);
        }
    }

    return result;
}

template<typename T>
void Matrix<T>::setZeroMatrix() noexcept {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            data_[i][j] = static_cast<T>(0);
    }
}

template<typename T>
void Matrix<T>::setIdentityMatrix() {
    if (!isSquareMatrix())
        throw std::error_condition("Matrix must be square");

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            data_[i][j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
    }
}

template<typename T>
void Matrix<T>::setDiagonalizable() {
    if (!isSquareMatrix())
        throw std::error_condition("Matrix must be square");

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (data_[i][j] != 0)
                data_[i][j] = static_cast<T>(0);
            
            else if (i == j && data_[i][j] == 0)
                data_[i][j] = static_cast<T>(1);
        }
    }
}

template <typename T>
void Matrix<T>::setNormalMatrix() {
    if (!isSquareMatrix())
        throw std::error_condition("Matrix must be square");

    Matrix<T> transpose = this->transposeMatrix();
    Matrix<T> identity = Matrix<T>::makeIdentityMatrix(rows_);

    if (*this * transpose != transpose * this || *this * identity != identity)
        throw std::error_condition("Matrix is not normal");
}

template<typename T>
void Matrix<T>::setOrthogonalMatrix() {
    if (!isSquareMatrix())
        throw std::error_condition("Matrix must be square");

    Matrix<T> transpose = this->transposeMatrix();
    Matrix<T> identity = Matrix<T>::makeIdentityMatrix(rows_);

    if ((*this * transpose != identity && *this * transpose != -identity) || (*this * identity != identity && *this * identity != -identity))
        throw std::error_condition("Matrix is not orthogonal");
}

template<typename T>
void Matrix<T>::setDiagonalMatrix(const T* diagonalArray) {
    if (!isSquareMatrix())
        throw std::error_condition("Matrix must be square");

    if (diagonalArray == nullptr || sizeof(diagonalArray) / sizeof(*diagonalArray) != rows_)
        throw std::error_argument("Len array must be equal with matrix rows number")

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] = (i == j)? diagonalArray[i] : static_cast<T>(0);
        }
    }
}

