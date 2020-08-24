//contains the main program for the checklist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <goal_list.h>

#define MAX_INPUT 500

int main()
{
  //print_current_goals();

  char input[MAX_INPUT];
  char ** argv;
  int argc = 0;

  do
  {
    fgets(input, MAX_INPUT, stdin);

    argv = parse_args(input, &argc);

    if (argc > 0)
    {
      if (strcmp(argv[0], "add") == 0)
      {
        add_goal(argv, argc);
      } else if (strcmp(argv[0], "exit") == 0)
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
}
