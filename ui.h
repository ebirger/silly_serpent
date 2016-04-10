#ifndef __UI_H__
#define __UI_H__

#include "snake.h"

extern int MAXX, MAXY;

struct ui_cbs {
	void (*on_frame)(void);
	void (*on_keypress)(enum snake_dir dir);
};

void ui_uninit(void);
void ui_init(int argc, char *argv[]);

void ui_game_over(void);
void ui_run(const struct ui_cbs *cbs);

#endif
