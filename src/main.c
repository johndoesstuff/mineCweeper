#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int width, height;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
		return 1;
	}

	width = atoi(argv[1]);
	height = atoi(argv[2]);

	if (width <= 8 || height <= 8) {
		fprintf(stderr, "Width and height must be at least 8.\n");
		return 1;
	}
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	if (width*3 >= max_x) {
		fprintf(stderr, "Too wide of a board for current screen size");
	}

	if (height >= max_y) {
		fprintf(stderr, "Too tall of a board for current screen size");
	}

	mvprintw(0, 0, "MineCweeper");
	refresh();

	getch();

	endwin();
	return 0;
}
