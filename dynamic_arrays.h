#ifndef _DYNAMIC_ARRAYS_H
#define _DYNAMIC_ARRAYS_H

goal new_array[](int max_size);
goal double_array_size[](goal old_array[], int * size);
void add_element(goal array[], int * size, int index, goal element);
void remove_element(goal array[], int * size, int index);

#endif
