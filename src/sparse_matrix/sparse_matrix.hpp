#pragma once 

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

namespace matrix_lib {

/**
 * @brief Класс для представления разреженной матрицы.
 *
 * Данный класс реализует разреженную матрицу с возможностью
 * хранения ненулевых значений, их индексов и выполнения различных
 * операций над матрицами, таких как сложение, вычитание, умножение,
 * а также получение характеристик матрицы.
 *
 * @tparam T Тип элементов матрицы (например, int, double).
 */
template <typename T>
class SparseMatrix {
private:
    std::vector<size_t> rowsIndexes;  ///< Индексы строк ненулевых элементов
    std::vector<size_t> colsIndexes;  ///< Индексы столбцов ненулевых элементов
    std::vector<T> values;             ///< Ненулевые значения
    size_t rows_;                      ///< Количество строк
    size_t cols_;                      ///< Количество столбцов

public:
    /**
     * @brief Конструктор по умолчанию. Создает пустую разреженную матрицу.
     */
    SparseMatrix() : rows_(0), cols_(0) {}

    /**
     * @brief Конструктор с параметрами. Создает разреженную матрицу заданного размера.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     */
    SparseMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {}

    /**
     * @brief Конструктор копирования.
     * @param other Другой объект SparseMatrix для копирования.
     */
    SparseMatrix(const SparseMatrix& other) = default;

    /**
     * @brief Конструктор перемещения.
     * @param other Другой объект SparseMatrix для перемещения.
     */
    SparseMatrix(SparseMatrix&& other) noexcept = default;

    /**
     * @brief Деструктор. Освобождает ресурсы.
     */
    ~SparseMatrix() = default;

    /**
     * @brief Получить количество строк матрицы.
     * @return Количество строк.
     */
    size_t getRowsSparseMatrix() const { return rows_; }

    /**
     * @brief Получить количество столбцов матрицы.
     * @return Количество столбцов.
     */
    size_t getColsSparseMatrix() const { return cols_; }

    /**
     * @brief Оператор присваивания копированием.
     * @param other Другой объект SparseMatrix.
     * @return Ссылка на текущий объект.
     */
    SparseMatrix& operator=(const SparseMatrix& other);

    /**
     * @brief Оператор присваивания перемещением.
     * @param other Другой объект SparseMatrix.
     * @return Ссылка на текущий объект.
     */
    SparseMatrix& operator=(SparseMatrix&& other) noexcept;

    /**
     * @brief Оператор сложения.
     * @param other Другой объект SparseMatrix.
     * @return Новый объект SparseMatrix, представляющий сумму.
     */
    SparseMatrix operator+(const SparseMatrix& other) const;

    /**
     * @brief Оператор вычитания.
     * @param other Другой объект SparseMatrix.
     * @return Новый объект SparseMatrix, представляющий разность.
     */
    SparseMatrix operator-(const SparseMatrix& other) const;

    /**
     * @brief Оператор умножения.
     * @param other Другой объект SparseMatrix.
     * @return Новый объект SparseMatrix, представляющий произведение.
     */
    SparseMatrix operator*(const SparseMatrix& other) const;

    /**
     * @brief Оператор умножения на скаляр.
     * @param scalar Скаляр.
     * @return Новый объект SparseMatrix, представляющий произведение.
     */
    SparseMatrix operator*(const T scalar) const;

    /**
     * @brief Оператор присваивания сложения.
     * @param other Другой объект SparseMatrix.
     * @return Ссылка на текущий объект.
     */
    SparseMatrix& operator+=(const SparseMatrix& other);

    /**
     * @brief Оператор присваивания вычитания.
     * @param other Другой объект SparseMatrix.
     * @return Ссылка на текущий объект.
     */
    SparseMatrix& operator-=(const SparseMatrix& other);

    /**
     * @brief Оператор присваивания умножения.
     * @param other Другой объект SparseMatrix.
     * @return Ссылка на текущий объект.
     */
    SparseMatrix& operator*=(const SparseMatrix& other);

    /**
     * @brief Оператор присваивания умножения на скаляр.
     * @param scalar Скаляр.
     * @return Ссылка на текущий объект.
     */
    SparseMatrix& operator*=(const T scalar);

    /**
     * @brief Оператор сравнения на равенство.
     * @param other Другой объект SparseMatrix.
     * @return true, если матрицы равны, иначе false.
     */
    bool operator==(const SparseMatrix& other) const;

