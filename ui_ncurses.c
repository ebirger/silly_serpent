#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
#include "ui.h"
#include "world.h"

static int game_running = 1;

int MAXX, MAXY;

void ui_uninit(void)
{
	endwin();
}

void ui_init(int argc, char *argv[])
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE); /* Non blocking getch() */
	keypad(stdscr, TRUE); /* Fix arrow keys */
	curs_set(0); /* hide cursor */
	MAXX = COLS;
	MAXY = LINES;
}

static enum snake_dir map_key(int c)
{
	if (c == 'k' || c == KEY_UP)
		return SNAKE_DIR_UP;
	if (c == 'j' || c == KEY_DOWN)
		return SNAKE_DIR_DOWN;
	if (c == 'h' || c == KEY_LEFT)
		return SNAKE_DIR_LEFT;
	if (c == 'l' || c == KEY_RIGHT)
		return SNAKE_DIR_RIGHT;

	return SNAKE_DIR_UNKOWN;
}

static void draw_snake_cb(elem pos)
{
	mvaddch(Y(pos), X(pos), 'X');
}

static void draw_snake(struct snake *snake)
{
	snake_iter(snake, draw_snake_cb);
}

static void draw_apple(void)
{
	mvaddch(Y(apple), X(apple), 'o');
}

void ui_game_over(void)
{
	mvprintw(MAXY / 2, MAXX / 2, "GAME OVER!!!");

	nodelay(stdscr, FALSE);
	getch();

	game_running = 0;
}

void ui_run(const struct ui_cbs *cbs)
{
	while (game_running)
	{
		int c = getch();

		if (c == 'q')
			break;

		if (c != ERR)
			cbs->on_keypress(map_key(c));
		else
			cbs->on_frame();

		clear();
		box(stdscr, '|', '-');
		draw_snake(&g_snake);
		draw_apple();
		refresh();
		usleep(90000);
	}
}
