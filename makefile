CC=gcc
CFLAGS=-I.
DEPS = goal_list.h
OBJ = goal_list.o goal_list_func.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

goal_list: $(OBJ)
	$(CC) -o goal_list goal_list.o goal_list_func.o

run:
	./goal_list

run_goal_list:
	./goal_list
