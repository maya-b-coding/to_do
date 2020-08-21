//contains the main program for the checklist

#include <stdio.h>
#include <string.h>
#include <time.h>

void check_errors(int error_status);
void print_date(struct tm * date, int display_time);
int print_current_goals();
int print_past_goals();
int print_all_goals(); // is this function really necessary?

const int MAX_CHARS = 99;
const char * DATE_NO_TIME = "%x";
const char * DATE_W_TIME = "%x - %I:%M%p";

struct goal{

};

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

void check_errors(int error_status)
{
  switch (error_status) {
    case 0:
      return;
    default:
      printf("Error encountered");
      return;
  }
}

int print_current_goals(){
  return 0;
}

void print_date(struct tm * date, int display_time){
  char * format_type = display_time == 0 ? DATE_NO_TIME : DATE_W_TIME;
  char date_string [MAX_CHARS];

  strftime(date_string, MAX_CHARS, format_type, date); //can i drop the size_t?

  printf("%s\n", date_string);
}
