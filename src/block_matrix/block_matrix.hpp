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

};

}
