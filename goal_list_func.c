#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "goal_list.h"
#include "date_and_time.h"
#include "dynamic_arrays.h"

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

void add_goal(char ** argv, int argc, goal * goal_array_ptr[], int * array_index, int * array_max_size)
{

  goal my_goal;

  if (argc > 4)
  {
    if (is_date(argv[3]) && is_time(argv[4]))
    {
      struct tm date = string_to_date_w_time(argv[3], argv[4]);
      my_goal = create_goal(argv[2], date, 1, 1);
    } else {
      printf("Date or time is invalid, no goal created\n");
      return;
    }
  } else if (argc > 3)
  {
    if (is_date(argv[3]))
    {
      struct tm date = string_to_date(argv[3]);
      my_goal = create_goal(argv[2], date, 1, 0);

    } else
    {
      printf("Date is invalid, no goal created\n");
      return; //eror when converting the date
    }
  }
  else if (argc > 2)
  {
    struct tm empty_date;
    my_goal = create_goal(argv[2], empty_date, 0, 0);

  } else
  {
    printf("invalid input: not enough arguments\n");
    printf("Command usage: add \"Goal Title\" <target_array> <date>\n");
    return;
  }

  add_element(goal_array_ptr, array_max_size, array_index, my_goal);

}

void set_date_target(goal * array, int index, char * date_str)
{
  if (strcmp(date_str, "none") == 0){
    array[index].has_target = 0;
    array[index].has_target_time = 0;
    printf("Target date for goal [%d] removed\n", index);
  }
  else if (is_date(date_str))
  {
    struct tm date = string_to_date(date_str);
    array[index].has_target = 1;
    array[index].has_target_time = 0;
    array[index].date_target = date;
    printf("Target date for goal [%d] changed\n", index);
  }
}

void set_date_target_w_time(goal * array, int index, char * date_str, char * time_str)
{
  if (is_date(date_str) && is_time(time_str))
  {
    struct tm date = string_to_date_w_time(date_str, time_str);
    array[index].has_target = 1;
    array[index].has_target_time = 1;
    array[index].date_target = date;
    printf("Target date for goal [%d] changed\n", index);
  }
}

void set_name(goal * array, int index, char * new_name)
{
  char * old_name = array[index].name;
  array[index].name = malloc(strlen(new_name) + 1); //dynamically allocated copy of new_name
  strcpy(array[index].name, new_name);
  printf("Goal [%d] changed from \"%s\" to \"%s\"\n", index, old_name, new_name);
  free(old_name);
}

void complete_goal(goal * array, int index)
{
  time_t rawtime;
  time(&rawtime);

  array[index].is_completed = 1;
  array[index].date_completed = *localtime(&rawtime);
}

void renew_goal(goal * array, int index)
{
  array[index].is_completed = 0;
}

int get_target_array(char * target_str)
{
  if (strcmp(target_str, "g") == 0 || strcmp(target_str, "goal") == 0)
  {
    return 0;
  } else if (strcmp(target_str, "c") == 0 || strcmp(target_str, "complete") == 0)
  {
    return 1;
  } else {
    return -1;
  }
}

goal create_goal(char * name, struct tm target_date, int has_target, int has_target_time)
{
  goal new_goal;

  new_goal.name = malloc(strlen(name) + 1);
  strcpy(new_goal.name, name);
  new_goal.has_target = (char) has_target;
  new_goal.has_target_time = has_target_time;
  new_goal.is_completed = 0;

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

void print_goal(goal cur_goal)
{
  printf("%s", cur_goal.name);
  if (cur_goal.has_target)
  {
    printf(" - Target Date: ");
    print_date(&cur_goal.date_target, cur_goal.has_target_time); //default to not showing time
    if (!cur_goal.is_completed)
    {
      time_t rawtime;
      struct tm * cur_date;

      time(&rawtime);
      cur_date = localtime(&rawtime);

      int cmp;
      if (cur_goal.has_target_time)
      {
        cmp = cmp_dates_w_time(&cur_goal.date_target, cur_date);
      } else {
        cmp = cmp_dates(&cur_goal.date_target, cur_date);
      }

      if (cmp > 0)
      {
        printf(" (EXPIRED)");
      }
    }
  }

  if (cur_goal.is_completed)
  {
    printf(" - Completed: ");
    print_date(&cur_goal.date_completed, 1);
  }
  printf("\n");
}

void print_goal_array(goal * array, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("[%d] - ", i);
    print_goal(array[i]);
  }
}

void free_goal_name(goal g)
{
  free(g.name);
  g.name = NULL;
}
