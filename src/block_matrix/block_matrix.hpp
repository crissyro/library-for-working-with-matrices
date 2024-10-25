#pragma once

#include "../matrix/matrix.hpp"
#include <limits>

#define MIN_COUNT_BLOCK 2

#define MIN_VALUE(T) (std::numeric_limits<T>::min())

#define MAX_VALUE(T) (std::numeric_limits<T>::max())

namespace matrix_lib {

/**
 * @brief Класс для работы с блочными матрицами.
 * 
 * Класс `BlockMatrix` предназначен для представления и управления матрицами,
 * разбитыми на блоки, что позволяет эффективно выполнять операции над большими матрицами.
 * 
 * @tparam MatrixType Тип данных, используемый для элементов матрицы.
 */
template<typename MatrixType>
class BlockMatrix {

private:
    size_t rows_;                      ///< Общее количество строк в матрице.
    size_t cols_;                      ///< Общее количество столбцов в матрице.
    size_t blockRows_;                 ///< Количество строк в одном блоке.
    size_t blockCols_;                 ///< Количество столбцов в одном блоке.
    std::unique_ptr<std::unique_ptr<Matrix<MatrixType>[]>[]> data_; ///< Указатель на блоки матриц.

    /**
     * @brief Инициализация памяти для хранения блоков матрицы.
     * 
     * Метод выделяет необходимую память для хранения блоков матрицы, 
     * устанавливая размерность блоков в соответствии с заданными параметрами.
     */
    void initMemory();

    /**
     * @brief Освобождение памяти, занятой блоками матрицы.
     * 
     * Метод освобождает память, ранее выделенную для хранения блоков матрицы, 
     * предотвращая утечки памяти.
     */
    void freeMemory();

    /**
     * @brief Копирование данных из другой блочной матрицы.
     * @param other Блочная матрица для копирования.
     * 
     * Метод копирует данные из указанной блочной матрицы в текущую матрицу,
     * сохраняя размеры и элементы.
     */
    void copy(const BlockMatrix& other) noexcept;

public:
    /**
     * @brief Возвращает количество строк в блочной матрице.
     * @return Количество строк.
     */
    inline size_t getRows() const noexcept { return rows_; }

    /**
     * @brief Возвращает количество столбцов в блочной матрице.
     * @return Количество столбцов.
     */
    inline size_t getCols() const noexcept { return cols_; }

    /**
     * @brief Возвращает количество строк в блоке матрицы.
     * @return Количество строк в блоке.
     */
    inline size_t getBlockRows() const noexcept { return blockRows_; }

    /**
     * @brief Возвращает количество столбцов в блоке матрицы.
     * @return Количество столбцов в блоке.
     */
    inline size_t getBlockCols() const noexcept { return blockCols_; }

    /**
     * @brief Получение указанного блока матрицы.
     * @param blockRow Индекс строки блока.
     * @param blockCol Индекс столбца блока.
     * @return Ссылка на матрицу, представляющую указанный блок.
     */
    Matrix<MatrixType>& getBlock(const size_t blockRow, const size_t blockCol) const;

    /**
     * @brief Конструктор по умолчанию.
     * 
     * Создает пустую блочную матрицу с нулевыми размерами.
     */
    BlockMatrix();

    /**
     * @brief Конструктор для создания блочной матрицы с заданным количеством строк и столбцов.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     * 
     * Создает блочную матрицу с указанным количеством строк и столбцов, 
     * устанавливая размеры блоков по умолчанию.
     */
    BlockMatrix(size_t rows, size_t cols);

    /**
     * @brief Конструктор для создания блочной матрицы с заданным количеством строк, столбцов и блоков.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     * @param blockRows Количество строк в блоке.
     * @param blockCols Количество столбцов в блоке.
     * 
     * Создает блочную матрицу с указанным количеством строк, столбцов и размерами блоков.
     */
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols);

    /**
     * @brief Конструктор для создания блочной матрицы на основе существующей матрицы.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     * @param matrix Исходная матрица для инициализации блочной матрицы.
     * 
     * Создает блочную матрицу, используя данные из заданной матрицы.
     */
    BlockMatrix(size_t rows, size_t cols, const Matrix<MatrixType>& matrix);

    /**
     * @brief Конструктор копирования.
     * @param other Другая блочная матрица для копирования.
     * 
     * Создает новую блочную матрицу, копируя данные из указанной матрицы.
     */
    BlockMatrix(const BlockMatrix& other);

