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

void add_goal(char ** argv, int argc, goal goal_array[], int * array_index)
{

  goal my_goal;

  if (argc > 2)
  {
    if (is_date(argv[2]))
    {
      struct tm date = string_to_date(argv[2]);
      my_goal = create_goal(argv[1], date, 1);

    } else
    {
      printf("Date is invalid, no goal created\n");
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
    printf("Command usage: add \"Goal Title\" <date>\n");
    return;
  }

  goal_array[*array_index] = my_goal;
  (*array_index)++;
}

goal create_goal(char * name, struct tm target_date, int has_target)
{
  goal new_goal;

  new_goal.name = malloc(strlen(name) + 1);
  strcpy(new_goal.name, name);
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

struct tm string_to_date(char * str)
{
  //we assume this string has already been tested and shown to be valid
  int month;
  int day;
  int year;

  month = strn_to_int(str, 2);
  year = strn_to_int(str + 6, 2) + 2000;
  day = strn_to_int(str + 3, 2);

  struct tm new_date = create_date(month, day, year);
  return new_date;
}

int get_wday(int month, int day, int year){
  int wday = year % 100;
  wday = wday / 4;
  wday += day;
  switch (month) //add the month's key value
  {
    case 1:
    case 10:
      wday += 1;
      break;
    case 2:
    case 3:
    case 11:
      wday += 4;
      break;
    case 5:
      wday += 2;
      break;
    case 6:
      wday += 5;
      break;
    case 8:
      wday += 3;
      break;
    case 9:
    case 12:
      wday += 6;
      break;
    case 4:
    case 7:
    default:
      break;
  }

  if (year / 100 == 20) //this is dependednt on the century... though I doubt anyone will use this in 100 years
  {
    wday += 6;
  }

  wday += (year % 100);

  wday -= 1;
  if (month <= 2 & !(year % 4)){
    wday -= 1;
  }
  wday = wday % 7;



  return wday;
}

int get_yday(int month, int day, int year){
  int yday = 0;

  for (int i = 1; i < month; i++)
  {
    switch(i)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:

        yday += 31;
        break;
      case 4:
      case 6:
      case 9:
      case 11:
        yday += 30;
        break;
      case 2:
        if (!(year % 4))
        {
          yday += 29;
        } else
        {
          yday += 28;
        }
        break;
      default:
        break;
    }
  }

  yday = yday + day - 1;
  return yday;
}

struct tm create_date(int month, int day, int year){

  struct tm new_date;

  new_date.tm_sec = 0;
  new_date.tm_min = 0;
  new_date.tm_hour = 0;

  new_date.tm_mday = day;
  new_date.tm_mon = month - 1;
  new_date.tm_year = year - 1900;

  new_date.tm_wday = get_wday(month, day, year);
  new_date.tm_yday = get_yday(month, day, year);

  return new_date;

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
        printf("invalid date, date should be of format MM-DD-YY\n");
        return 0;
      }
    } else if (!is_dash_slash(*str))
    {
      printf("invalid date, date should be of format MM-DD-YY\n");
      return 0;
    }

  }

  int month;
  int day;
  int year;

  month = strn_to_int(str, 2);
  if (month < 1 || month > 12)
  {
    printf("Error: %d is not a valid month\n", month);
    return 0;
  }

  year = strn_to_int(str + 6, 2) + 2000;

  day = strn_to_int(str + 3, 2);

  switch (month) //check if the day of the month is valid
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
        return 0;
      }
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      if (day > 30 || day < 1)
      {
        printf("%d is not a valid day in month %d\n", day, month);
        return 0;
      }
      break;

    case 2:
      if (!(year % 4)){
        if (day > 29 || day < 1)
        {
          printf("%d is not a valid day in month %d of a leap year\n", day, month);
          return 0;
        }
      } else
      {
        if (day > 28 || day < 1)
        {
          printf("%d is not a valid day in month %d of a non-leap year\n", day, month);
          return 0;
        }
      }
      break;

    default:
      break;
  }
  return 1;
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

void print_goal(goal cur_goal)
{
  printf("Goal: %s", cur_goal.name);
  if (cur_goal.has_target)
  {
    printf(" - Target Date: ");
    print_date(&cur_goal.date_target, 0); //default to not showing time
  }
  printf("\n");
}

void free_goal_name(goal g)
{
  free(g.name);
  g.name = NULL;
}
