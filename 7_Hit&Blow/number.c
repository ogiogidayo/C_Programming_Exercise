#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "main.h"

// function to generate random numbers
int generateNumber() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int num;
    srand((unsigned)(tv.tv_sec + tv.tv_usec));
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
    if (num <1000 || num > 9999)
        return 1;
    return 1;
}