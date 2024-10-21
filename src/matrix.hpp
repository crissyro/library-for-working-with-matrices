/**
 * @file matrix.hpp
 * @brief Заголовочный файл для класса Matrix, поддерживающего основные операции с матрицами.
 */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

#define MIN_SIZE_MATRIX 2

namespace matrix_lib {
/**
 * @class MatrixTypeException
 * @brief Исключение для неподдерживаемых типов данных.
 */
class MatrixTypeException : public std::exception {
public:
    /**
     * @brief Возвращает сообщение об ошибке.
     * @return Сообщение об ошибке.
     */
    const char* what() const noexcept override {
        return "Matrix type error: matrix does not support this type.";
    }
};

/**
 * @class Matrix
 * @brief Шаблонный класс для работы с матрицами.
 * @tparam T Тип данных элементов матрицы. Должен быть числовым типом.
 */
template<typename T>
class Matrix {
    static_assert(std::is_arithmetic<T>::value, "Matrix only supports numeric types.");

private:
    size_t rows_;  /**< Количество строк в матрице. */
    size_t cols_;  /**< Количество столбцов в матрице. */
    std::unique_ptr<std::unique_ptr<T[]>[]> data_;  /**< Двумерный массив для хранения данных матрицы. */

    /**
     * @brief Инициализация памяти под матрицу.
     */
    void initMatrix() noexcept;

    /**
     * @brief Освобождение памяти под матрицу.
     */
    void freeMemoryMatrix() noexcept;

    /**
     * @brief Копирование данных другой матрицы.
     * @param other Другая матрица для копирования.
     */
    void copyMatrix(const Matrix<T>& other) noexcept;

public:
    /**
     * @brief Возвращает количество строк в матрице.
     * @return Количество строк.
     */
    size_t getRows() const noexcept;

    /**
     * @brief Возвращает количество столбцов в матрице.
     * @return Количество столбцов.
     */
    size_t getCols() const noexcept;

    /**
     * @brief Конструктор по умолчанию.
     */
    Matrix() noexcept;

    /**
     * @brief Конструктор для создания квадратной матрицы заданного размера.
     * @param size Размер матрицы.
     */
    Matrix(const size_t size) noexcept;

    /**
     * @brief Конструктор для создания матрицы с заданным количеством строк и столбцов.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     */
    Matrix(const size_t rows, const size_t cols) noexcept;

    /**
     * @brief Конструктор для создания матрицы на основе двумерного массива.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     * @param array Исходный двумерный массив.
     */
    Matrix(const size_t rows, const size_t cols, T** array) noexcept;

    /**
     * @brief Конструктор копирования.
     * @param other Другая матрица для копирования.
     */
    Matrix(const Matrix& other) noexcept;

    /**
     * @brief Конструктор перемещения.
     * @param other Другая матрица для перемещения.
     */
    Matrix(Matrix&& other) noexcept;

    /**
     * @brief Деструктор класса Matrix.
     * 
     * Освобождает память, выделенную под матрицу. Так как используется `std::unique_ptr`, 
     * освобождение памяти происходит автоматически, но деструктор гарантирует корректное удаление всех данных матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     */
    ~Matrix() noexcept = default;

    /**
     * @brief Оператор присваивания.
     * @param other Другая матрица для присваивания.
     * @return Ссылка на текущий объект.
     */
    Matrix& operator=(const Matrix& other); 

    /**
     * @brief Оператор сравнения матриц на равенство.
     * 
     * Сравнивает текущую матрицу с другой матрицей на предмет равенства.
     * Матрицы считаются равными, если они имеют одинаковые размеры и все элементы совпадают.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для сравнения.
     * @return true, если матрицы равны, иначе false.
     */
    bool operator==(const Matrix& other) const;

    /**
     * @brief Оператор сложения матриц.
     * 
     * Складывает текущую матрицу с другой матрицей и возвращает результат в виде новой матрицы.
     * Размеры обеих матриц должны совпадать.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для сложения.
     * @return Новая матрица, содержащая результат сложения.
     * @throw std::invalid_argument Если размеры матриц не совпадают.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Оператор вычитания матриц.
     * 
     * Вычитает из текущей матрицы другую матрицу и возвращает результат в виде новой матрицы.
     * Размеры обеих матриц должны совпадать.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для вычитания.
     * @return Новая матрица, содержащая результат вычитания.
     * @throw std::invalid_argument Если размеры матриц не совпадают.
     */
    Matrix operator-(const Matrix& other) const;

