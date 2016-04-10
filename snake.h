#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "circ_buf.h"
#include "world.h"

enum snake_dir {
	SNAKE_DIR_UNKOWN = 0x00000000,
	SNAKE_DIR_UP = 0xffff0000,
	SNAKE_DIR_DOWN = 0x00010000,
	SNAKE_DIR_LEFT = 0x0000ffff,
	SNAKE_DIR_RIGHT = 0x00000001,
};

static inline enum snake_dir opposite_dir(enum snake_dir dir)
{
	return MKPOS((short)X(dir) * -1, (short)Y(dir) * -1);
}

struct snake {
	struct circ_buf body;
	enum snake_dir dir;
};

static inline elem snake_head(struct snake *snake)
{
	return snake->body.buf[snake->body.head];
}

static inline void snake_grow(struct snake *snake)
{
	circ_buf_realloc(&snake->body, snake->body.len + 1);
}

int is_in_snake(struct snake *snake, elem pos, int exclude_head);
void snake_move(struct snake *snake, enum snake_dir dir);
void snake_iter(struct snake *snake, void (*cb)(elem pos));

#endif