    /**
     * @brief Оператор сравнения на неравенство.
     * @param other Другой объект SparseMatrix.
     * @return true, если матрицы не равны, иначе false.
     */
    bool operator!=(const SparseMatrix& other) const;

    /**
     * @brief Проверка, является ли матрица нулевой.
     * @return true, если матрица нулевая, иначе false.
     */
    bool isZeroSparseMatrix() const;

    /**
     * @brief Проверка, является ли матрица квадратной.
     * @return true, если матрица квадратная, иначе false.
     */
    bool isSquareSparseMatrix() const;

    /**
     * @brief Проверка, является ли матрица единичной.
     * @return true, если матрица единичная, иначе false.
     */
    bool isIdentitySparseMatrix() const;

    /**
     * @brief Проверка, является ли матрица диагональной.
     * @return true, если матрица диагональная, иначе false.
     */
    bool isDiagonalSparseMatrix() const;

    /**
     * @brief Проверка, является ли матрица пустой.
     * @return true, если матрица пустая, иначе false.
     */
    bool isEmptySparseMatrix() const;

    /**
     * @brief Добавить ненулевое значение в матрицу.
     * @param row Индекс строки.
     * @param col Индекс столбца.
     * @param value Ненулевое значение для добавления.
     */
    void addValue(const size_t row, const size_t col, const T value);

    /**
     * @brief Получить значение по индексу.
     * @param row Индекс строки.
     * @param col Индекс столбца.
     * @return Значение в указанной позиции.
     * @throw std::out_of_range Если индекс выходит за пределы матрицы.
     */
    T getValue(const size_t row, const size_t col) const;

    /**
     * @brief Вывести все ненулевые элементы матрицы.
     */
    void printSparseMatrix() const;

    /**
     * @brief Получить количество ненулевых элементов в матрице.
     * @return Количество ненулевых элементов.
     */
    size_t getNonZeroCount() const;

    /**
     * @brief Транспонировать матрицу.
     * @return Транспонированная матрица.
     */
    SparseMatrix<T> transposeSparseMatrix() const;

    /**
     * @brief Умножить матрицу на скаляр.
     * @param scalar Скаляр для умножения.
     */
    void scaleSparseMatrix(T scalar);

    /**
     * @brief Заполнить главную диагональ матрицы заданным значением.
     * @param value Значение для заполнения диагонали.
     */
    void fillDiagonalSparseMatrix(T value);

    /**
     * @brief Получить количество ненулевых элементов в строке.
     * @param row Индекс строки.
     * @return Количество ненулевых элементов в строке.
     */
    size_t nonZeroCountInRow(int row) const;

    /**
     * @brief Получить количество ненулевых элементов в столбце.
     * @param col Индекс столбца.
     * @return Количество ненулевых элементов в столбце.
     */
    size_t nonZeroCountInColumn(int col) const;

    /**
     * @brief Получить размеры матрицы.
     * @return Пара, содержащая количество строк и столбцов.
     */
    std::pair<size_t, size_t> sizeSparseMatrix() const;

    /**
     * @brief Вычислить плотность разреженной матрицы.
     * @return Плотность матрицы (отношение ненулевых элементов к общему количеству элементов).
     */
    double densitySparseMatrix() const;

    /**
     * @brief Очистить разреженную матрицу, удалив все элементы.
     */
    void clearSparseMatrix();

    /**
     * @brief Получить максимальный элемент разреженной матрицы.
     * @return Максимальный элемент.
     * @throw std::runtime_error Если матрица пуста.
     */
    T maxElementSparseMatrix() const;

    /**
     * @brief Получить минимальный элемент разреженной матрицы.
     * @return Минимальный элемент.
     * @throw std::runtime_error Если матрица пуста.
     */
    T minElementSparseMatrix() const;

    /**
     * @brief Вычислить сумму элементов указанной строки.
     * @param row Индекс строки.
     * @return Сумма элементов строки.
     */
    T sumRowSparseMatrix(int row) const;

    /**
     * @brief Вычислить сумму элементов указанного столбца.
     * @param col Индекс столбца.
     * @return Сумма элементов столбца.
     */
    T sumColumnSparseMatrix(int col) const;

    /**
     * @brief Получить общую сумму ненулевых значений.
     * @return Общая сумма.
     */
    T totalSumSparseMatrix() const;

