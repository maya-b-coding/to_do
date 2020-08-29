//contains the main program for the checklist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "goal_list.h"
#include "date_and_time.h"
#include "dynamic_arrays.h"

#define MAX_INPUT 1000
#define ARRAY_SIZE 2

int main()
{
  //print_current_goals();

  char input[MAX_INPUT];
  char ** argv;
  int argc = 0;

  goal * current_goals;
  goal * completed_goals;

  int current_goals_size;
  int completed_goals_size;

  int current_goals_max_size;
  int completed_goals_max_size;

  FILE * read_file;
  FILE * write_file;

  if ((read_file = fopen("my_goals.goal", "r")) != NULL)
  {
    read_goal_array(&current_goals, read_file, &current_goals_size, &current_goals_max_size);
    read_goal_array(&completed_goals, read_file, &completed_goals_size, &completed_goals_max_size);
  } else
  {
    current_goals_size = 0;
    completed_goals_size = 0;

    current_goals_max_size = ARRAY_SIZE;
    completed_goals_max_size = ARRAY_SIZE;

    current_goals = new_array(current_goals_max_size);
    completed_goals = new_array(completed_goals_max_size);
  }

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
              complete_goal(completed_goals, completed_goals_size - 1);
              break;
            default:
              printf("Invalid target array. Type c/complete for completed goals, or g/goals for current goals.\n");
              break;
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
            break;
        }
      }

      } else if (strcmp(command, "delete") == 0 || strcmp(command, "d") == 0)
      {
        {if (argc < 2)
        {
          printf("Please specify a target array in your second argument. Type c/complete for completed goals, or g/goals for current goals.\n");
        } else if (argc < 3){
          printf("Invalid input. Syntax for delete command should read \"delete <target_array> <index>\n");
        } else {
            int index = atoi(argv[2]);
            switch (get_target_array(argv[1]))
            {
              case 0:
                if (index < 0 || index >= current_goals_size)
                {
                  printf("Error: %d is not a valid index in the current goals array.\n", index);
                } else {
                  printf("Goal [%d] - \"%s\" deleted from current goals array\n", index, current_goals[index].name);
                  remove_element(current_goals, &current_goals_size, index);
                }
                break;
              case 1:
                if (index < 0 || index >= completed_goals_size)
                {
                  printf("Error: %d is not a valid index in the completed goals array.\n", index);
                } else {
                  printf("Goal [%d] - \"%s\" deleted from completed goals array\n", index, completed_goals[index].name);
                  remove_element(completed_goals, &completed_goals_size, index);
                }
                break;
              default:
                printf("Invalid target array. Type c/complete for completed goals, or g/goals for current goals.\n");
                break;
            }
          }

        }
      }  else if (strcmp(command, "complete") == 0 || strcmp(command, "c") == 0)
      {
        if (argc < 2)
        {
          printf("Invalid input. Syntax for complete command should read \"complete <index>\"\n");
        } else
        {
          int index = atoi(argv[1]);
          if (index < 0 || index >= current_goals_size)
          {
            printf("Error: %d is not a valid index in the current goals array.\n", index);
          } else {
            complete_goal(current_goals, index);
            goal removed = current_goals[index];
            remove_element(current_goals, &current_goals_size, index);
            add_element(&completed_goals, &completed_goals_max_size, &completed_goals_size, removed);

          }
        }
      } else if (strcmp(command, "renew") == 0 || strcmp(command, "r") == 0){
        if (argc < 2)
        {
          printf("Invalid input. Syntax for renew command should read \"renew <index>\"\n");
        } else {
          int index = atoi(argv[1]);
          if (index < 0 || index >= completed_goals_size)
          {
            printf("Erorr: %d is not a valid index in the completed goals array.\n", index);
          } else {
            renew_goal(completed_goals, index);
            goal removed = completed_goals[index];
            remove_element(completed_goals, &completed_goals_size, index);
            add_element(&current_goals, &current_goals_max_size, &current_goals_size, removed);
          }
        }
      } else if (strcmp(command, "change_target_date") == 0 || strcmp(command, "ctd") == 0)
      {
        if (argc < 4)
        {
          printf("Invalid input. Syntax for change_target_date command should read \"change_target_date <target_array> <index> <date>\"\n");
        } else
        {
          int index = atoi(argv[2]);
          switch (get_target_array(argv[1]))
          {
            case 0:
              if (index < 0 || index >= current_goals_size)
              {
                printf("Error: %d is not a valid index in the current goals array.\n", index);
              } else
              {
                if (argc < 5)
                {
                  set_date_target(current_goals, index, argv[3]);
                } else
                {
                  set_date_target_w_time(current_goals, index, argv[3], argv[4]);
                }

              }
              break;
            case 1:
              if (index < 0 || index >= completed_goals_size)
              {
                printf("Error: %d is not a valid index in the completed goals array.\n", index);
              } else
              {
                if (argc < 5)
                {
                  set_date_target(completed_goals, index, argv[3]);
                } else
                {
                  set_date_target_w_time(completed_goals, index, argv[3], argv[4]);
                }

              }
              break;
            default:
              printf("Invalid target array. Type c/complete for completed goals, or g/goals for current goals.\n");
              break;
          }
        }

      } else if (strcmp(command, "change_name") == 0 || strcmp(command, "cn") == 0)
      {
        if (argc < 4)
        {
          printf("Invalid input. Syntax for change_name command should read \"change_name <target_array> <index> <new_name>\"\n");
        } else {
          int index = atoi(argv[2]);
          switch (get_target_array(argv[1]))

          {
            case 0:
              if (index < 0 || index >= current_goals_size)
              {
                printf("Error: %d is not a valid index in the current goals array.\n", index);
              } else
              {
                set_name(current_goals, index, argv[3]);
              }
              break;
            case 1:
              if (index < 0 || index >= completed_goals_size)
              {
                printf("Error: %d is not a valid index in the completed goals array.\n", index);
              } else
              {
                set_name(completed_goals, index, argv[3]);
              }
              break;
            default:
              printf("Invalid target array. Type c/complete for completed goals, or g/goals for current goals.\n");
              break;
          }
        }
      } else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
      {
        break;
      } else {
        printf("Invalid command. type help for a list of commands.\n");
      }

    }

    free_parsed_args(argv);

  } while (1);

  //write to file
  write_file = fopen("my_goals.goal", "w");

  if (write_file == NULL)
  {
    printf("error opening write file\n");
  } else {
    write_goal_array(current_goals, write_file, current_goals_size);
    write_goal_array(completed_goals, write_file, completed_goals_size);
  }

  //free all used memory

  for (int i = 0; i < current_goals_size; i++)
  {
    free_goal_name(current_goals[i]);
  }
  for (int i = 0; i < completed_goals_size; i++)
  {
    free_goal_name(completed_goals[i]);
  }

  free(current_goals);
  free(completed_goals);

  if (read_file != NULL)
  {
    fclose(read_file);
  }

  if (write_file != NULL)
  {
    fclose(write_file);
  }
}
