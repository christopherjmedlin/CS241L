#include <stdio.h>
#include <stdbool.h>

int main(void) {
   int inputYear;
   
   scanf("%d", &inputYear);
   
   // input year divisible by 4 AND 
   // (input year not divisible by 100 OR input year divisble by 400)
   if (!(inputYear % 4) && (inputYear % 100 || !(inputYear % 400))) {
      printf("%d - leap year\n", inputYear);  
   } else {
      printf("%d - not a leap year\n", inputYear);
   }

   return 0;
}