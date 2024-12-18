#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int width, height;
int center_x, center_y;
int game_over;

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
			board[y][x].mine = rand() % 10 == 1; // 1/10 mine chance
			board[y][x].count = 0;
			board[y][x].revealed = 0;
		}
	}

	return board;
}

int main(int argc, char *argv[]) {

	srand(time(NULL));
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
		return 1;
	}

	width = atoi(argv[1]);
	height = atoi(argv[2]);

	int cursor_x, cursor_y;

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

	cursor_x = width/2;
	cursor_y = height/2;

	game_over = 0;
	wchar_t ch;

	while (!game_over) {
		erase();
		drawBoard(board);
		mvprintw(cursor_y + center_y - height/2, cursor_x*3 + center_x - 3*width/2, ">*<");
		refresh();

		ch = getch();

		switch (ch) {
			case KEY_UP:
				if (cursor_y > 0) cursor_y--;
				break;
			case KEY_DOWN:
				if (cursor_y < height - 1) cursor_y++;
				break;
			case KEY_LEFT:
				if (cursor_x > 0) cursor_x--;
				break;
			case KEY_RIGHT:
				if (cursor_x < width - 1) cursor_x++;
				break;
			case 10: //enter
				revealCell(board);
		}
	}
	endwin();
	return 0;
}