    /**
     * @brief Конструктор перемещения.
     * @param other Другая блочная матрица для перемещения.
     * 
     * Перемещает данные из указанной матрицы в новую блочную матрицу.
     */
    BlockMatrix(BlockMatrix&& other) noexcept;

    /**
     * @brief Деструктор класса BlockMatrix.
     * 
     * Освобождает память, выделенную под блочную матрицу, 
     * гарантируя корректное удаление всех данных.
     */
    ~BlockMatrix() noexcept = default;

    /**
     * @brief Оператор присваивания.
     * @param other Другая блочная матрица для присваивания.
     * @return Ссылка на текущий объект.
     * 
     * Присваивает значения другой блочной матрицы текущему объекту,
     * освобождая предыдущие данные при необходимости.
     */
    BlockMatrix& operator=(const BlockMatrix& other);

    /**
     * @brief Оператор перемещения.
     * @param other Другая блочная матрица для перемещения.
     * @return Ссылка на текущий объект.
     * 
     * Перемещает данные из указанной блочной матрицы в текущий объект,
     * освобождая память, занимаемую старым объектом.
     */
    BlockMatrix& operator=(BlockMatrix&& other) noexcept;

    /**
     * @brief Получение значения из указанного блока матрицы.
     * @param blockRow Индекс строки блока.
     * @param blockCol Индекс столбца блока.
     * @return Блок матрицы по заданным индексам.
     * 
     * Возвращает блок матрицы, соответствующий заданным индексам.
     */
    Matrix<MatrixType> operator()(const size_t blockRow, const size_t blockCol) const;

    /**
     * @brief Оператор сложения блочных матриц.
     * @param other Другая блочная матрица для сложения.
     * @return Результирующая блочная матрица, полученная в результате сложения.
     * 
     * Складывает текущую блочную матрицу с указанной и возвращает новую блочную матрицу.
     */
    BlockMatrix operator+(const BlockMatrix& other) const;

    /**
     * @brief Оператор вычитания блочных матриц.
     * @param other Другая блочная матрица для вычитания.
     * @return Результирующая блочная матрица, полученная в результате вычитания.
     * 
     * Вычитает указанную блочную матрицу из текущей и возвращает новую блочную матрицу.
     */
    BlockMatrix operator-(const BlockMatrix& other) const;

    /**
     * @brief Оператор умножения блочных матриц.
     * @param other Другая блочная матрица для умножения.
     * @return Результирующая блочная матрица, полученная в результате умножения.
     * 
     * Умножает текущую блочную матрицу на указанную и возвращает новую блочную матрицу.
     */
    BlockMatrix operator*(const BlockMatrix& other) const;

    /**
     * @brief Оператор умножения блочной матрицы на скаляр.
     * @param scalar Скалярное значение для умножения.
     * @return Результирующая блочная матрица, полученная в результате умножения.
     * 
     * Умножает текущую блочную матрицу на указанное скалярное значение и возвращает новую блочную матрицу.
     */
    BlockMatrix operator*(const MatrixType& scalar) const;

    /**
     * @brief Оператор сложения с присваиванием.
     * @param other Другая блочная матрица для сложения.
     * @return Ссылка на текущий объект.
     * 
     * Складывает указанную блочную матрицу с текущей и обновляет текущий объект.
     */
    BlockMatrix& operator+=(const BlockMatrix& other);

    /**
     * @brief Оператор вычитания с присваиванием.
     * @param other Другая блочная матрица для вычитания.
     * @return Ссылка на текущий объект.
     * 
     * Вычитает указанную блочную матрицу из текущей и обновляет текущий объект.
     */
    BlockMatrix& operator-=(const BlockMatrix& other);

    /**
     * @brief Оператор умножения с присваиванием.
     * @param other Другая блочная матрица для умножения.
     * @return Ссылка на текущий объект.
     * 
     * Умножает текущую блочную матрицу на указанную и обновляет текущий объект.
     */
    BlockMatrix& operator*=(const BlockMatrix& other);

    /**
     * @brief Оператор умножения с присваиванием на скаляр.
     * @param scalar Скалярное значение для умножения.
     * @return Ссылка на текущий объект.
     * 
     * Умножает текущую блочную матрицу на указанное скалярное значение и обновляет текущий объект.
     */
    BlockMatrix& operator*=(const MatrixType& scalar);

    /**
     * @brief Оператор сравнения блочных матриц на равенство.
     * @param other Другая блочная матрица для сравнения.
     * @return true, если матрицы равны, иначе false.
     * 
     * Сравнивает текущую блочную матрицу с указанной на предмет равенства.
     */
    bool operator==(const BlockMatrix& other) const;