    /**
     * @brief Оператор умножения матриц.
     * 
     * Умножает текущую матрицу на другую матрицу и возвращает результат в виде новой матрицы.
     * Количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для умножения.
     * @return Новая матрица, содержащая результат умножения.
     * @throw std::invalid_argument Если количество столбцов первой матрицы не равно количеству строк второй матрицы.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brief Оператор умножения матрицы на скаляр.
     * 
     * Умножает все элементы текущей матрицы на заданный скаляр и возвращает результат в виде новой матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param scalar Скаляр для умножения.
     * @return Новая матрица, содержащая результат умножения.
     */
    Matrix operator*(const T scalar) const;

    /**
     * @brief Оператор доступа к элементу матрицы.
     * 
     * Позволяет получать доступ к элементу матрицы по заданным индексу строки и столбца.
     * 
     * @tparam T Тип элементов матрицы.
     * @param row Индекс строки.
     * @param col Индекс столбца.
     * @return Ссылка на элемент матрицы.
     * @throw std::out_of_range Если индексы выходят за пределы размеров матрицы.
     */
    T& operator()(const size_t row, const size_t col);

    /**
     * @brief Оператор доступа к элементу матрицы для константных объектов.
     * 
     * Позволяет получать доступ к элементу матрицы по заданным индексу строки и столбца.
     * Этот оператор используется для константных объектов матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param row Индекс строки.
     * @param col Индекс столбца.
     * @return Константная ссылка на элемент матрицы.
     * @throw std::out_of_range Если индексы выходят за пределы размеров матрицы.
     */
    const T& operator()(const size_t row, const size_t col) const;

    /**
     * @brief Оператор сложения матриц с присваиванием.
     * 
     * Складывает другую матрицу с текущей матрицей и сохраняет результат в текущей матрице.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для сложения.
     * @return Ссылка на текущую матрицу после выполнения операции.
     * @throw std::invalid_argument Если размеры матриц не совпадают.
     */
    Matrix& operator+=(const Matrix& other);

    /**
     * @brief Оператор вычитания матриц с присваиванием.
     * 
     * Вычитает другую матрицу из текущей матрицы и сохраняет результат в текущей матрице.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для вычитания.
     * @return Ссылка на текущую матрицу после выполнения операции.
     * @throw std::invalid_argument Если размеры матриц не совпадают.
     */
    Matrix& operator-=(const Matrix& other);

    /**
     * @brief Оператор умножения матриц с присваиванием.
     * 
     * Умножает текущую матрицу на другую матрицу и сохраняет результат в текущей матрице.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для умножения.
     * @return Ссылка на текущую матрицу после выполнения операции.
     * @throw std::invalid_argument Если количество столбцов первой матрицы не равно количеству строк второй матрицы.
     */
    Matrix& operator*=(const Matrix& other);

    /**
     * @brief Оператор умножения матрицы на скаляр с присваиванием.
     * 
     * Умножает все элементы текущей матрицы на заданный скаляр и сохраняет результат в текущей матрице.
     * 
     * @tparam T Тип элементов матрицы.
     * @param scalar Скаляр для умножения.
     * @return Ссылка на текущую матрицу после выполнения операции.
     */
    Matrix& operator*=(const T scalar);


    /**
     * @brief Оператор вывода матрицы в поток.
     * 
     * Этот оператор позволяет выводить матрицу в стандартный поток вывода (например, std::cout).
     * Формат вывода матрицы будет строковым представлением с элементами, разделёнными пробелами,
     * где каждая строка матрицы будет на новой строке.
     * 
     * @tparam T Тип элементов матрицы.
     * @param os Ссылка на поток вывода.
     * @param matrix Матрица, которую нужно вывести.
     * @return Ссылка на поток вывода.
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);

    /**
     * @brief Оператор ввода матрицы из потока.
     * 
     * Этот оператор позволяет считывать матрицу из стандартного потока ввода (например, std::cin).
     * Ввод ожидается в виде последовательности чисел, соответствующих элементам матрицы,
     * по строкам (одна строка элементов за раз). 
     * 
     * @tparam T Тип элементов матрицы.
     * @param is Ссылка на поток ввода.
     * @param matrix Матрица, которую нужно заполнить данными из потока.
     * @return Ссылка на поток ввода.
     */
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);

