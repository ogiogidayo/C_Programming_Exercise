#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"


// ヒット数とブロー数を数える関数
int countHitBlow(int num, int ans, int *hit, int *blow) {
    int i, j;
    int digit[4];
    int digitAns[4];
    for (i = 0; i < 4; i++) {
        digit[i] = num % 10;
        num /= 10;
        digitAns[i] = ans % 10;
        ans /= 10;
    }
    *hit = 0;
    *blow = 0;
    for (i = 0; i < 4; i++) {
        if (digit[i] == digitAns[i]) {
            (*hit)++;
        } else {
            for (j = 0; j < 4; j++) {
                if (digit[i] == digitAns[j]) {
                    (*blow)++;
                }
            }
        }
    }
    return 0;
    
}
