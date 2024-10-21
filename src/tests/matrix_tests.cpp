#include "../matrix.hpp"
#include <gtest/gtest.h>

namespace matrix_lib {

// Тест на создание матрицы
TEST(MatrixTest, Creation) {
    Matrix<int> mat(3, 3);
    EXPECT_EQ(mat.getRows(), 3);
    EXPECT_EQ(mat.getCols(), 3);
}

// Тест на создание матрицы по умолчанию
TEST(MatrixTest, DefaultMatrix) {
    Matrix<int> mat; // Предполагается, что конструктор по умолчанию создаёт 2x2 матрицу
    EXPECT_EQ(mat.getRows(), 2);
    EXPECT_EQ(mat.getCols(), 2);
}

// Тест на установку значений матрицы
TEST(MatrixTest, SetValues) {
    Matrix<int> mat(3, 3);
    mat(0, 0) = 1;
    mat(0, 1) = 2;
    mat(0, 2) = 3;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(0, 2), 3);
}

// Тест на создание единичной матрицы
TEST(MatrixTest, IdentityMatrix) {
    Matrix<int> m;
    m = m.makeIdentityMatrix(3);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(1, 1), 1);
    EXPECT_EQ(m(2, 2), 1);
    EXPECT_EQ(m(0, 1), 0);
}

// Тест на создание нулевой матрицы
TEST(MatrixTest, ZeroMatrix) {
    Matrix<int> mat;
    mat = mat.makeZeroMatrix(2, 3);
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            EXPECT_EQ(mat(i, j), 0);
        }
    }
}

// Тест на сложение матриц
TEST(MatrixTest, Addition) {
    Matrix<int> mat1(2, 2);
    Matrix<int> mat2(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;
    mat2(0, 0) = 5; mat2(0, 1) = 6;
    mat2(1, 0) = 7; mat2(1, 1) = 8;

    Matrix<int> result = mat1 + mat2;
    EXPECT_EQ(result(0, 0), 6);
    EXPECT_EQ(result(0, 1), 8);
    EXPECT_EQ(result(1, 0), 10);
    EXPECT_EQ(result(1, 1), 12);
}

// Тест на умножение матриц
TEST(MatrixTest, Multiplication) {
    Matrix<int> mat1(2, 3);
    Matrix<int> mat2(3, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2; mat1(0, 2) = 3;
    mat1(1, 0) = 4; mat1(1, 1) = 5; mat1(1, 2) = 6;
    mat2(0, 0) = 7; mat2(0, 1) = 8;
    mat2(1, 0) = 9; mat2(1, 1) = 10;
    mat2(2, 0) = 11; mat2(2, 1) = 12;

    Matrix<int> result = mat1 * mat2;
    EXPECT_EQ(result(0, 0), 58);
    EXPECT_EQ(result(0, 1), 64);
    EXPECT_EQ(result(1, 0), 139);
    EXPECT_EQ(result(1, 1), 154);
}

// Тест на проверку на квадратность
TEST(MatrixTest, SquareMatrixCheck) {
    Matrix<int> mat(3, 3);
    EXPECT_TRUE(mat.isSquareMatrix());
    Matrix<int> mat2(2, 3);
    EXPECT_FALSE(mat2.isSquareMatrix());
}

// Тест на оператор вывода
TEST(MatrixTest, StreamOutput) {
    Matrix<int> mat(2, 2);
    mat(0, 0) = 1;
    mat(0, 1) = 2;
    mat(1, 0) = 3;
    mat(1, 1) = 4;
    std::ostringstream oss;
    oss << mat;
    EXPECT_EQ(oss.str(), "1 2\n3 4\n");
}

// Тест на оператор ввода
TEST(MatrixTest, StreamInput) {
    Matrix<int> mat(2, 2);
    std::istringstream iss("1 2\n3 4\n");
    iss >> mat;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}