    /**
     * @brief Проверяет, равна ли текущая матрица другой матрице.
     * 
     * Сравнивает текущую матрицу с другой на предмет равенства размеров и всех элементов.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для сравнения.
     * @return true, если матрицы равны, иначе false.
     */
    bool isEqualMatrix(const Matrix& other) const noexcept;

    /**
     * @brief Проверяет, является ли матрица квадратной.
     * 
     * Матрица считается квадратной, если количество строк равно количеству столбцов.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица квадратная, иначе false.
     */
    bool isSquareMatrix() const noexcept;

    /**
     * @brief Проверяет, является ли матрица симметричной.
     * 
     * Симметричная матрица — это квадратная матрица, которая равна своей транспонированной матрице.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица симметричная, иначе false.
     */
    bool isSymetricMatrix() const noexcept;

    /**
     * @brief Проверяет, является ли матрица единичной.
     * 
     * Единичная матрица — это квадратная матрица, в которой на главной диагонали стоят единицы, 
     * а остальные элементы равны нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица единичная, иначе false.
     */
    bool isIdentityMatrix() const noexcept;

    /**
     * @brief Проверяет, является ли матрица нулевой.
     * 
     * Нулевая матрица — это матрица, все элементы которой равны нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица нулевая, иначе false.
     */
    bool isZeroMatrix() const noexcept;

    /**
     * @brief Проверяет, является ли матрица вырожденной (сингулярной).
     * 
     * Вырожденная матрица — это матрица, определитель которой равен нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица вырожденная, иначе false.
     */
    bool isSingular() const noexcept;

    /**
     * @brief Проверяет, является ли матрица диагональной.
     * 
     * Диагональная матрица — это квадратная матрица, у которой все элементы, кроме элементов на главной диагонали, равны нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица диагональная, иначе false.
     */
    bool isDiagonalMatrix() const;

    /**
     * @brief Проверяет, является ли матрица треугольной.
     * 
     * Треугольная матрица — это матрица, у которой либо все элементы ниже (нижнетреугольная),
     * либо все элементы выше (верхнетреугольная) главной диагонали равны нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица треугольная, иначе false.
     */
    bool isTriangularMatrix() const;

    /**
     * @brief Проверяет, является ли матрица верхнетреугольной.
     * 
     * Верхнетреугольная матрица — это матрица, у которой все элементы ниже главной диагонали равны нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица верхнетреугольная, иначе false.
     */
    bool isUpperTriangularMatrix() const;

    /**
     * @brief Проверяет, является ли матрица нижнетреугольной.
     * 
     * Нижнетреугольная матрица — это матрица, у которой все элементы выше главной диагонали равны нулю.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица нижнетреугольная, иначе false.
     */
    bool isLowerTriangularMatrix() const;

    /**
     * @brief Проверяет, является ли матрица ортогональной.
     * 
     * Ортогональная матрица — это матрица, произведение которой на её транспонированную матрицу
     * даёт единичную матрицу.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица ортогональная, иначе false.
     */
    bool isOrthogonalMatrix() const;

    /**
     * @brief Проверяет, является ли матрица нормальной.
     * 
     * Нормальная матрица — это матрица, которая коммутирует со своей транспонированной:
     * \f$ A * A^T = A^T * A \f$.
     * 
     * @tparam T Тип элементов матрицы.
     * @return true, если матрица нормальная, иначе false.
     */
    bool isNormalMatrix() const;
    
    /**
     * @brief Создает единичную матрицу заданного размера.
     *
     * Эта функция генерирует единичную матрицу, где все диагональные элементы
     * равны 1, а все остальные элементы равны 0. Матрица должна быть квадратной.
     *
     * @param size Размер единичной матрицы (число строк и столбцов).
     * @return Новый объект матрицы, представляющий единичную матрицу.
     * @throws std::invalid_argument Если размер меньше MIN_SIZE_MATRIX.
     */
    Matrix makeIdentityMatrix(const size_t size = MIN_SIZE_MATRIX) const;

