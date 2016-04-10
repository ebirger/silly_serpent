#ifndef __WORLD_H__
#define __WORLD_H__

#define Y(pos) (((pos) >> 16) & 0xffff)
#define X(pos) ((pos) & 0xffff)
#define MKPOS(x, y) ((((y) & 0xffff) << 16) | ((x) & 0xffff))

#include "snake.h"

extern elem apple;
extern struct snake g_snake;

#endif
