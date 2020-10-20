#include <stdlib.h>
#include <stdio.h>

int main() {
    int lengths[10] = {};
    int* nums[10];

    for (int i = 0; i < 10; i++) {
        nums[i] = (int*) malloc(100);
    }

    for (int i = 0; i < 100; i++) {
        int new_num = rand() % 999 + 1;
        int idx = new_num % 10;
        printf("%d\n %d\n", new_num, lengths[idx]);
        nums[idx][lengths[idx]] = new_num;
        lengths[idx]++;
    }

    return 0;
}
