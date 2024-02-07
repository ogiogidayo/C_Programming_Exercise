#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

// function to generate random numbers
int generateNumber() {
    int num;
    srand((unsigned)time(NULL));
    num = rand() % 9000 + 1000;
    return num;
}

// function to determine if all the generated random numbers have different digits
int checkNumber(int num) {
    int i, j;
    int digit[4];
    for (i = 0; i < 4; i++) {
        digit[i] = num % 10;
        num /= 10;
    }
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            if (digit[i] == digit[j]) {
                return 0;
            }
        }
    }
    return 1;
}