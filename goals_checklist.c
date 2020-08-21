//contains the main program for the checklist

#include <stdio.h>
#include <string.h>

void check_errors(int error_status);
int print_current_goals();
int print_past_goals();
int print_all_goals();

int main()
{
  check_errors(print_past_goals());


  
}

void check_errors(int error_status)
{
  switch (error_status) {
    case 0:
      return; //shouldn't need to break because we are returning
    default:
      print("Error encountered");
      return;
  }
}
