CC=gcc
CFLAGS=-I.
DEPS = goal_list.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

goal_list: goal_list.o goal_list_func.o
	$(CC) -o goal_list goal_list.o goal_list_func.o
