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

TEST(MatrixTest, ExceptionInverseMatrix) {
    Matrix<int> mat(2, 3);
    EXPECT_THROW(mat.inverseMatrix(), std::logic_error);
}

TEST(MatrixTest, ExceptionCofactorZeroDeterminantMatrix) {
    Matrix<int> mat(2, 2);
    EXPECT_EQ(mat.determinant(), 0);
    mat.makeIdentityMatrix();
    EXPECT_THROW(mat.inverseMatrix(), std::runtime_error);
}

TEST(MatrixTest, Determinant) {
    Matrix<int> mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;
    EXPECT_EQ(mat.determinant(), -2);

    Matrix<int> mat3(3, 3);
    mat3(0, 0) = 1; mat3(0, 1) = 2; mat3(0, 2) = 3;
    mat3(1, 0) = 2; mat3(1, 1) = 4; mat3(1, 2) = 6;
    mat3(2, 0) = 3; mat3(2, 1) = 6; mat3(2, 2) = 9;
    EXPECT_EQ(mat3.determinant(), 0);

    Matrix<float> mat33(3, 3);
    mat33(0, 0) = 1.0; mat33(0, 1) = 2.0; mat33(0, 2) = 3.0;
    mat33(1, 0) = 2.0; mat33(1, 1) = 4.0; mat33(1, 2) = 6.0;
    mat33(2, 0) = 3.0; mat33(2, 1) = 6.0; mat33(2, 2) = 9.0;
    EXPECT_EQ(mat33.determinant(), 0.0);

    int arr4[4][4] = {{3, 2, 1, 5}, {1, 0, 2, 3}, {4, 3, 2, 1}, {0, 1, 0, 2}};

    Matrix<int> mat4(arr4);

    EXPECT_EQ(mat4.determinant(), -37);

    int arr5[5][5] = {
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 3, 5, 2, 4},
        {4, 5, 2, 1, 3},
        {2, 1, 4, 5, 3}
    };

    Matrix<int> mat5(arr5);

    EXPECT_EQ(mat5.determinant(), 0);  
    
    int arr6[6][6] = {
        {2, 3, 1, 5, 4, 6},
        {1, 2, 5, 4, 3, 6},
        {3, 5, 2, 1, 6, 4},
        {6, 1, 4, 3, 5, 2},
        {4, 6, 3, 2, 1, 5},
        {5, 4, 6, 1, 2, 3}
    };

    Matrix<int> mat6(arr6);

    EXPECT_EQ(mat6.determinant(), 819);  

}

TEST(MatrixTest, InverseMatrix) {
    Matrix<double> mat(2, 2);
    mat(0, 0) = 4.0; mat(0, 1) = 7.0;
    mat(1, 0) = 2.0; mat(1, 1) = 6.0;

    Matrix<double> inv = mat.inverseMatrix();

    EXPECT_DOUBLE_EQ(inv(0, 0), 0.6);
    EXPECT_DOUBLE_EQ(inv(0, 1), -0.7);
    EXPECT_DOUBLE_EQ(inv(1, 0), -0.2);
    EXPECT_DOUBLE_EQ(inv(1, 1), 0.4);
}

TEST(MatrixTest, CofactorMatrix) {
    Matrix<int> mat(3, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 0; mat(1, 1) = 1; mat(1, 2) = 4;
    mat(2, 0) = 5; mat(2, 1) = 6; mat(2, 2) = 0;

    Matrix<int> cofactor = mat.cofactorMatrix();

    EXPECT_EQ(cofactor(0, 0), -24);  
    EXPECT_EQ(cofactor(0, 1), 20);   
    EXPECT_EQ(cofactor(0, 2), -5);   
    EXPECT_EQ(cofactor(1, 0), 18);   
    EXPECT_EQ(cofactor(1, 1), -15);  
    EXPECT_EQ(cofactor(2, 0), 5);    
    EXPECT_EQ(cofactor(2, 1), -4);   
    EXPECT_EQ(cofactor(2, 2), 1);  
}

TEST(MatrixTest, AlgebraicComplement) {
    Matrix<int> mat(3, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 0; mat(1, 1) = 1; mat(1, 2) = 4;
    mat(2, 0) = 5; mat(2, 1) = 6; mat(2, 2) = 0;

    Matrix<int> algebraicComplement = mat.adjugateMatrix();

    EXPECT_EQ(algebraicComplement(0, 0), -24);
    EXPECT_EQ(algebraicComplement(0, 1), 18);
    EXPECT_EQ(algebraicComplement(0, 2), 5);
    EXPECT_EQ(algebraicComplement(1, 0), 20);
    EXPECT_EQ(algebraicComplement(1, 1), -15);
    EXPECT_EQ(algebraicComplement(1, 2), -4);
    EXPECT_EQ(algebraicComplement(2, 0), -5);
    EXPECT_EQ(algebraicComplement(2, 1), 4);
    EXPECT_EQ(algebraicComplement(2, 2), 1);
}


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

TEST(MatrixTest, IsSymmetricMatrix) {
    Matrix<int> mat(3, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 2; mat(1, 1) = 4; mat(1, 2) = 5;
    mat(2, 0) = 3; mat(2, 1) = 5; mat(2, 2) = 6;
    EXPECT_TRUE(mat.isSymmetricMatrix());

    mat(0, 1) = 0;
    EXPECT_FALSE(mat.isSymmetricMatrix());
}

TEST(MatrixTest, IsIdentityMatrix) {
    Matrix<int> identity = Matrix<int>().makeIdentityMatrix(3);
    EXPECT_TRUE(identity.isIdentityMatrix());

    identity(0, 0) = 0;
    EXPECT_FALSE(identity.isIdentityMatrix());
}

TEST(MatrixTest, IsZeroMatrix) {
    Matrix<int> zeroMat = Matrix<int>().makeZeroMatrix(3, 3);
    EXPECT_TRUE(zeroMat.isZeroMatrix());

    zeroMat(0, 0) = 1;
    EXPECT_FALSE(zeroMat.isZeroMatrix());
}

TEST(MatrixTest, IsSingularMatrix) {
    Matrix<int> singular(2, 2);
    singular(0, 0) = 1; singular(0, 1) = 2;
    singular(1, 0) = 2; singular(1, 1) = 4;
    EXPECT_TRUE(singular.isSingular());

    singular(1, 1) = 3;
    EXPECT_FALSE(singular.isSingular());
}

TEST(MatrixTest, IsDiagonalMatrix) {
    Matrix<int> diagonal(3, 3);
    diagonal(0, 0) = 1; diagonal(1, 1) = 2; diagonal(2, 2) = 3;
    EXPECT_TRUE(diagonal.isDiagonalMatrix());

    diagonal(0, 1) = 1;
    EXPECT_FALSE(diagonal.isDiagonalMatrix());
}

TEST(MatrixTest, IsOrthogonalMatrix) {
    Matrix<int> ortho = Matrix<int>().makeIdentityMatrix(3);
    EXPECT_TRUE(ortho.isOrthogonalMatrix());

    ortho(0, 0) = 2;
    EXPECT_FALSE(ortho.isOrthogonalMatrix());
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}