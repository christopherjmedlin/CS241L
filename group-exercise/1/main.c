#include <stdio.h>

void reverse(char* str, int length) {
    char* end = str + length-1;
    char* start = str;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main(int argc, char* argv[]) {
    char str[4];
    int length;
    scanf("%d", &length);
    scanf("%s", &str);
    reverse(str, length);
    printf("%s", str);
}
