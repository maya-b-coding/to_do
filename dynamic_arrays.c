#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "goal_list.h"
#include "dynamic_arrays.h"

goal * new_array (int max_size)
{
  goal * array = malloc(max_size * sizeof(goal));

  if (array == NULL)
  {
    printf("Error allocating intial array\n");
    return NULL;
  }

  return array;
}

void double_array_size (goal ** old_array_ptr, int * max_size)
{
  goal * old_array = *old_array_ptr;
  goal * array = new_array((*max_size) + 20); //make sure this is set up correctly later

  if (array == NULL)
  {
    printf("Error allocating array of double size\n");
    return;
  }

  for (int i = 0; i < *max_size; i++) //copy elements into the new array
  {
    array[i] = old_array[i];
  }

  *max_size = (*max_size) * 2;
  free(old_array);
  *old_array_ptr = array;
}

void add_element(goal ** array_ptr, int *  max_size, int * size, goal element)
{
  if (*size >= *max_size)
  {
    double_array_size(array_ptr, max_size);
  }

  goal * array = *array_ptr;
  array[*size] = element;

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
