CC = gcc
CFLAGS =  -Werror -Wall -Wextra -std=c11
PILK = pilk.c
UI = cli/*.c
TETRIS_BACK = back/bricks/*.c back/brickMovement/*.c back/fullLineHandler/*.c back/gameManager/*.c
TETRIS = tetris/*.c
CURSES = -lncurses
CHECK_FLAGS = -lcheck
LIBS = $(CURSES)

pilk:
	$(CC) $(PILK)

s21_matrix_oop.a: s21_matrix_oop.o
	ar rc s21_matrix_oop.a $(LIB_OBJECT)
	ranlib s21_matrix_oop.a
	make clean_libobj

rebuild_lib: clean s21_matrix_oop.a

install: ${TETRIS_BACK}  ${UI} ${TETRIS}
		$(CC) ${CFLAGS} $(LIBS) $^ -o tetris.out

run: 
	./tetris.out

bepis: clean
	$(CC) $(TETRIS_BACK) $(UI) $(TETRIS) $(LIBS) -o bepis
	./bepis

test: clean
	$(CC) $(BACK) back/test/*.c back/test/collision_tests/*.c $(CHECK_FLAGS) -o test.out
	./test.out

clang:
	@cp ../../../../materials/linters/.clang-format .clang-format
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@rm .clang-format


clean:
	rm -rf *.o *.out test.out bepis