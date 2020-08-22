//contains the main program for the checklist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <goal_list.h>

#define MAX_INPUT 100

int main()
{
  //print_current_goals();

  char input[MAX_INPUT];
  char ** args;
  int argc;

  do
  {
    fgets(input, MAX_INPUT, stdin);
    printf("%s", input);

    args = parse_args(input, &argc);

    printf("x = %d\n", x);

  } while (strncmp(input, "exit", 4) != 0);
}
