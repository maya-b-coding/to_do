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
  char in_quote = 0; //whether or not cur_char is in a quote
  while (*cur_char != '\0')
  {
    if (!in_quote)
    {
      if (*cur_char == ' ' || *cur_char == '\n')
      {
        in_arg = 0;
      } else if (*cur_char == '\"')
      {
        char * next_char = cur_char + 1;

        if (*next_char != '\0' && *next_char != '\n' && *next_char != '\"')
        {
          *argc = *argc + 1;
        }

        in_arg = 0;
        in_quote = 1;
      } else if (!in_arg)
      {
        *argc = *argc + 1;

        in_arg = 1;
      }
    } else if (*cur_char == '\"')
    {
      in_quote = 0;
    }
    cur_char++;
  }

  char ** argv;

  if (!(argv = malloc((*argc) * sizeof(char *))))
  {
    printf("error allocating memory for argv in parse_args\n");
    return NULL;
  }

  cur_char = arguments;
  int i = 0;
  in_arg = 0;
  in_quote = 0;

  while (*cur_char != '\0')
  {
    if (!in_quote)
    {
      if (*cur_char == ' ' || *cur_char == '\n')
      {
        in_arg = 0;
        *cur_char = '\0';
      } else if (*cur_char == '\"')
      {
        in_arg = 0;
        in_quote = 1;
        *cur_char = '\0';
        char * next_char = cur_char + 1;

        if (*next_char != '\0' && *next_char != '\n' && *next_char != '\"')
        {
          argv[i] = next_char;
          i++;
        }
      } else if (!in_arg)
      {
        in_arg = 1;
        argv[i] = cur_char;
        i++;
      }
    } else if (*cur_char == '\"' || *cur_char == '\n')
    {
      *cur_char = '\0';
      in_quote = 0;
    }
    cur_char++;
  }

  return argv;
}

void free_parsed_args(char **argv)
{
  if (argv)
  {
    free(argv);
  }
}

void add_goal(char ** argv, int argc){
  printf("adding goal\n");
}
