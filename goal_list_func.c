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

void add_goal(char ** argv, int argc)
{
  printf("adding goal\n");

  goal my_goal;

  if (argc > 2)
  {
    struct tm * date = NULL;
    date = string_to_date(argv[2]);
    if (date != NULL)
    {
      my_goal = create_goal(argv[1], *date, 1);
      free(date);
    } else
    {
      printf("Date is NULL\n");
      return; //eror when converting the date
    }
  }
  else if (argc > 1)
  {
    struct tm empty_date;
    my_goal = create_goal(argv[1], empty_date, 0);
  } else
  {
    printf("invalid input: not enough arguments\n");
  }

  printf("my_goal.name = %s\n", my_goal.name);
}

goal create_goal(char * name, struct tm target_date, int has_target)
{
  goal new_goal;

  new_goal.name = name;
  new_goal.has_target = (char) has_target;
  new_goal.is_completed = 0;
  new_goal.is_expired = 0;

  if (has_target)
  {
    new_goal.date_target = target_date;

  }

  //set date_set to current date
  time_t rawtime;
  time(&rawtime);
  new_goal.date_set = *localtime(&rawtime);

  return new_goal;
}

struct tm * string_to_date(char * str)
{
  if (!is_date(str))
  {
    printf("date enterred INCORRECTLY!\n");
    return NULL;
  }

  int month;
  int day;
  int year;


  printf("num_str = %s\n", num_str);

  month = strn_to_int(str, 2);
  if (month < 1 || month > 12)
  {
    printf("Error: %d is not a valid month\n", month);
    return NULL;
  }

  num_str = strncpy(num_str, str + 6, 2);

  year = atoi(num_str) + 2000;

  num_str = strncpy(num_str, str + 3, 2);

  day = atoi(num_str);

  switch (month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:

      if (day > 31 || day < 1)
      {
        printf("%d is not a valid day in month %d\n", day, month);
        return NULL;
      }
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      if (day > 30 || day < 1)
      {
        printf("%d is not a valid day in month %d\n", day, month);
        return NULL;
      }
      break;

    case 2:
      if (year % 4){
        if (day > 29 || day < 1)
        {
          printf("%d is not a valid day in month %d on a leap year\n", day, month);
          return NULL;
        }
      } else
      {
        if (day > 28 || day < 1)
        {
          printf("%d is not a valid day in month %d on a non-leap year\n", day, month);
          return NULL;
      }
      }
      break;
  }

  printf("valid date good job\n");
  return NULL;
}




int is_num(char c)
{
  switch (c)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return 1;
    default:
      return 0;
  }
}
int is_dash_slash(char c)
{
  switch (c)
  {
    case '/':
    case '\\':
    case '-':
      return 1;
    default:
      return 0;
  }
}

int is_date(char * str)
{
  if (strlen(str) != 8)
  {
    printf("invalid date length, date should be of format MM-DD-YY\n");
    return 0;
  }

  for (int i = 0; i < strlen(str); i++, str++)
  {
    if ((i + 1) % 3 != 0)
    {
      if (!is_num(*str)){
        printf("i = %d\n", i);
        printf("%c is not a num\n", *str);
        printf("invalid date, date should be of format MM-DD-YY\n");
        return 0;
      }
    } else if (!is_dash_slash(*str))
    {
      printf("i = %d\n", i);
      printf("%c is not a dash\n", *str);
      printf("invalid date, date should be of format MM-DD-YY\n");
      return 0;
    }

  }
}

int strn_to_int(char * str, int n)
{
  //converts a string of n characters to an integer
  char copied_str[n + 1];


  int i;
  for (i = 0; i < n && str[i] != '\0'; i++)
  {
    copied_str[i] = str[i];
  }

  copied_str[i] = '\0';

  return atoi(copied_str);
}