    /**
     * @brief Оператор сравнения блочных матриц на неравенство.
     * @param other Другая блочная матрица для сравнения.
     * @return true, если матрицы не равны, иначе false.
     * 
     * Сравнивает текущую блочную матрицу с указанной на предмет неравенства.
     */
    bool operator!=(const BlockMatrix& other) const;

    /**
     * @brief Печать блочной матрицы в стандартный поток.
     * 
     * Выводит содержимое блочной матрицы на экран, форматируя данные 
     * для удобного восприятия.
     */
    void printBlockMatrix() const;

    /**
     * @brief Сложение с другой блочной матрицей.
     * @param other Блочная матрица для сложения.
     * 
     * Метод выполняет сложение текущей блочной матрицы с указанной.
     */
    void sumBlockMatrix(const BlockMatrix& other);

    /**
     * @brief Вычитание другой блочной матрицы.
     * @param other Блочная матрица для вычитания.
     * 
     * Метод выполняет вычитание указанной блочной матрицы из текущей.
     */
    void subBlockMatrix(const BlockMatrix& other);

    /**
     * @brief Умножение на другую блочную матрицу.
     * @param other Блочная матрица для умножения.
     * 
     * Метод выполняет умножение текущей блочной матрицы на указанную.
     */
    void mulBlockMatrix(const BlockMatrix& other);

    /**
     * @brief Умножение на скаляр.
     * @param scalar Скалярное значение для умножения.
     * 
     * Метод выполняет умножение текущей блочной матрицы на заданное 
     * скалярное значение.
     */
    void mulBlockScalar(const MatrixType& scalar);

    /**
     * @brief Сложение двух блочных матриц.
     * @param mat1 Первая блочная матрица.
     * @param mat2 Вторая блочная матрица.
     * @return Результирующая блочная матрица, полученная в результате сложения.
     * 
     * Метод выполняет сложение двух указанных блочных матриц.
     */
    BlockMatrix sumBlockMatrix(const BlockMatrix& mat1, const BlockMatrix& mat2) const;

    /**
     * @brief Вычитание двух блочных матриц.
     * @param mat1 Первая блочная матрица.
     * @param mat2 Вторая блочная матрица.
     * @return Результирующая блочная матрица, полученная в результате вычитания.
     * 
     * Метод выполняет вычитание второй блочной матрицы из первой.
     */
    BlockMatrix subBlockMatrix(const BlockMatrix& mat1, const BlockMatrix& mat2) const;

    /**
     * @brief Умножение двух блочных матриц.
     * @param mat1 Первая блочная матрица.
     * @param mat2 Вторая блочная матрица.
     * @return Результирующая блочная матрица, полученная в результате умножения.
     * 
     * Метод выполняет умножение двух указанных блочных матриц.
     */
    BlockMatrix mulBlockMatrix(const BlockMatrix& mat1, const BlockMatrix& mat2) const;

    /**
     * @brief Умножение блочной матрицы на скаляр.
     * @param mat Блочная матрица для умножения.
     * @param scalar Скалярное значение для умножения.
     * @return Результирующая блочная матрица, полученная в результате умножения.
     * 
     * Метод выполняет умножение указанной блочной матрицы на заданное 
     * скалярное значение.
     */
    BlockMatrix mulBlockScalar(const BlockMatrix& mat, const MatrixType& scalar) const;

    /**
     * @brief Транспонирование блочной матрицы.
     * 
     * Метод выполняет транспонирование текущей блочной матрицы.
     */
    void transposeBlockMatrix();

    /**
     * @brief Проверка на симметричность блочной матрицы.
     * @return true, если матрица симметрична, иначе false.
     * 
     * Метод проверяет, является ли текущая блочная матрица симметричной.
     */
    bool isSymmetric() const;

    /**
     * @brief Проверка, является ли блочная матрица квадратной.
     * @return true, если матрица квадратная, иначе false.
     * 
     * Метод проверяет, является ли текущая блочная матрица квадратной.
     */
    bool isSquare() const;

    /**
     * @brief Вычисление нормы Фробениуса блочной матрицы.
     * @return Значение нормы Фробениуса.
     * 
     * Метод вычисляет норму Фробениуса текущей блочной матрицы.
     */
    double frobeniusNorm() const;

    /**
     * @brief Получение количества блоков в блочной матрице.
     * @return Количество блоков.
     * 
     * Метод возвращает количество блоков в текущей блочной матрице.
     */
    size_t getBlockCount() const;

