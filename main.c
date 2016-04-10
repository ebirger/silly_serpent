#include <stdio.h>

#include "snake.h"
#include "world.h"
#include "ui.h"

static int illegal_pos(struct snake *snake, elem pos, int exclude_head)
{
	return X(pos) == 0 || Y(pos) == 0 || X(pos) > MAXX ||
	     Y(pos) > MAXY || is_in_snake(snake, pos, exclude_head);
}

static void new_apple_position(struct snake *snake)
{
	do
	{
		apple = MKPOS(rand() % MAXX, rand() % MAXY);
	} while(illegal_pos(snake, apple, 0));
}

static void on_frame(void)
{
	struct snake *snake = &g_snake;

	snake_move(snake, snake->dir);

	if (illegal_pos(snake, snake_head(snake), 1))
		ui_game_over();

	if (snake_head(snake) == apple)
	{
		snake_grow(snake);
		new_apple_position(snake);
	}
}

static void on_keypress(enum snake_dir dir)
{
	snake_move(&g_snake, dir); 
}

static const struct ui_cbs cbs = {
	.on_frame = on_frame,
	.on_keypress = on_keypress,
};

int main(int argc, char *argv[])
{
	ui_init(argc, argv);

	circ_buf_realloc(&g_snake.body, 3);
	circ_buf_push(&g_snake.body, MKPOS(1, 1));
	circ_buf_push(&g_snake.body, MKPOS(1, 2));
	circ_buf_push(&g_snake.body, MKPOS(1, 3));

	g_snake.dir = SNAKE_DIR_RIGHT;
	new_apple_position(&g_snake);

	ui_run(&cbs);

	ui_uninit();
	return 0;
}