    /**
     * @brief Создает нулевую матрицу заданных размеров.
     *
     * Эта функция генерирует матрицу, где все элементы установлены в 0. 
     * Количество строк и столбцов может быть задано, по умолчанию используется размер 2x2.
     *
     * @param rows Количество строк в матрице. По умолчанию 2.
     * @param cols Количество столбцов в матрице. По умолчанию 2.
     * @return Новый объект матрицы, где все элементы инициализированы как 0.
     * @throws std::invalid_argument Если количество строк или столбцов меньше MIN_SIZE_MATRIX.
     */
    Matrix makeZeroMatrix(const size_t rows = MIN_SIZE_MATRIX, const size_t cols = MIN_SIZE_MATRIX) const;

    /**
     * @brief Устанавливает текущую матрицу как нулевую.
     * 
     * Все элементы матрицы будут установлены в ноль.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void setZeroMatrix() noexcept;

    /**
     * @brief Устанавливает текущую матрицу как единичную.
     * 
     * Единичная матрица имеет единицы на главной диагонали и нули в остальных позициях.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void setIdentityMatrix();

    /**
     * @brief Преобразует текущую матрицу в диагонализируемую.
     * 
     * Метод преобразует матрицу в диагонализируемую, если возможно.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void setDiagonalizable();

    /**
     * @brief Преобразует текущую матрицу в нормальную матрицу.
     * 
     * Нормальная матрица удовлетворяет условию коммутативности с транспонированной матрицей.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void setNormalMatrix();

    /**
     * @brief Преобразует текущую матрицу в ортогональную.
     * 
     * Ортогональная матрица — это матрица, произведение которой на транспонированную матрицу даёт единичную матрицу.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void setOrthogonalMatrix();

    /**
     * @brief Устанавливает текущую матрицу как диагональную матрицу.
     * 
     * Использует массив диагональных элементов для заполнения главной диагонали матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param diagonalArray Массив элементов для главной диагонали.
     */
    void setDiagonalMatrix(const T* diagonalArray, const size_t diagonalArrayLength);

    /**
     * @brief Преобразует текущую матрицу в ортогональную, используя другую матрицу.
     * 
     * Матрица приводится к ортогональной форме на основе переданной матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица, используемая для преобразования в ортогональную форму.
     */
    void setOrthogonalMatrix(const Matrix& other);

    /**
     * @brief Устанавливает текущую матрицу как диагональную, используя одно значение для всех элементов диагонали.
     * 
     * Все элементы на главной диагонали будут равны переданному значению, остальные элементы будут нулями.
     * 
     * @tparam T Тип элементов матрицы.
     * @param value Значение для всех диагональных элементов.
     */
    void setDiagonalMatrix(const T value);

    /**
     * @brief Устанавливает текущую матрицу как верхнетреугольную с заданным значением диагонали.
     * 
     * Устанавливает все элементы ниже главной диагонали в ноль и задаёт значение для диагональных элементов.
     * 
     * @tparam T Тип элементов матрицы.
     * @param value Значение для всех диагональных элементов.
     */
    void setUpperTriangularMatrix(const T value);

    /**
     * @brief Устанавливает текущую матрицу как нижнетреугольную с заданным значением диагонали.
     * 
     * Устанавливает все элементы выше главной диагонали в ноль и задаёт значение для диагональных элементов.
     * 
     * @tparam T Тип элементов матрицы.
     * @param value Значение для всех диагональных элементов.
     */
    void setLowerTriangularMatrix(const T value);

    /**
     * @brief Устанавливает текущую матрицу как треугольную с заданным значением диагонали.
     * 
     * Устанавливает все элементы выше или ниже главной диагонали в ноль, в зависимости от параметра `isUpper`, и задаёт значение для диагональных элементов.
     * 
     * @tparam T Тип элементов матрицы.
     * @param value Значение для всех диагональных элементов.
     * @param isUpper Если true, создаётся верхнетреугольная матрица, иначе — нижнетреугольная.
     */
    void setTriangularMatrix(const T value, bool isUpper = true);

    /**
     * @brief Выводит матрицу в консоль.
     * 
     * Печатает содержимое матрицы в удобочитаемом формате.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void printMatrix() const;

    /**
     * @brief Выполняет сложение текущей матрицы с другой матрицей.
     * 
     * Элементы текущей матрицы складываются с соответствующими элементами другой матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для сложения.
     * @throws std::invalid_argument Если размеры матриц не совпадают.
     */
    void sumMatrix(const Matrix& other);

