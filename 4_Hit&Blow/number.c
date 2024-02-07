#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

// 乱数を生成する関数
int generateNumber() {
    int num;
    srand((unsigned)time(NULL));
    num = rand() % 10000;
    return num;
}

// 数字の格桁が異なるかどうかを判定する関数
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