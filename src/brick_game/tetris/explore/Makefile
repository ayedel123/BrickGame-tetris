CC = gcc
PILK = pilk.c
UI = cli/*.c
BACK = back/*.c
CURSES = -lncurses
CHECK_FLAGS = -lcheck

pilk:
	$(CC) $(PILK)

bepis:
	$(CC) $(BACK) $(UI) $(CURSES)

test: clean
	$(CC) $(BACK) back/test/*.c back/test/collision_tests/*.c $(CHECK_FLAGS) -o test.out
	./test.out

clean:
	rm -rf *.o *.out test.out