    /**
     * @brief Найти след разреженной матрицы.
     * @return След матрицы.
     */
    T traceSparseMatrix() const;

    /**
     * @brief Получить минор матрицы по указанным индексам.
     * @param row Индекс удаляемой строки.
     * @param col Индекс удаляемого столбца.
     * @return Минор разреженной матрицы.
     */
    SparseMatrix<T> minorSparseMatrix(size_t row, size_t col) const;

    /**
     * @brief Вычислить определитель разреженной матрицы.
     * @return Определитель.
     */
    T determinantSparseMatrix() const;

    /**
     * @brief Получить матрицу кофакторов.
     * @return Матрица кофакторов.
     */
    SparseMatrix<T> cofactorSparseMatrix() const;

    /**
     * @brief Получить аджугат разреженной матрицы.
     * @return Аджугат разреженной матрицы.
     */
    SparseMatrix<T> adjugateSparseMatrix() const;

    /**
     * @brief Вычислить обратную матрицу.
     * @return Обратная матрица.
     */
    SparseMatrix<T> inverseSparseMatrix() const;
};

template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        rowsIndexes = other.rowsIndexes;
        colsIndexes = other.colsIndexes;
        values = other.values;
    }

    return *this;
}

template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator=(SparseMatrix&& other) noexcept {
    if (this != &other) {
        rows_ = std::exchange(other.rows_, 0);
        cols_ = std::exchange(other.cols_, 0);
        rowsIndexes = std::move(other.rowsIndexes);
        colsIndexes = std::move(other.colsIndexes);
        values = std::move(other.values);
    }

    return *this;
}

template <typename T>
bool SparseMatrix<T>::operator==(const SparseMatrix& other) const {
    return (rows_ == other.rows_ && cols_ == other.cols_ &&
            rowsIndexes == other.rowsIndexes && colsIndexes == other.colsIndexes &&
            values == other.values);
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::operator+=(const SparseMatrix& other) {
    (*this) = (*this) + other; 
    return *this;
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::operator-=(const SparseMatrix& other) {
    (*this) = (*this) - other;
    return *this;
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::operator*=(const SparseMatrix& other) {
    (*this) = (*this) * other;
    return *this;
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::operator*=(const T scalar) {
    (*this) = (*this) * scalar;
    return *this;
}

template <typename T>
bool SparseMatrix<T>::operator!=(const SparseMatrix& other) const { return !(*this == other); }

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) 
        throw std::invalid_argument("Matrices have different dimensions");
    
    SparseMatrix result(rows_, cols_);

    size_t i = 0;
    size_t j = 0;

    while (i < values.size() || j < other.values.size()) {
        if (i < values.size() && (j >= other.values.size() || rowsIndexes[i] < other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] < other.colsIndexes[j]))) {
            result.addValue(rowsIndexes[i], colsIndexes[i], values[i]);
            ++i;
        } else if (j < other.values.size() && (i >= values.size() || rowsIndexes[i] > other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] > other.colsIndexes[j]))) {
            result.addValue(other.rowsIndexes[j], other.colsIndexes[j], other.values[j]);
            ++j;
        } else {
            T sum = values[i] + other.values[j];
            if (sum != T(0)) result.addValue(rowsIndexes[i], colsIndexes[i], sum); 

            ++i;
            ++j;
        }
    }

    return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator-(const SparseMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) 
        throw std::invalid_argument("Matrices have different dimensions");
    

    SparseMatrix result(rows_, cols_);

    size_t i = 0;
    size_t j = 0;

    while (i < values.size() || j < other.values.size()) {
        if (i < values.size() && (j >= other.values.size() || rowsIndexes[i] < other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] < other.colsIndexes[j]))) {
            result.addValue(rowsIndexes[i], colsIndexes[i], values[i]);
            ++i;
        } else if (j < other.values.size() && (i >= values.size() || rowsIndexes[i] > other.rowsIndexes[j] ||
            (rowsIndexes[i] == other.rowsIndexes[j] && colsIndexes[i] > other.colsIndexes[j]))) {
            result.addValue(other.rowsIndexes[j], other.colsIndexes[j], -other.values[j]);
            ++j;
        } else {
            T diff = values[i] - other.values[j];
            if (diff != T(0)) result.addValue(rowsIndexes[i], colsIndexes[i], diff);
    
            ++i;
            ++j;
        }
    }

    return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix& other) const {
    if (cols_ != other.rows_) 
        throw std::invalid_argument("Matrices have incompatible dimensions for multiplication");
    
    SparseMatrix result(rows_, other.cols_);

    for (size_t i = 0; i < values.size(); ++i) {
        int row = rowsIndexes[i];
        T value = values[i];

        for (size_t j = 0; j < other.values.size(); ++j) {
            if (other.rowsIndexes[j] == colsIndexes[i]) { 
                int col = other.colsIndexes[j];
                T product = value * other.values[j];
                result.addValue(row, col, result.getValue(row, col) + product);
            }
        }
    }

    return result;
}