    /**
     * @brief Выполняет вычитание другой матрицы из текущей.
     * 
     * Элементы другой матрицы вычитаются из соответствующих элементов текущей матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для вычитания.
     * @throws std::invalid_argument Если размеры матриц не совпадают.
     */
    void subMatrix(const Matrix& other);

    /**
     * @brief Выполняет умножение текущей матрицы на другую матрицу.
     * 
     * Выполняется матричное умножение текущей матрицы и другой матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для умножения.
     * @throws std::invalid_argument Если количество столбцов текущей матрицы не совпадает с количеством строк другой матрицы.
     */
    void mulMatrix(const Matrix& other);

    /**
     * @brief Умножает все элементы текущей матрицы на скаляр.
     * 
     * Все элементы матрицы умножаются на переданное скалярное значение.
     * 
     * @tparam T Тип элементов матрицы.
     * @param scalar Значение скаляра для умножения.
     */
    void mulScalar(const T& scalar);

    /**
     * @brief Выполняет сложение двух матриц.
     *
     * Элементы первой матрицы складываются с соответствующими элементами второй матрицы.
     *
     * @tparam T Тип элементов матрицы.
     * @param mat1 Первая матрица для сложения.
     * @param mat2 Вторая матрица для сложения.
     * @return Новая матрица, представляющая результат сложения.
     * @throws std::invalid_argument Если размеры матриц не совпадают.
     */
    Matrix sumMatrix(const Matrix& mat1, const Matrix& mat2) const;

    /**
     * @brief Выполняет вычитание одной матрицы из другой.
     *
     * Элементы второй матрицы вычитаются из соответствующих элементов первой матрицы.
     *
     * @tparam T Тип элементов матрицы.
     * @param mat1 Первая матрица, из которой происходит вычитание.
     * @param mat2 Вторая матрица, которая вычитается.
     * @return Новая матрица, представляющая результат вычитания.
     * @throws std::invalid_argument Если размеры матриц не совпадают.
     */
    Matrix subMatrix(const Matrix& mat1, const Matrix& mat2) const;

    /**
     * @brief Выполняет умножение двух матриц.
     *
     * Выполняется матричное умножение первой матрицы и второй матрицы.
     *
     * @tparam T Тип элементов матрицы.
     * @param mat1 Первая матрица для умножения.
     * @param mat2 Вторая матрица для умножения.
     * @return Новая матрица, представляющая результат умножения.
     * @throws std::invalid_argument Если количество столбцов первой матрицы не совпадает с количеством строк второй матрицы.
     */
    Matrix mulMatrix(const Matrix& mat1, const Matrix& mat2) const;

    /**
     * @brief Умножает все элементы матрицы на скаляр.
     *
     * Все элементы матрицы умножаются на переданное скалярное значение, 
     * и результат возвращается в виде новой матрицы.
     *
     * @tparam T Тип элементов матрицы.
     * @param mat Исходная матрица, элементы которой будут умножены.
     * @param scalar Значение скаляра для умножения.
     * @return Новая матрица, представляющая результат умножения.
     */
    Matrix mulScalar(const Matrix& mat, const T& scalar) const;

    /**
     * @brief Транспонирует текущую матрицу.
     * 
     * Меняет строки и столбцы местами.
     * 
     * @tparam T Тип элементов матрицы.
     */
    void transposeMatrix();

    /**
     * @brief Возвращает транспонированную копию другой матрицы.
     * 
     * Создаёт и возвращает новую матрицу, которая является транспонированной версией переданной матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Другая матрица для транспонирования.
     * @return Транспонированная версия матрицы.
     */
    Matrix transposeMatrix(const Matrix& other) const;

    /**
     * @brief Вычисляет детерминант матрицы.
     * 
     * Возвращает значение детерминанта текущей матрицы. Работает только для квадратных матриц.
     * 
     * @tparam T Тип элементов матрицы.
     * @return Детерминант матрицы.
     * @throws std::invalid_argument Если матрица не является квадратной.
     */
    T determinant() const;

    /**
     * @brief Вычисляет матрицу кофакторов.
     * 
     * Возвращает матрицу кофакторов для текущей матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @return Матрица кофакторов.
     */
    Matrix cofactorMatrix() const;

