CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g 
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -lgtest -lgtest_main -pthread

HEADERS = matrix/matrix.hpp
TEST_SRC = tests/matrix_tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_OBJ_COV = $(TEST_SRC:.cpp=.gcov.o)
TEST_BIN = tests/tests
GCOV_REPORT_DIR = report

.PHONY: all clean test gcov_report rebuild

# Цель по умолчанию - сборка и тестирование
all: test

# Компиляция тестов без покрытия
$(TEST_OBJ): $(TEST_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция тестов с флагами покрытия
$(TEST_OBJ_COV): $(TEST_SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

# Линковка тестов и выполнение без покрытия
test: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_OBJ) $(GTEST_FLAGS)
	./$(TEST_BIN)

# Линковка тестов и выполнение с покрытием
gcov_report: $(TEST_OBJ_COV)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(TEST_OBJ_COV) $(GTEST_FLAGS)
	./$(TEST_BIN)
	mkdir -p $(GCOV_REPORT_DIR)
	# Создание отчета о покрытии с помощью lcov
	lcov -t "matrix_tests" -o $(GCOV_REPORT_DIR)/coverage.info -c -d . --ignore-errors mismatch --include '*.hpp'
	# Генерация HTML-отчета о покрытии
	genhtml -o $(GCOV_REPORT_DIR) $(GCOV_REPORT_DIR)/coverage.info

# Очистка проекта
clean:
	rm -f $(TEST_OBJ) $(TEST_OBJ_COV) $(TEST_BIN)
	rm -rf $(GCOV_REPORT_DIR)
	rm -f *.gcda *.gcno *.gcov
	rm -f tests/*.gcda
	rm -f tests/*.gcno
	rm -f tests/*.gcov

rebuild: clean all
