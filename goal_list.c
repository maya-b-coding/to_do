//contains the main program for the checklist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <goal_list.h>

#define MAX_INPUT 500
#define ARRAY_SIZE 100

int main()
{
  //print_current_goals();

  char input[MAX_INPUT];
  char ** argv;
  int argc = 0;

  goal expired_goals[ARRAY_SIZE];
  goal completed_goals[ARRAY_SIZE];
  goal current_goals[ARRAY_SIZE];

  int goal_index = 0;
  do
  {
    fgets(input, MAX_INPUT, stdin);

    argv = parse_args(input, &argc);

    if (argc > 0)
    {
      if (strcmp(argv[0], "add") == 0)
      {
        add_goal(argv, argc, current_goals, &goal_index);
      } else if (strcmp(argv[0], "wday") == 0)
      {
        int wday = get_wday(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        printf("weekday = %d\n", wday);
      } else if (strcmp(argv[0], "print_goals") == 0)
      {
        printf("Current goals:\n");

        for (int i = 0; i < goal_index; i++)
        {
          print_goal(current_goals[i]);
        }
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
