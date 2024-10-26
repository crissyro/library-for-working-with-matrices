#include "../sparse_matrix/sparse_matrix.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

namespace matrix_lib {

TEST(SparseMatrixTest, ConstructorSparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    EXPECT_EQ(mat.sizeSparseMatrix().first, 3);
    EXPECT_EQ(mat.sizeSparseMatrix().second, 3);
}

// Тест для добавления значений
TEST(SparseMatrixTest, AddValueSparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    mat.addValue(0, 0, 5);
    mat.addValue(1, 2, 3);

    EXPECT_EQ(mat.getValue(0, 0), 5);
    EXPECT_EQ(mat.getValue(1, 2), 3);
    EXPECT_EQ(mat.getValue(1, 1), 0); // По умолчанию должно быть 0
}

// Тест для сложения матриц
TEST(SparseMatrixTest, AdditionSparseMatrix) {
    SparseMatrix<int> mat1(3, 3);
    mat1.addValue(0, 0, 1);
    mat1.addValue(1, 1, 2);

    SparseMatrix<int> mat2(3, 3);
    mat2.addValue(0, 0, 3);
    mat2.addValue(1, 1, 4);

    SparseMatrix<int> result = mat1 + mat2;

    EXPECT_EQ(result.getValue(0, 0), 4);
    EXPECT_EQ(result.getValue(1, 1), 6);
    EXPECT_EQ(result.getValue(2, 2), 0); // Проверка на несуществующий элемент
}

// Тест для вычитания матриц
TEST(SparseMatrixTest, SubtractionSparseMatrix) {
    SparseMatrix<int> mat1(3, 3);
    mat1.addValue(0, 0, 5);
    mat1.addValue(1, 1, 4);

    SparseMatrix<int> mat2(3, 3);
    mat2.addValue(0, 0, 3);
    mat2.addValue(1, 1, 2);

    SparseMatrix<int> result = mat1 - mat2;

    EXPECT_EQ(result.getValue(0, 0), 2);
    EXPECT_EQ(result.getValue(1, 1), 2);
}

// Тест для умножения матриц
TEST(SparseMatrixTest, MultiplicationSparseMatrix) {
    SparseMatrix<int> mat1(2, 3);
    mat1.addValue(0, 0, 1);
    mat1.addValue(1, 2, 2);

    SparseMatrix<int> mat2(3, 2);
    mat2.addValue(0, 1, 3);
    mat2.addValue(2, 0, 4);

    SparseMatrix<int> result = mat1 * mat2;

    EXPECT_EQ(result.getValue(0, 1), 3);
    EXPECT_EQ(result.getValue(1, 0), 8);
}

// Тест для проверки следа матрицы
TEST(SparseMatrixTest, TraceSparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    mat.addValue(0, 0, 1);
    mat.addValue(1, 1, 2);
    mat.addValue(2, 2, 3);

    EXPECT_EQ(mat.traceSparseMatrix(), 6);
}

// Тест для проверки детерминанта
TEST(SparseMatrixTest, DeterminantSparseMatrix) {
    SparseMatrix<int> mat(2, 2);
    mat.addValue(0, 0, 1);
    mat.addValue(0, 1, 2);
    mat.addValue(1, 0, 3);
    mat.addValue(1, 1, 4);

    EXPECT_EQ(mat.determinantSparseMatrix(), -2);
}

// Тест для проверки на пустоту
TEST(SparseMatrixTest, IsEmptySparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    EXPECT_TRUE(mat.isEmptySparseMatrix());

    mat.addValue(0, 0, 5);
    EXPECT_FALSE(mat.isEmptySparseMatrix());
}

// Тест для проверки диагональной матрицы
TEST(SparseMatrixTest, IsDiagonalSparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    mat.addValue(0, 0, 1);
    mat.addValue(1, 1, 2);
    mat.addValue(2, 2, 3);

    EXPECT_TRUE(mat.isDiagonalSparseMatrix());

    mat.addValue(1, 2, 4);
    EXPECT_FALSE(mat.isDiagonalSparseMatrix());
}

// Тест для проверки идентичной матрицы
TEST(SparseMatrixTest, IsIdentitySparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    mat.fillDiagonalSparseMatrix(1);
    EXPECT_TRUE(mat.isIdentitySparseMatrix());

    mat.addValue(0, 1, 2);
    EXPECT_FALSE(mat.isIdentitySparseMatrix());
}

TEST(SparseMatrixTest, AddValueOutOfBounds) {
    SparseMatrix<int> mat(3, 3);
    EXPECT_THROW(mat.addValue(3, 3, 5), std::out_of_range);
}

// Тест для исключения при получении значения вне границ
TEST(SparseMatrixTest, GetValueOutOfBounds) {
    SparseMatrix<int> mat(3, 3);
    EXPECT_THROW(mat.getValue(3, 3), std::out_of_range);
}

// Тест для детерминанта 3x3 матрицы
TEST(SparseMatrixTest, Determinant3x3SparseMatrix) {
    SparseMatrix<int> mat(3, 3);
    mat.addValue(0, 0, 1);
    mat.addValue(0, 1, 2);
    mat.addValue(0, 2, 3);
    mat.addValue(1, 0, 0);
    mat.addValue(1, 1, 4);
    mat.addValue(1, 2, 5);
    mat.addValue(2, 0, 1);
    mat.addValue(2, 1, 0);
    mat.addValue(2, 2, 6);

    EXPECT_EQ(mat.determinantSparseMatrix(), 22); // Проверьте правильность результата
}

// Тест для проверки сложения матриц разного размера
TEST(SparseMatrixTest, AdditionDifferentSizeSparseMatrix) {
    SparseMatrix<int> mat1(2, 2);
    SparseMatrix<int> mat2(3, 3);
    EXPECT_THROW(mat1 + mat2, std::invalid_argument);
}

// Тест для проверки вычитания матриц разного размера
TEST(SparseMatrixTest, SubtractionDifferentSizeSparseMatrix) {
    SparseMatrix<int> mat1(2, 2);
    SparseMatrix<int> mat2(3, 3);
    EXPECT_THROW(mat1 - mat2, std::invalid_argument);
}

// Тест для проверки умножения матриц несовместимых размеров
TEST(SparseMatrixTest, MultiplicationIncompatibleSizeSparseMatrix) {
    SparseMatrix<int> mat1(2, 3);
    SparseMatrix<int> mat2(4, 2);
    EXPECT_THROW(mat1 * mat2, std::invalid_argument);
}

// Тест для проверки вычисления следа для недопустимой матрицы (размер 0)
TEST(SparseMatrixTest, TraceZeroSizeSparseMatrix) {
    SparseMatrix<int> mat(2, 3);
    mat.addValue(0, 0, 1);
    mat.addValue(0, 1, 2);
    mat.addValue(0, 2, 3);
    EXPECT_THROW(mat.traceSparseMatrix(), std::invalid_argument);
}

}

