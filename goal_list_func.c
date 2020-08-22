#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <goal_list.h>

const int MAX_CHARS = 20;
char * DATE_NO_TIME = "%x";
char * DATE_W_TIME = "%x - %I:%M%p";

void check_errors(int error_status)
{
  switch (error_status) {
    case 0:
      return;
    default:
      printf("Error encountered");
      return;
  }
}

int print_current_goals(){
  return 0;
}

void print_date(struct tm * date, int display_time){
  char * format_type = display_time == 0 ? DATE_NO_TIME : DATE_W_TIME;
  char date_string [MAX_CHARS];

  strftime(date_string, MAX_CHARS, format_type, date); //can i drop the size_t?

  printf("%s\n", date_string);
}

char **parse_args(char * arguments, int *argc)
{
  //first we must count the arguments
  *argc = 0;
  char * cur_char = arguments;
  char in_arg = 0; //whether or not cur_char is already in the middle of some argument
  while (*cur_char != '\n' && *cur_char != '\0')
  {
    if (*cur_char == ' ')
    {
      in_arg = 0;
    } else if (!in_arg)
    {
      *argc = *argc + 1;
      in_arg = 1;
    }
    cur_char++;
  }

  printf("argument count = %d \n", *argc);
}
void free_parsed_args(char **argv);
