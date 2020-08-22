#ifndef _GOAL_LIST_H
#define _GOAL_LIST_H

const int MAX_CHARS;
char * DATE_NO_TIME;
char * DATE_W_TIME;

typedef struct{
  struct tm date_set;
  struct tm date_target; //day the goal was initially intended to be completeted
  struct tm date_completed;
  char * name;
  int completed; //boolean that tells if it's been completed or not
} goal;

void check_errors(int error_status);
void print_date(struct tm * date, int display_time);
int print_current_goals();
int print_past_goals();
int print_all_goals(); // is this function really necessary?

#endif
