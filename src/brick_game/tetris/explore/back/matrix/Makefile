CC = gcc -Wall -Werror -Wextra -std=c11

LIB_SOURCES = s21_*.c
OBJECT = $(patsubst %*.c, %*.o, $(LIB_SOURCES))
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

OS = $(shell uname -s)

ifeq ($(OS), Linux)
  CHECK_FLAGS = -lpthread -lcheck -pthread -lrt -lm -lsubunit
endif
ifeq ($(OS), Darwin)
  CHECK_FLAGS = -lcheck
endif

all: clean s21_matrix.a

s21_matrix.a:
	$(CC) -c $(LIB_SOURCES) 
	@ar rcs s21_matrix.a $(OBJECT)
	@rm -rf ./*.o

rebuild_lib: clean s21_matrix.a

manual_test: rebuild_lib
	gcc /tests/manual_test.c $(CHECK_FLAGS) s21_matrix.a -o manual_test

test: rebuild_lib
	gcc tests/test_s21_matrix.c s21_matrix.a $(CHECK_FLAGS) -o test
	./test
gcov_report: rebuild_lib
	@gcc $(GCOV_FLAGS) tests/test_s21_matrix.c $(CHECK_FLAGS) $(LIB_SOURCES) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info


clang:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n s21* ./tests/manual_test.c ./tests/test_s21_matrix.c
	clang-format -i s21* ./tests/manual_test.c ./tests/test_s21_matrix.c
	@rm .clang-format


valgrind: test
	valgrind -s  --track-origins=yes --tool=memcheck --leak-check=yes ./test

valgrind_manual: manual_test
	valgrind -s  --track-origins=yes --tool=memcheck --leak-check=yes ./manual_test

clean:
	@rm -rf ./a.out ./*.o ./*.a ./test ./GcovReport ./report ./*.info ./*.gcno ./*gcda ./*.gch tests/.out ./*.out decimal_api/*.gch

