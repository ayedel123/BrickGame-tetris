CC = gcc
CFLAGS =  -Werror -Wall -Wextra -std=c11
PILK = pilk.c
FRONTEND = ../../gui/cli/*.c
TETRIS_BACK = back/bricks/*.c back/brickMovement/*.c back/fullLineHandler/*.c back/gameInfo/*.c back/field/*.c
TETRIS = tetris/*.c
TEST_SOURCES = test/*.c test/collisionTest/*.c test/movementTest/*.c test/fullLineHandlerTest/*.c test/addPointsTest/*.c

CURSES = -lncurses
CHECK_FLAGS = -lcheck
LIBS = $(CURSES)
G_FLAGS = -lpthread -g -fprofile-arcs -ftest-coverage
DIST_DIR = ../../game_archive

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif

all: gcov_report install run

install: ${TETRIS_BACK} $(FRONTEND) ${TETRIS}
		$(CC) $(LIBS) $^ -o tetris.out

uninstall:
	rm -f tetris.out

gcov_report: clean clean_record
	$(CC) $(CFLAGS) $(TETRIS_BACK) $(TEST_SOURCES) $(CHECK_FLAGS) $(G_FLAGS) -o GcovReport
	./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info --no-external -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html
	make clean_gcov

dist: clean_dist
	mkdir -p ${DIST_DIR}
	cp -rf ../../brick_game ${DIST_DIR}/brick_game
	tar -czvf ../../game_archive.tar.gz ${DIST_DIR}
	rm -rf ${DIST_DIR}

dvi:
	$(OPEN_COMMAND) ./dvi/README.html

run: 
	./tetris.out

test: clean
	$(CC) $(TETRIS_BACK) $(TEST_SOURCES) $(CHECK_FLAGS) -o test.out
	./test.out


clang:
	@cp ../../../../materials/linters/.clang-format .clang-format
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@rm .clang-format


clean: clean_gcov clean_dist
	rm -rf *.o *.out test.out bepis report 

clean_gcov: clean_record
	rm -rf GcovReport *.gcda *.gcno GcovReport.dSYM *.info

clean_record:
	rm -rf record

clean_dist:
	rm -rf ${DIST_DIR} ../../game_archive.tar.gz