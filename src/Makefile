CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g 
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -lgtest -lgtest_main -pthread

HEADERS = matrix/matrix.hpp sparse_matrix/sparse_matrix.hpp
TEST_SRC = tests/matrix_tests.cpp tests/sparse_matrix_tests.cpp tests/main_tests.cpp
TEST_OBJ_DIR = obj
TEST_OBJ = $(patsubst tests/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
TEST_BIN = tests/tests
GCOV_REPORT_DIR = report
GCOV_OBJ_DIR = gcov_obj
GCOV_OBJ = $(patsubst tests/%.cpp,$(GCOV_OBJ_DIR)/%.gcov.o,$(TEST_SRC))

DOXYGEN_CONFIG = Doxyfile
DOXYGEN_OUTPUT_DIR = docs

.PHONY: all clean test gcov_report rebuild format check_format doxygen clean_doxygen

# Цель по умолчанию - сборка и тестирование
all: test

# Создание директории для объектных файлов
$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

# Создание директории для gcov объектов
$(GCOV_OBJ_DIR):
	mkdir -p $(GCOV_OBJ_DIR)

# Компиляция тестов без покрытия
$(TEST_OBJ): $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: tests/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Линковка тестов и выполнение без покрытия
test: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_OBJ) $(GTEST_FLAGS)
	./$(TEST_BIN)

# Компиляция тестов с флагами покрытия
$(GCOV_OBJ): $(GCOV_OBJ_DIR)

$(GCOV_OBJ_DIR)/%.gcov.o: tests/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

# Линковка тестов и выполнение с покрытием
gcov_report: $(GCOV_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_BIN) $(GCOV_OBJ) $(GTEST_FLAGS)
	./$(TEST_BIN)
	mkdir -p $(GCOV_REPORT_DIR)
	lcov -t "matrix_tests" -o $(GCOV_REPORT_DIR)/coverage.info -c -d . --ignore-errors mismatch --include '*.hpp'
	genhtml -o $(GCOV_REPORT_DIR) $(GCOV_REPORT_DIR)/coverage.info

# Проверка форматирования файлов с помощью clang-format
check_format:
	@clang-format -n $(HEADERS) $(TEST_SRC)

# Проверка и форматирование всех hpp и cpp файлов
format: check_format
	@clang-format -i $(HEADERS) $(TEST_SRC)	

# Генерация документации Doxygen
doxygen: $(DOXYGEN_CONFIG)
	@doxygen $(DOXYGEN_CONFIG)

# Очистка сгенерированной документации
clean_doxygen:
	rm -rf $(DOXYGEN_OUTPUT_DIR)

# Очистка проекта
clean:
	rm -f $(TEST_OBJ) $(GCOV_OBJ) $(TEST_BIN)
	rm -rf $(GCOV_REPORT_DIR) $(TEST_OBJ_DIR) $(GCOV_OBJ_DIR) $(DOXYGEN_OUTPUT_DIR)

rebuild: clean all
