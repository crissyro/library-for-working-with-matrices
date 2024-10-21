#include "../matrix.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

namespace matrix_lib {

TEST(MatrixTest, DefaultMatrix) {
    Matrix<int> mat;
    EXPECT_EQ(mat.getRows(), 2);
    EXPECT_EQ(mat.getCols(), 2);
}

TEST(MatrixTest, SetValues) {
    Matrix<int> mat(3, 3);
    mat(0, 0) = 1;
    mat(0, 1) = 2;
    mat(0, 2) = 3;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(0, 2), 3);
}

TEST(MatrixTest, IdentityMatrix) {
    Matrix<int> m;
    m = m.makeIdentityMatrix(3);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(1, 1), 1);
    EXPECT_EQ(m(2, 2), 1);
    EXPECT_EQ(m(0, 1), 0);
}

TEST(MatrixTest, ZeroMatrix) {
    Matrix<int> mat;
    mat = mat.makeZeroMatrix(2, 3);
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            EXPECT_EQ(mat(i, j), 0);
        }
    }
}

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

TEST(MatrixTest, SquareMatrixCheck) {
    Matrix<int> mat(3, 3);
    EXPECT_TRUE(mat.isSquareMatrix());
    Matrix<int> mat2(2, 3);
    EXPECT_FALSE(mat2.isSquareMatrix());
}

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

TEST(MatrixTest, StreamInput) {
    Matrix<int> mat(2, 2);
    std::istringstream iss("1 2\n3 4\n");
    iss >> mat;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST(MatrixTest, ExceptionOnInvalidIndex) {
    Matrix<int> mat(2, 2);
    EXPECT_THROW(mat(2, 2), std::out_of_range);
    EXPECT_THROW(mat(-1, -1), std::out_of_range);
}

TEST(MatrixTest, ExceptionOnInvalidAddition) {
    Matrix<int> mat1(2, 2);
    Matrix<int> mat2(3, 3);
    EXPECT_THROW(mat1 + mat2, std::logic_error);
}

TEST(MatrixTest, ExceptionOnInvalidMultiplication) {
    Matrix<int> mat1(2, 3);
    Matrix<int> mat2(2, 2);
    EXPECT_THROW(mat1 * mat2, std::logic_error);
}

TEST(MatrixTest, ExceptionOnIdentityMatrix) {
    Matrix<int> mat;
    EXPECT_THROW(mat.makeIdentityMatrix(0), std::logic_error);
}

TEST(MatrixTest, ExceptionOnZeroMatrix) {
    Matrix<int> mat;
    EXPECT_THROW(mat.makeZeroMatrix(0, 3), std::logic_error);
    EXPECT_THROW(mat.makeZeroMatrix(2, 0), std::logic_error);
}

TEST(MatrixTest, EdgeCaseEmptyMatrix) {
    Matrix<int> mat(0, 0);
    EXPECT_EQ(mat.getRows(), 0);
    EXPECT_EQ(mat.getCols(), 0);
}

TEST(MatrixTest, EdgeCaseLargeMatrix) {
    Matrix<int> mat(1000, 1000);
    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            mat(i, j) = 1;
        }
    }
    EXPECT_EQ(mat(999, 999), 1);
}

TEST(MatrixTest, TypeCheckDoubleMatrix) {
    Matrix<double> mat(2, 2);
    mat(0, 0) = 1.1;
    mat(1, 0) = 2.2;
    EXPECT_DOUBLE_EQ(mat(0, 0), 1.1);
    EXPECT_DOUBLE_EQ(mat(1, 0), 2.2);
}

TEST(MatrixTest, ExceptionDeterminantMatrix) {
    Matrix<int> mat(2, 3);
    EXPECT_THROW(mat.determinant(), std::logic_error);
}

TEST(MatrixTest, ExceptionCofactorMatrix) {
    Matrix<int> mat(2, 3);
    EXPECT_THROW(mat.cofactorMatrix(), std::logic_error);
}

TEST(MatrixTest, ExceptionAdjugateMatrix) {
    Matrix<int> mat(2, 3);
    EXPECT_THROW(mat.adjugateMatrix(), std::logic_error);
}

// TEST(MatrixTest, Determinant) {
//     Matrix<int> mat(2, 2);
//     mat(0, 0) = 1; mat(0, 1) = 2;
//     mat(1, 0) = 3; mat(1, 1) = 4;
//     EXPECT_EQ(mat.determinant(), -2);

//     Matrix<int> mat3(3, 3);
//     mat3(0, 0) = 1; mat3(0, 1) = 2; mat3(0, 2) = 3;
//     mat3(1, 0) = 0; mat3(1, 1) = 1; mat3(1, 2) = 4;
//     mat3(2, 0) = 5; mat3(2, 1) = 6; mat3(2, 2) = 0;
//     EXPECT_EQ(mat3.determinant(), 1);
// }

// TEST(MatrixTest, InverseMatrix) {
//     Matrix<int> mat(2, 2);
//     mat(0, 0) = 4; mat(0, 1) = 7;
//     mat(1, 0) = 2; mat(1, 1) = 6;
//     Matrix<int> inv = mat.inverseMatrix();
//     EXPECT_DOUBLE_EQ(inv(0, 0), 0.6);
//     EXPECT_DOUBLE_EQ(inv(0, 1), -0.7);
//     EXPECT_DOUBLE_EQ(inv(1, 0), -0.2);
//     EXPECT_DOUBLE_EQ(inv(1, 1), 0.4);
// }

// TEST(MatrixTest, CofactorMatrix) {
//     Matrix<int> mat(3, 3);
//     mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
//     mat(1, 0) = 0; mat(1, 1) = 1; mat(1, 2) = 4;
//     mat(2, 0) = 5; mat(2, 1) = 6; mat(2, 2) = 0;
//     Matrix<int> cofactor = mat.cofactorMatrix();
//     EXPECT_EQ(cofactor(0, 0), 6);
//     EXPECT_EQ(cofactor(0, 1), -15);
//     EXPECT_EQ(cofactor(0, 2), 4);
//     EXPECT_EQ(cofactor(1, 0), -3);
//     EXPECT_EQ(cofactor(1, 1), 15);
//     EXPECT_EQ(cofactor(1, 2), -1);
// }

// TEST(MatrixTest, AlgebraicComplement) {
//     Matrix<int> mat(3, 3);
//     mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
//     mat(1, 0) = 0; mat(1, 1) = 1; mat(1, 2) = 4;
//     mat(2, 0) = 5; mat(2, 1) = 6; mat(2, 2) = 0;
//     Matrix<int> algebraicComplement = mat.adjugateMatrix();
//     EXPECT_EQ(algebraicComplement(0, 0), 6);
//     EXPECT_EQ(algebraicComplement(0, 1), -15);
//     EXPECT_EQ(algebraicComplement(0, 2), 4);
// }

TEST(MatrixTest, PredicateCheck) {
    Matrix<int> mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;

    EXPECT_FALSE(mat.isSymmetricMatrix());
    EXPECT_FALSE(mat.isZeroMatrix());

    Matrix<int> mat2(2, 2);
    mat2(0, 0) = 0; mat2(0, 1) = 0;
    mat2(1, 0) = 0; mat2(1, 1) = 0;

    EXPECT_TRUE(mat2.isZeroMatrix());
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}