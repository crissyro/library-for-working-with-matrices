CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g 
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -lgtest -lgtest_main -pthread

SRC = matrix.cpp
OBJ = $(SRC:.cpp=.o)
OBJ_COV = $(SRC:.cpp=.gcov.o)
TEST_SRC = tests/tests.cpp
TEST_OBJ = $(SRC:.cpp=.o)
TEST_OBJ_COV = $(SRC:.cpp=.gcov.o)
TARGET = matrix.a 
TARGET_COV = matrix_cov.a 
TEST_BIN = tests/tests 
GCOV_REPORT_DIR = report 

.PHONY: all clean test gcov_report rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

$(TARGET_COV): $(OBJ_COV)
	ar rcs $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.gcov.o: %.cpp
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

test: $(TARGET_COV) $(TEST_OBJ_COV)  
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) $(GTEST_FLAGS)
	./$(TEST_BIN)

gcov_report: $(TARGET_COV) $(TEST_OBJ_COV) 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(TEST_OBJ_COV) $(TARGET_COV) $(GTEST_FLAGS)
	./$(TEST_BIN)
	mkdir -p $(GCOV_REPORT_DIR)
	lcov -t "s21_matrix_oop" -o $(GCOV_REPORT_DIR)/coverage.info -c -d . --ignore-errors mismatch --include 's21_matrix_oop.cpp'
	genhtml -o $(GCOV_REPORT_DIR) $(GCOV_REPORT_DIR)/coverage.info



clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TARGET_COV) $(TEST_BIN)
	rm -rf $(GCOV_REPORT_DIR)
	rm -f *.gcda *.gcno *.gcov *.gcov.o
	rm -f tests/*.gcda
	rm -f tests/*.gcov
	rm -f tests/*.gcov.o
	rm -f tests/*.gcno

rebuild: clean all