template <typename T>
inline SparseMatrix<T> SparseMatrix<T>::operator*(const T scalar) const {
    SparseMatrix result(*this);

    for (T& element : result.values) element *= scalar;
    
    return result;
}

template <typename T>
inline void SparseMatrix<T>::scaleSparseMatrix(T scalar) {
    for (auto& value : values) value *= scalar;
}

template <typename T>
void SparseMatrix<T>::clearSparseMatrix() {
    rowsIndexes.clear();
    colsIndexes.clear();
    values.clear();
}

template <typename T>
T SparseMatrix<T>::traceSparseMatrix() const {
    if (rows_ != cols_) 
        throw std::invalid_argument("Matrix must be square");
    

    T traceValue = static_cast<T>(0);
    for (size_t i = 0; i < values.size(); ++i) 
        if (rowsIndexes[i] == colsIndexes[i]) traceValue += values[i];  
    
    return traceValue;
}

template <typename T>
void SparseMatrix<T>::addValue(const size_t row, const size_t col, const T value) {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Index out of range");
    
    if (value != static_cast<T>(0)) {
        rowsIndexes.push_back(row);
        colsIndexes.push_back(col);
        values.push_back(value);
    }
}

template<typename T>
T SparseMatrix<T>::getValue(const size_t row, const size_t col) const {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Index out of range");

    for (size_t i = 0; i < values.size(); ++i) 
        if (rowsIndexes[i] == row && colsIndexes[i] == col) return values[i];
    
    return static_cast<T>(0);
}

template <typename T>
void SparseMatrix<T>::printSparseMatrix() const {
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << "Value: " << values[i] << " at (" 
                  << rowsIndexes[i] << ", " << colsIndexes[i] << ")\n";
    }
}

template <typename T>
inline std::pair<size_t, size_t> SparseMatrix<T>::sizeSparseMatrix() const { return { rows_, cols_ }; }

template <typename T>
double SparseMatrix<T>::densitySparseMatrix() const { return static_cast<double>(values.size()) / (rows_ * cols_); }

template <typename T>
inline size_t SparseMatrix<T>::getNonZeroCount() const { return values.size(); }

template <typename T>
inline bool SparseMatrix<T>::isZeroSparseMatrix() const { return values.empty(); }

template <typename T>
inline bool SparseMatrix<T>::isSquareSparseMatrix() const { return rows_ == cols_; }

template <typename T>
inline bool SparseMatrix<T>::isEmptySparseMatrix() const { return values.empty(); }

template<typename T>
bool SparseMatrix<T>::isIdentitySparseMatrix() const {
    if (!isSquareSparseMatrix()) return false;

    for (size_t i = 0; i < values.size(); i++) {
        if (rowsIndexes[i] == colsIndexes[i]) {
            if (values[i] != static_cast<T>(1)) return false;
        } else {
            if (values[i] != static_cast<T>(0)) return false;
        }
    }

    return true;
}

template<typename T>
bool SparseMatrix<T>::isDiagonalSparseMatrix() const {
    for (size_t i = 0; i < values.size(); i++) {
        if (rowsIndexes[i] != colsIndexes[i]) 
            if (values[i] != static_cast<T>(0)) return false;
    }

    return true;
}

template <typename T>
T SparseMatrix<T>::maxElementSparseMatrix() const {
    if (values.empty()) throw std::runtime_error("Matrix is empty");
    return *std::max_element(values.begin(), values.end());
}

template <typename T>
T SparseMatrix<T>::minElementSparseMatrix() const {
    if (values.empty()) throw std::runtime_error("Matrix is empty");
    return *std::min_element(values.begin(), values.end());
}


