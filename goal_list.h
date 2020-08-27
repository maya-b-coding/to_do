#ifndef _GOAL_LIST_H
#define _GOAL_LIST_H

typedef struct{
  struct tm date_set;
  struct tm date_target; //day the goal was initially intended to be completeted
  struct tm date_completed;
  char * name;
  char has_target; //boolean telling whether a target date is set
  char is_completed; //boolean that tells if it's been completed or not
  char is_expired; //true if the date_target has been passed but still hasn't been completed
} goal;

void check_errors(int error_status);

void add_goal(char ** argv, int argc, goal * goal_array_ptr[], int * array_index, int *array_max_size);
void free_goal_name(goal g); //frees the name string within each goal
char **parse_args(char * arguments, int *argc);
void free_parsed_args(char **argv);
void print_goal(goal new_goal);
void print_goal_array(goal * array, int size);

goal create_goal(char * name, struct tm target_date, int has_target);
#endif
