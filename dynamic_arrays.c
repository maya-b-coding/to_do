#include <stdlib.h>
#include <stdio.h>
#include <goal_list.h>
#include <dynamic_arrays.h>

goal new_array[] (int max_size)
{
  goal array [] = malloc(max_size * sizeof(goal));

  if (array == NULL)
  {
    printf("Error allocating intial array\n");
    return NULL;
  }

  return array;
}

goal double_array_size(goal old_array[], int * max_size)
{
  goal new_array[] = malloc((*max_size * 2) * sizeof(goal)); //make sure this is set up correctly later

  if (new_array == NULL)
  {
    printf("Error allocating array of double size\n");
    return NULL;
  }

  for (int i = 0; i < max_size; i++) //copy elements into the new array
  {
    new_array[i] = old_array[i];
  }

  *max_size = *max_size * 2;
  free(old_array);
  return new_array;
}

void add_element(goal array[], int *  max_size, int * size, goal element)
{

  if (*size >= *max_size)
  {
    array = double_array_size(array,max_size);
  }

  array[size] = element;

  *size = *size + 1;
}

void remove_element(goal array[], int * size, int index)
{
  *size = *size - 1;

  while (index < *size)
  {
    array[index] = array[index + 1];
    index++;
  }
}
