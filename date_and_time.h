#ifndef _DATE_AND_TIME_H
#define _DATE_AND_TIME_H

const int MAX_CHARS;
char * DATE_NO_TIME;
char * DATE_W_TIME;

char * date_to_str(struct tm * date, int display_time);

void print_goal_array(goal array[], int size);

int is_num(char c);
int is_dash_slash(char c);
int is_date(char * str);

int strn_to_int(char * str, int n);
int get_wday(int month, int day, int year);
int get_yday(int month, int day, int year);

struct tm string_to_date(char * str);
struct tm create_date(int month, int day, int year);


#endif
