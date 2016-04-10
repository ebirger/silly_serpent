all: snake
 
CFLAGS+=-Wall --coverage
LDFLAGS+=-lncurses --coverage
OBJS:=main.o snake.o ui_ncurses.o world.o

$(OBJS): $(wildcard *.h)

%.o: %.c
	$(CC) $(CFLAGS) -g -o $@ -c $<

snake: $(OBJS)
	$(CC) -g -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJS) snake
