#ifndef __CIRC_BUF_H__
#define __CIRC_BUF_H__

#include <stdlib.h>
#include <string.h>

typedef unsigned int elem;

struct circ_buf {
	elem *buf;
	int len;
	int head;
};

#define POS(head, i, len) ((head) >= (i) ? (head) - (i) : (len) + (head) - (i))

static inline void circ_buf_realloc(struct circ_buf *b, int len)
{
	elem *new_buf = realloc(b->buf, len);
	int i;

	if (!new_buf)
	{
		free(b->buf);
		exit(1);
	}
	
	b->buf = new_buf;
	memset(new_buf + b->len, 0, len - b->len);
	for (i = 0; i < b->len; i++)
		b->buf[POS(b->head, i, len)] = b->buf[POS(b->head, i, b->len)];
	b->len = len;
}

static inline void circ_buf_push(struct circ_buf *b, elem c)
{
	b->head = (b->head + 1) % b->len;
	b->buf[b->head] = c;
}

static inline void circ_buf_free(struct circ_buf *b)
{
	free(b->buf);
}

#endif
