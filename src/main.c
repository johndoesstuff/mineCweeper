#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int width, height;
int center_x, center_y;

typedef struct {
	int mine;
	int count;
	int revealed;
} Cell;

void drawCell(int x, int y, Cell cell) {
	mvprintw(y + center_y - height/2, x*3 + center_x - 3*width/2, "[-]");
}

void drawBoard(Cell** board) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			drawCell(x, y, board[y][x]);
		}
	}
}

Cell** initializeBoard(int width, int height) {
	Cell** board = (Cell**)malloc(height * sizeof(Cell*));
	for (int i = 0; i < height; i++) {
		board[i] = (Cell*)malloc(width * sizeof(Cell));
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			board[y][x].mine = 0;
			board[y][x].count = 0;
			board[y][x].revealed = 0;
		}
	}

	return board;
}

int main(int argc, char *argv[]) {

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
		return 1;
	}

	width = atoi(argv[1]);
	height = atoi(argv[2]);

	if (width < 8 || height < 8) {
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
		endwin();
		fprintf(stderr, "Too wide of a board for current screen size\n");
		return 1;
	}

	if (height >= max_y) {
		endwin();
		fprintf(stderr, "Too tall of a board for current screen size\n");
		return 1;
	}

	Cell** board = initializeBoard(width, height);

	mvprintw(0, 0, "MineCweeper W: %d, H: %d", width, height);

	center_x = max_x/2;
	center_y = max_y/2;

	drawBoard(board);

	refresh();

	getch();

	endwin();
	return 0;
}