template <typename T>
void SparseMatrix<T>::fillDiagonalSparseMatrix(T value) {
    clearSparseMatrix();
    size_t minDim = std::min(rows_, cols_);

    for (size_t i = 0; i < minDim; ++i) addValue(i, i, value);
}

template <typename T>
T SparseMatrix<T>::sumRowSparseMatrix(int row) const {
    T sum = static_cast<T>(0);

    for (size_t i = 0; i < rowsIndexes.size(); ++i) 
        if (rowsIndexes[i] == row) sum += values[i];
        
    return sum;
}

template <typename T>
T SparseMatrix<T>::sumColumnSparseMatrix(int col) const {
    T sum = static_cast<T>(0);

    for (size_t i = 0; i < colsIndexes.size(); ++i) 
        if (colsIndexes[i] == col) sum += values[i];
        
    return sum;
}

template <typename T>
inline T SparseMatrix<T>::totalSumSparseMatrix() const {
    T sum = static_cast<T>(0);
    for (const T& value : values) sum += value;
    
    return sum;
}

template <typename T>
size_t SparseMatrix<T>::nonZeroCountInRow(int row) const {
    size_t count = 0;

    for (size_t i = 0; i < rowsIndexes.size(); ++i) 
        if (rowsIndexes[i] == row) ++count;
        
    return count;
}

template <typename T>
size_t SparseMatrix<T>::nonZeroCountInColumn(int col) const {
    size_t count = 0;

    for (size_t i = 0; i < colsIndexes.size(); ++i) 
        if (colsIndexes[i] == col) ++count;
    

    return count;
}


template <typename T>
SparseMatrix<T> SparseMatrix<T>::transposeSparseMatrix() const {
    SparseMatrix result(cols_, rows_);

    result.rowsIndexes = colsIndexes;
    result.colsIndexes = rowsIndexes;
    result.values = values;

    return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::minorSparseMatrix(size_t row, size_t col) const {
    SparseMatrix<T> minorMatrix(rows_ - 1, cols_ - 1);

    for (size_t i = 0; i < values.size(); ++i) {
        if (rowsIndexes[i] == row || colsIndexes[i] == col) continue;

        size_t newRow = (rowsIndexes[i] < row) ? rowsIndexes[i] : rowsIndexes[i] - 1;
        size_t newCol = (colsIndexes[i] < col) ? colsIndexes[i] : colsIndexes[i] - 1;

        minorMatrix.addValue(newRow, newCol, values[i]);
    }

    return minorMatrix;
}

template <typename T>
T SparseMatrix<T>::determinantSparseMatrix() const {
    if (!isSquareSparseMatrix()) 
        throw std::invalid_argument("Matrix must be square");
    

    if (rows_ == 1) return getValue(0, 0); 

    if (rows_ == 2) return getValue(0, 0) * getValue(1, 1) - getValue(0, 1) * getValue(1, 0);
    
    T det = static_cast<T>(0);
    for (size_t i = 0; i < cols_; ++i) {
        T minorDet = minorSparseMatrix(0, i).determinantSparseMatrix();
        det += ((i % 2 == 0) ? 1 : -1) * getValue(0, i) * minorDet;
    }

    return det;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::cofactorSparseMatrix() const {
    SparseMatrix<T> cofactorMat(rows_, cols_);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            T minorDet = minorSparseMatrix(i, j).determinantSparseMatrix();
            T sign = ((i + j) % 2 == 0) ? 1 : -1;
            cofactorMat.addValue(i, j, sign * minorDet);
        }
    }

    return cofactorMat;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::adjugateSparseMatrix() const { return cofactorSparseMatrix().transposeSparseMatrix(); }

template <typename T>
SparseMatrix<T> SparseMatrix<T>::inverseSparseMatrix() const {
    T det = determinantSparseMatrix();

    if (det == static_cast<T>(0)) 
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    

    SparseMatrix<T> adjugateMatrix = adjugateSparseMatrix();
    SparseMatrix<T> inverseMatrix(rows_, cols_);

    for (size_t i = 0; i < adjugateMatrix.values.size(); ++i) {
        inverseMatrix.addValue(
            adjugateMatrix.rowsIndexes[i],
            adjugateMatrix.colsIndexes[i],
            adjugateMatrix.values[i] / det
        );
    }

    return inverseMatrix;
}

} // namespace matrix_lib