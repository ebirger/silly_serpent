#include "world.h"

static elem next_pos(elem pos, enum snake_dir dir)
{
	return MKPOS(X(pos) + (short)X(dir), Y(pos) + (short)Y(dir));
}

int is_in_snake(struct snake *snake, elem pos, int exclude_head)
{
	int i;

	for (i = exclude_head ? 1 : 0; i < snake->body.len; i++)
	{
		if (pos == snake->body.buf[POS(snake->body.head, i, snake->body.len)])
			return 1;
	}
	return 0;
}

void snake_iter(struct snake *snake, void (*cb)(elem pos))
{
	int i;

	for (i = 0; i < snake->body.len; i++)
		cb(snake->body.buf[POS(snake->body.head, i, snake->body.len)]);
}

void snake_move(struct snake *snake, enum snake_dir dir)
{
	if (dir == opposite_dir(snake->dir))
		return;

	circ_buf_push(&snake->body, next_pos(snake->body.buf[snake->body.head], dir));
	snake->dir = dir;
}
