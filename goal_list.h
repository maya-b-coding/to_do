#ifndef _GOAL_LIST_H
#define _GOAL_LIST_H

const int MAX_CHARS;
char * DATE_NO_TIME;
char * DATE_W_TIME;

struct goal{

};

void check_errors(int error_status);
void print_date(struct tm * date, int display_time);
int print_current_goals();
int print_past_goals();
int print_all_goals(); // is this function really necessary?

#endif
