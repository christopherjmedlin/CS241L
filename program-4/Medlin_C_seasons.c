#include <stdio.h>
#include <string.h>

int main(void) {
   char inputMonth[50];
   int inputDay;
   int monthNum;
   
   scanf("%s", inputMonth); 
   scanf("%d", &inputDay); 
   
   if (!strcmp(inputMonth, "January")) {
      monthNum = 1;
   } else if (!strcmp(inputMonth, "February")) {
      monthNum = 2;
   } else if (!strcmp(inputMonth, "March")) {
      monthNum = 3;
   } else if (!strcmp(inputMonth, "April")) {
      monthNum = 4;
   } else if (!strcmp(inputMonth, "May")) {
      monthNum = 5;
   } else if (!strcmp(inputMonth, "June")) {
      monthNum = 6;
   } else if (!strcmp(inputMonth, "July")) {
      monthNum = 7;
   } else if (!strcmp(inputMonth, "August")) {
      monthNum = 8;
   } else if (!strcmp(inputMonth, "September")) {
      monthNum = 9;
   } else if (!strcmp(inputMonth, "October")) {
      monthNum = 10;
   } else if (!strcmp(inputMonth, "November")) {
      monthNum = 11;
   } else if (!strcmp(inputMonth, "December")) {
      monthNum = 12;
   } else {
      printf("Invalid\n");
      return 1;
   }
   
   if (inputDay < 0 || inputDay > 31) {
      printf("Invalid\n");
      return 1;
   }
   
   if ((monthNum > 3 && monthNum < 6) ||
       (inputDay >= 20 && monthNum == 3) ||
       (inputDay <= 20 && monthNum == 6)) {
      printf("Spring\n");
   } else if ((monthNum >= 6 && monthNum < 9) ||
              (monthNum == 9 && inputDay <= 21)) {
      printf("Summer\n");
   } else if ((monthNum >= 9 && monthNum < 12) ||
              (monthNum == 12 && inputDay <= 20)) {
      printf("Autumn\n");
   } else {
      printf("Winter\n");
   }
   return 0;
}