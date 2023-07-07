#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int random(int min, int max);

int main(void) {
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        printf("Min : 1 Max : 40 %d\n", random(1, 40));
    }
    return 0;
}

int random(int min, int max) {
    int result = 0, low = 0, high = 0;
    if (min < max) {
        low = min;
        high = max + 1; // include max in output
    }
    else {
        low = max + 1; // include max in output
        high = min;
    }
    result = (rand() % (high - low)) + low;
    return result;
}