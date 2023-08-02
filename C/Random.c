#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

int main(void) {
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        printf("Min : 1 Max : 40 %d\n", random(1, 40));
    }
    return 0;
}