    /**
     * @brief Конкатенация двух блочных матриц.
     * @param other Другая блочная матрица для конкатенации.
     * @param horizontal Если true, конкатенирует горизонтально, иначе вертикально.
     * @return Результирующая блочная матрица после конкатенации.
     * 
     * Метод выполняет конкатенацию текущей блочной матрицы с указанной 
     * матрицей в зависимости от значения параметра horizontal.
     */
    BlockMatrix concat(const BlockMatrix& other, bool horizontal = true) const;

    /**
     * @brief Нахождение максимального элемента в блочной матрице.
     * @return Максимальный элемент.
     * 
     * Метод находит максимальный элемент среди всех блоков текущей 
     * блочной матрицы.
     */
    MatrixType findMaxElementBlockMatrix() const noexcept;

    /**
     * @brief Нахождение максимального элемента в указанном блоке блочной матрицы.
     * @return Блок матрицы, содержащий максимальный элемент.
     * 
     * Метод находит максимальный элемент в указанном блоке текущей 
     * блочной матрицы.
     */
    Matrix<MatrixType> findMaxElementBlockMatrixBlock() const noexcept;

    /**
     * @brief Нахождение минимального элемента в блочной матрице.
     * @return Минимальный элемент.
     * 
     * Метод находит минимальный элемент среди всех блоков текущей 
     * блочной матрицы.
     */
    MatrixType findMinElementBlockMatrix() const noexcept;

    /**
     * @brief Нахождение минимального элемента в указанном блоке блочной матрицы.
     * @return Блок матрицы, содержащий минимальный элемент.
     * 
     * Метод находит минимальный элемент в указанном блоке текущей 
     * блочной матрицы.
     */
    Matrix<MatrixType> findMinElementBlockMatrixBlock() const noexcept;

    /**
     * @brief Вычисление скалярного произведения с другой блочной матрицей.
     * @param other Другая блочная матрица для скалярного произведения.
     * @return Значение скалярного произведения.
     * 
     * Метод вычисляет скалярное произведение текущей блочной матрицы 
     * с указанной матрицей.
     */
    MatrixType dotProduct(const BlockMatrix& other) const;

    /**
     * @brief Возведение блочной матрицы в степень.
     * @param exp Показатель степени.
     * @return Результирующая блочная матрица после возведения в степень.
     * 
     * Метод возводит текущую блочную матрицу в указанную степень 
     * и возвращает новую матрицу.
     */
    BlockMatrix pow(int exp) const;
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
inline bool BlockMatrix<MatrixType>::isSquare() const { return rows_ == cols_; }

template<typename MatrixType>
double BlockMatrix<MatrixType>::frobeniusNorm() const {
    double sum = 0.0;

    for (size_t i = 0; i < getBlockCount(); ++i) 
        for (size_t j = 0; j < getBlockCount(); ++j) sum += data_[i][j].frobeniusNorm(); 
        
    return std::sqrt(sum);
}

template <typename MatrixType>
inline size_t BlockMatrix<MatrixType>::getBlockCount() const {
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
Matrix<MatrixType> BlockMatrix<MatrixType>::findMaxElementBlockMatrixBlock() const noexcept {
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

template <typename MatrixType>
MatrixType BlockMatrix<MatrixType>::dotProduct(const BlockMatrix<MatrixType>& other) const {
    MatrixType result = static_cast<MatrixType>(0);

    for (size_t i = 0; i < getBlockRows(); ++i) 
        for (size_t j = 0; j < getBlockCols(); ++j) result += (this->getBlock(i, j) * other.getBlock(i, j)).findSumElements();
    
    return result;
}

template <typename MatrixType>
BlockMatrix<MatrixType> BlockMatrix<MatrixType>::pow(int exp) const {
    if (!isSquare()) 
        throw std::invalid_argument("Matrix must be square to raise to a power.");
    
    BlockMatrix<MatrixType> result(*this); 
    BlockMatrix<MatrixType> base(*this);

    if (exp == 0) {
        result = BlockMatrix<MatrixType>(getRows(), getCols(), getBlockRows(), getBlockCols());
        for (size_t i = 0; i < getBlockRows(); ++i) 
            result.getBlock(i, i) = Matrix<MatrixType>::makeIdentityMatrix(getBlockRows());
    } else {
        for (int i = 1; i < exp; ++i) 
            result = result * base;
    }

    return result;
}

} // namespace