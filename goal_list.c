//contains the main program for the checklist

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <goal_list.h>

int main()
{
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime (&rawtime);

  printf("Current local time and date: %s", asctime(timeinfo));

  print_date(timeinfo, 0);

  print_date(timeinfo, 1);

}
