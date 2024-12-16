#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int width, height;
int center_x, center_y;

void drawCell(int x, int y, int mine, int count, int revealed) {
	mvprintw(y + center_y - height/2, x*3 + center_x - 3*width/2, "[-]");
}

int main(int argc, char *argv[]) {

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

	mvprintw(0, 0, "MineCweeper W: %d, H: %d", width, height);

	center_x = max_x/2;
	center_y = max_y/2;
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			drawCell(x, y, 0, 0, 0);
		}
	}




	refresh();

	getch();

	endwin();
	return 0;
}