    /**
     * @brief Вычисляет присоединённую (адъюнгированную) матрицу.
     * 
     * Присоединённая матрица является транспонированной матрицей кофакторов.
     * 
     * @tparam T Тип элементов матрицы.
     * @return Присоединённая матрица.
     */
    Matrix adjugateMatrix() const;

    /**
     * @brief Вычисляет обратную матрицу.
     * 
     * Возвращает обратную матрицу для текущей, если она существует.
     * 
     * @tparam T Тип элементов матрицы.
     * @return Обратная матрица.
     * @throws std::domain_error Если матрица является вырожденной (необратимой).
     */
    Matrix inverseMatrix() const;

    /**
     * @brief Возвращает обратную матрицу для другой матрицы.
     * 
     * Вычисляет и возвращает обратную матрицу для переданной матрицы.
     * 
     * @tparam T Тип элементов матрицы.
     * @param other Матрица для вычисления обратной.
     * @return Обратная матрица.
     * @throws std::domain_error Если матрица является вырожденной (необратимой).
     */
    Matrix inverseMatrix(const Matrix& other) const;

}; // class Matrix;

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
    *this = *this + other;
    return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    *this = *this - other;
    return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    *this = *this * other;
    return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const T scalar) {
    *this = *this * scalar;
    return *this;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix) {
    for (size_t i = 0; i < matrix.rows_; ++i) {
        for (size_t j = 0; j < matrix.cols_; ++j) {
            os << matrix.data_[i][j];

            if (j < matrix.cols_ - 1) os << " ";
        }

        os << std::endl;
    }
    
    return os;
}

template<typename U>
std::istream& operator>>(std::istream& is, Matrix<U>& matrix) {
    for (size_t i = 0; i < matrix.rows_; ++i) {
        for (size_t j = 0; j < matrix.cols_; ++j) 
            is >> matrix.data_[i][j];
    }

    return is;
}

template<typename T>
inline bool Matrix<T>::isEqualMatrix(const Matrix& other) const noexcept {
    return *this == *other;
}

template<typename T>
inline bool Matrix<T>::isSquareMatrix() const noexcept {
    return rows_ == cols_;
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
Matrix<T> Matrix<T>::makeIdentityMatrix(const size_t size) const {
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
Matrix<T> Matrix<T>::makeZeroMatrix(const size_t rows, const size_t cols) const {
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
        throw std::logic_error("Matrix must be square");

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            data_[i][j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
    }
}

template<typename T>
void Matrix<T>::setDiagonalizable() {
    if (!isSquareMatrix())
        throw std::logic_error("Matrix must be square");

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
        throw std::logic_error("Matrix must be square");

    Matrix<T> transpose = this->transposeMatrix();
    Matrix<T> identity = Matrix<T>::makeIdentityMatrix(rows_);

    if (*this * transpose != transpose * this || *this * identity != identity)
        throw std::logic_error("Matrix is not normal");
}

template<typename T>
void Matrix<T>::setOrthogonalMatrix() {
    if (!isSquareMatrix())
        throw std::logic_error("Matrix must be square");

    Matrix<T> transpose = this->transposeMatrix();
    Matrix<T> identity = Matrix<T>::makeIdentityMatrix(rows_);

    if ((*this * transpose != identity && *this * transpose != -identity) || (*this * identity != identity && *this * identity != -identity))
        throw std::logic_error("Matrix is not orthogonal");
}

template<typename T>
void Matrix<T>::setDiagonalMatrix(const T* diagonalArray, const size_t diagonalArrayLength) {
    if (!isSquareMatrix())
        throw std::logic_error("Matrix must be square");

    if (diagonalArray == nullptr || diagonalArrayLength != rows_)
        throw std::logic_error("Len array must be equal with matrix rows number");

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] = (i == j)? diagonalArray[i] : static_cast<T>(0);
        }
    }
}

template<typename T>
void Matrix<T>::setTriangularMatrix(const T value, bool isUpper) {
    if (!isSquareMatrix())
        throw std::logic_error("Matrix must be square");

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (i < j && isUpper)
                data_[i][j] = static_cast<T>(0);
            else if (i > j &&!isUpper)
                data_[i][j] = static_cast<T>(0);
            else
                data_[i][j] = value;
        }
    }
}

