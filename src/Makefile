CC = gcc
CFLAGS =  -Werror -Wall -Wextra -std=c11

PILK = pilk.c
FRONTEND = gui/cli/getUserInput/*.c gui/cli/tetrisStats/*.c gui/cli/timer/*.c gui/cli/ui/*.c gui/cli/window/*.c
TETRIS_BACK = brick_game/tetris/back/bricks/*.c brick_game/tetris/back/brickMovement/*.c brick_game/tetris/back/fullLineHandler/*.c brick_game/tetris/back/gameInfo/*.c brick_game/tetris/back/field/*.c
TETRIS = brick_game/tetris/tetris/*.c
TEST_SOURCES = brick_game/tetris/test/*.c brick_game/tetris/test/collisionTest/*.c brick_game/tetris/test/movementTest/*.c brick_game/tetris/test/fullLineHandlerTest/*.c brick_game/tetris/test/addPointsTest/*.c

CURSES = -lncurses
CHECK_FLAGS = -lcheck
LIBS = $(CURSES)
G_FLAGS = -lpthread -g -fprofile-arcs -ftest-coverage
DIST_DIR = game_archive
OPEN_COMMAND = open

DVI = dvi/README.html

OS := $(shell uname)

ifeq ($(OS),Darwin)
    OPEN_COMMAND= open
    CHECK_FLAGS = -lcheck
else
    OPEN_COMMAND= xdg-open
    CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

all: gcov_report install run

install: ${TETRIS_BACK} $(FRONTEND) ${TETRIS}
		$(CC) $^ $(LIBS)  -o tetris.out

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
	cp -rf MakeFile ${DIST_DIR}
	cp -rf gui ${DIST_DIR}
	cp -rf brick_game ${DIST_DIR}
	cp -rf dvi_data ${DIST_DIR}
	tar -cvf game_archive.tar ${DIST_DIR}
	rm -rf ${DIST_DIR}

dvi:
	$(OPEN_COMMAND) dvi_data/README.html

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
	rm -rf ${DIST_DIR} game_archive.tar