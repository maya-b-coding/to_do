//contains the main program for the checklist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "goal_list.h"
#include "date_and_time.h"
#include "dynamic_arrays.h"

#define MAX_INPUT 500
#define ARRAY_SIZE 1

int main()
{
  //print_current_goals();

  char input[MAX_INPUT];
  char ** argv;
  int argc = 0;

  int current_goals_size = 0;
  int completed_goals_size = 0;

  int current_goals_max_size = ARRAY_SIZE;
  int completed_goals_max_size = ARRAY_SIZE;

  goal * completed_goals = new_array(completed_goals_max_size);
  goal * current_goals = new_array(current_goals_max_size);

  int goal_index = 0;
  do
  {
    fgets(input, MAX_INPUT, stdin);

    argv = parse_args(input, &argc);

    if (argc > 0)
    {
      if (strcmp(argv[0], "add") == 0)
      {
        add_goal(argv, argc, &current_goals, &current_goals_size, &current_goals_max_size);
      } else if (strcmp(argv[0], "wday") == 0)
      {
        int wday = get_wday(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        printf("weekday = %d\n", wday);
      } else if (strcmp(argv[0], "show_goals") == 0 || strcmp(argv[0], "sg") == 0)
      {
        printf("Current goals:\n");

        print_goal_array(current_goals, current_goals_size);
      } else if (strcmp(argv[0], "show_complete") == 0 || strcmp(argv[0], "sc") == 0)
      {
        printf("Completed goals:\n");

        print_goal_array(completed_goals, completed_goals_size);
      }

      else if (strcmp(argv[0], "exit") == 0)
      {
        free_parsed_args(argv);
        return 0;
      }
    }

  /*  for (int i = 0; i < argc; i++)
    {
      printf("%s\n", argv[i]);
    }*/

    free_parsed_args(argv);

  } while (strncmp(input, "exit", 4) != 0);

  //free all used memory

  for (int i = 0; i < goal_index; i++)
  {
    free_goal_name(current_goals[i]);
  }
}
