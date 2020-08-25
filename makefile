CC=gcc
CFLAGS=-I.
DEPS = goal_list.h date_and_time.h
OBJ = goal_list.o goal_list_func.o date_and_time.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

goal_list: $(OBJ)
	$(CC) -o goal_list goal_list.o goal_list_func.o date_and_time.o

run:
	./goal_list

run_goal_list:
	./goal_list
