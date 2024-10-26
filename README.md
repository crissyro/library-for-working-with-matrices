
# library-for-working-with-matrices
Coursework on programming basics in C++ at BSTU named after V.G. Shukhov

## Matrix Library

This project is a C++ library for working with various types of matrices, including dense, sparse, and block matrices. The library provides a wide range of functionalities for matrix operations, manipulation, and analysis. It aims to facilitate efficient handling of matrix data structures, especially in applications where sparsity is a significant factor.

### Features

- **Dense Matrix Operations**: Support for standard matrix operations such as addition, subtraction, multiplication, and transposition.
- **Sparse Matrix Representation**: Efficient storage and manipulation of sparse matrices, including operations tailored for sparse data.
- **Block Matrix Support**: Capabilities to handle block matrices, allowing for more advanced matrix manipulations and computations.
- **Comprehensive Testing**: Includes unit tests to ensure the reliability and correctness of the implemented functionalities. Note that tests for block matrices are currently not implemented due to time constraints.
- **Documentation**: Automatically generated documentation using Doxygen.

### Student Errors

Please note that this project may contain some student errors as it is part of a coursework assignment. Users are encouraged to review the code and contribute improvements.

## Getting Started

### Prerequisites

- C++17 compiler (e.g., g++)
- Make
- Doxygen (for documentation generation)
- Google Test (for testing)

### Building the Library

To build the library and run the tests, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/crissyro/library-for-working-with-matrices.git
   cd library-for-working-with-matrices
   ```

2. Use `make` to build the project:
   ```bash
   make
   ```

3. Run tests:
   ```bash
   make test
   ```

4. Generate a code coverage report (optional):
   ```bash
   make gcov_report
   ```

### Makefile Targets

- `all`: The default target that builds the library and runs the tests.
- `test`: Compiles and runs the tests without coverage.
- `gcov_report`: Compiles and runs the tests with coverage, generating coverage reports using lcov and genhtml.
- `format`: Checks and formats all `.hpp` and `.cpp` files using clang-format.
- `doxygen`: Generates documentation using Doxygen based on the provided configuration file.
- `clean`: Cleans up object files, test binaries, coverage reports, and generated documentation.
- `clean_doxygen`: Cleans up the generated Doxygen documentation.
- `rebuild`: Cleans the project and rebuilds it from scratch.

## Usage

To use the library, include the headers in your C++ project as follows:

```cpp
#include "matrix/matrix.hpp"
#include "sparse_matrix/sparse_matrix.hpp"
#include "block_matrix/block_matrix.hpp"
```

### Example

Here is a simple example of how to create a dense matrix and perform some operations:

```cpp
#include "matrix/matrix.hpp"

int main() {
    matrix_lib::Matrix<int> denseMatrix(3, 3); // Create a 3x3 dense matrix
    denseMatrix.setValue(0, 0, 1);
    denseMatrix.setValue(1, 1, 2);
    denseMatrix.setValue(2, 2, 3);
    denseMatrix.print(); // Print the matrix
    return 0;
}
```

## Documentation

To generate the documentation for the library, you can run the following command:

```bash
make doxygen
```

The generated documentation will be available in the `docs` directory.

## Contributing

Contributions are welcome! If you have suggestions for improvements or features, please create an issue or submit a pull request.

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE. See the [LICENSE](LICENSE) file for details.