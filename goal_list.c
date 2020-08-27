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
      char * command = argv[0];
      char * target_str = NULL;

      if ((strcmp(command, "add")) == 0 || (strcmp(command, "a") == 0))
      {
        if (argc <= 1)
        {
          printf("Please specify a target array in your second argument. Type c/complete for completed goals, or g/goals for current goals.\n");
        } else {
          switch (get_target_array(argv[1]))
          {
            case 0:
              add_goal(argv, argc, &current_goals, &current_goals_size, &current_goals_max_size);
              break;
            case 1:
              add_goal(argv, argc, &completed_goals, &completed_goals_size, &completed_goals_max_size);
              break;
            default:
              printf("Invalid target array. Type c/complete for completed goals, or g/goals for current goals.\n");
          }
        }

      } else if (strcmp(command, "wday") == 0)
      {
        int wday = get_wday(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        printf("weekday = %d\n", wday);
      } else if (strcmp(command, "show") == 0 || strcmp(argv[0], "s") == 0)
      {if (argc <= 1)
      {
        printf("Please specify a target array in your second argument. Type c/complete for completed goals, or g/goals for current goals.\n");
      } else {
        switch (get_target_array(argv[1]))
        {
          case 0:
            printf("Current goals:\n");
            print_goal_array(current_goals, current_goals_size);
            break;
          case 1:
            printf("Completed goals:\n");
            print_goal_array(completed_goals, completed_goals_size);
            break;
          default:
            printf("Invalid target array. Type c/complete for completed goals, or g/goals for current goals.\n");
        }
      }

      } else if (strcmp(command, "delete_goal") == 0 || strcmp(command, "dg") == 0)
      {

      } else if (strcmp(command, "delete_complete") == 0 || strcmp(command, "dc") == 0)
      {

      }

      else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
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
    free_goal_name(completed_goals[i]);
  }
  for (int i = 0; i < goal_index; i++)
  {
    free_goal_name(current_goals[i]);
  }

  free(completed_goals);
  free(current_goals);
}
