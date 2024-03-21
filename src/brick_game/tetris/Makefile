CC = gcc
CFLAGS =  -Werror -Wall -Wextra -std=c11
PILK = pilk.c
UI = cli/*.c
TETRIS_BACK = back/bricks/*.c back/brickMovement/*.c back/fullLineHandler/*.c back/gameInfo/*.c back/field/*.c
TETRIS = tetris/*.c

TEST_SOURCES = test/*.c test/collisionTest/*.c test/movementTest/*.c test/fullLineHandlerTest/*.c

CURSES = -lncurses
CHECK_FLAGS = -lcheck
LIBS = $(CURSES)
G_FLAGS = -lpthread -g -fprofile-arcs -ftest-coverage


pilk:
	$(CC) $(PILK)

s21_matrix_oop.a: s21_matrix_oop.o
	ar rc s21_matrix_oop.a $(LIB_OBJECT)
	ranlib s21_matrix_oop.a
	make clean_libobj

rebuild_lib: clean s21_matrix_oop.a

install: ${TETRIS_BACK}  ${UI} ${TETRIS}
		$(CC) $(LIBS) $^ -o tetris.out

gcov_report: clean
	$(CC) $(CFLAGS) $(TETRIS_BACK) $(TEST_SOURCES) $(CHECK_FLAGS) $(G_FLAGS) -o GcovReport
	./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info --no-external -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html


run: 
	./tetris.out

bepis: clean
	$(CC) $(TETRIS_BACK) $(UI) $(TETRIS) $(LIBS) -o bepis
	./bepis

test: clean
	$(CC) $(TETRIS_BACK) $(TEST_SOURCES) $(CHECK_FLAGS) -o test.out
	./test.out


clang:
	@cp ../../../../materials/linters/.clang-format .clang-format
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@rm .clang-format


clean: clean_gcov_report
	rm -rf *.o *.out test.out bepis
clean_gcov_report:
	rm -rf GcovReport *.gcda *.gcno GcovReport.dSYM *.info report