template<typename T>
void Matrix<T>::printMatrix() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            std::cout << data_[i][j];

            if (j < cols_ - 1) std::cout << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl; 
}

template<typename T>
inline void Matrix<T>::sumMatrix(const Matrix<T>& other) { this += other; }

template<typename T>
inline void Matrix<T>::subMatrix(const Matrix<T>& other) { this -= other; }

template<typename T>
inline void Matrix<T>::mulMatrix(const Matrix<T>& other) { this *= other; }

template<typename T>
inline void Matrix<T>::mulScalar(const T& scalar) { this *= scalar; }

template<typename T>
inline Matrix<T> Matrix<T>::sumMatrix(const Matrix<T>& mat1, const Matrix<T>& mat2) const { return mat1 + mat2; }

template<typename T>
inline Matrix<T> Matrix<T>::subMatrix(const Matrix<T>& mat1, const Matrix<T>& mat2) const { return mat1 - mat2; }

template<typename T>
inline Matrix<T> Matrix<T>::mulMatrix(const Matrix<T>& mat1, const Matrix<T>& mat2) const { return mat1 * mat2; }

template<typename T>
inline Matrix<T> Matrix<T>::mulScalar(const Matrix<T>& mat, const T& scalar) const { return mat * scalar; }

template<typename T>
void Matrix<T>::transposeMatrix() {
    Matrix<T> result(cols_, rows_);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            result(i, j) = data_[j][i];
    }

    *this = result;
}

template<typename T>
Matrix<T> Matrix<T>::transposeMatrix(const Matrix<T>& other) const {
    Matrix<T> result(cols_, rows_);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) 
            result(j, i) = data_[i][j];
    }

    return result;
}

template<typename T>
T Matrix<T>::determinant() const {
    if (!isSquareMatrix())
        throw std::logic_error("Matrix must be square");

    if (rows_ == 1)
        return data_[0][0];

    if (rows_ == 2)
        return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];

    T det = static_cast<T>(0);

    for (size_t i = 0; i < cols_; ++i) {
        Matrix<T> minor(rows_ - 1, cols_ - 1);
        for (size_t j = 1; j < rows_; ++j) {
            size_t minorIndex = 0;
            for (size_t k = 0; k < cols_; ++k) {
                if (k == i) continue;

                minor(j - 1, minorIndex++) = data_[j][i];
            }
        }
    
        det += (i % 2 == 0)? data_[0][i] * minor.determinant() : -data_[0][i] * minor.determinant();
    }

    return det;
}

template<typename T>
Matrix<T> Matrix<T>::cofactorMatrix() const {
    if (!isSquareMatrix()) throw std::logic_error("Matrix must be square");

    Matrix<T> cofactor(rows_, cols_);

    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            Matrix<T> minor(rows_ - 1, cols_ - 1);
            for (size_t m = 0; m < rows_ - 1; m++) {
                size_t minorIndex = 0;
                for (size_t n = 0; n < cols_; n++) {
                    if (n == j) continue;

                    minor(m, minorIndex++) = data_[m + 1][n];
                }
            }

            cofactor(i, j) = ((i + j) % 2 == 0) ? minor.determinant() : -minor.determinant();
        }
    }

    return cofactor;
}

template<typename T>
Matrix<T> Matrix<T>::adjugateMatrix() const {
    return this->cofactorMatrix().transposeMatrix();
}

template<typename T>
Matrix<T> Matrix<T>::inverseMatrix() const {
    if (!isSquareMatrix()) throw std::logic_error("Matrix must be square");

    T determinant = this->determinant();

    if (determinant == 0)  throw std::runtime_error("Matrix is singular and cannot be inverted.");

    Matrix<T> adjugate = this->adjugateMatrix();

    return adjugate * (1 / determinant);
}

template<typename T>
Matrix<T> Matrix<T>::inverseMatrix(const Matrix& other) const {
    if (!other.isSquareMatrix()) throw std::logic_error("Matrix must be square");

    T determinant = other.determinant();

    if (determinant == 0)  throw std::runtime_error("Matrix is singular and cannot be inverted.");

    Matrix<T> adjugate = this->adjugateMatrix();
    
    return adjugate * (1 / determinant);
}

} //matrix_lib