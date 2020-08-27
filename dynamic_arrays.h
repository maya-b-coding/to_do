#ifndef _DYNAMIC_ARRAYS_H
#define _DYNAMIC_ARRAYS_H

goal * new_array (int max_size);
void double_array_size (goal ** old_array_ptr, int * size);
void add_element(goal ** array_ptr, int *  max_size, int * size, goal element);
void remove_element(goal array[], int * size, int index);

#endif
