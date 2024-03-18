CC = gcc
PILK = pilk.c
UI = cli/*.c
BACK = back/*.c
CURSES = -lncurses
CHECK_FLAGS = -lcheck

pilk:
	$(CC) $(PILK)

bepis: clean
	$(CC) $(BACK) $(UI) $(CURSES) -o bepis
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