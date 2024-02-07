#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"

int previousGuesses[10000]; // これまでの推測を記録するグローバル配列
int numPreviousGuesses = 0; // これまでの推測数

int findSolution(int previousHits, int previousBlows, int lastGuess);
int setDigit(int number, int digit, int newDigit);
int getDigit(int number, int digit);
int isAllDigitsUnique(int number);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int num, input;
    int hit = 0, blow = 0;
    int score = 1;
    int before = 0;
    num = generateNumber();
    while (checkNumber(num) == 0) {
        num = generateNumber();
    }
    fprintf(fp, "Solution %d\n", num);

    printf("Hit & Blow\n");

    while (1) {
        input = findSolution(hit, blow, before);
        before = input;
        printf("solveHitBlow's input: %d\n", input);
        countHitBlow(input, num, &hit, &blow);
        fprintf(fp, "%d, %d hit, %d blow\n", input, hit, blow);
        printf("Hit: %d, Blow: %d\n", hit, blow);
        if (hit == 4) {
            break;
        }
        score++;
    }
    
    printf("Congratulations! You answered correctly. [Score %d]\n", score);
    fprintf(fp, "Score %d\n", score);

    fclose(fp);
    return 0;
}


// 与えられた桁の数字を返す関数
int getDigit(int number, int digit) {
    while (digit > 0) {
        number /= 10;
        digit--;
    }
    return number % 10;
}

// 指定した桁に新しい数字をセットする関数
int setDigit(int number, int digit, int newDigit) {
    int pow10 = 1;
    for (int i = 0; i < digit; ++i) {
        pow10 *= 10;
    }
    return (number / (pow10 * 10)) * (pow10 * 10) + newDigit * pow10 + number % pow10;
}
// 4桁の数字がすべて異なるかどうかを確認する関数
int isAllDigitsUnique(int number) {
    int used = 0;
    for (int i = 0; i < 4; ++i) {
        int digit = getDigit(number, i);
        if (used & (1 << digit)) {
            return 0; // 同じ数字が見つかった
        }
        used |= (1 << digit);
    }
    return 1; // すべて異なる
}
int findSolution(int previousHits, int previousBlows, int lastGuess) {
    int guess;
    if (lastGuess == 0) { // 初回の推測
        do {
            guess = 1000 + rand() % 9000; // 1000から9999の範囲で生成
        } while (!isAllDigitsUnique(guess));
    } else { // 2回目以降の推測
        do {
            guess = lastGuess;
            int digitsUsed[10] = {0};

            // 使用された数字を記録
            for (int i = 0; i < 4; ++i) {
                digitsUsed[getDigit(lastGuess, i)] = 1;
            }

            int changeCount = 4 - previousHits - (previousBlows / 2);

            for (int i = 0; i < changeCount; ++i) {
                int digitToChange, newDigit;
                do {
                    digitToChange = rand() % 4;
                    newDigit = rand() % 10;
                } while (digitsUsed[newDigit]);

                guess = setDigit(guess, digitToChange, newDigit);
                digitsUsed[newDigit] = 1;
            }

            if (guess < 1000) {
                guess += 1000;
            }
        } while (!isAllDigitsUnique(guess));
    }

    // これまでの推測を記録
    if (numPreviousGuesses < 100000) {
        previousGuesses[numPreviousGuesses++] = guess;
    } else {
        printf("Error: Maximum number of guesses reached.\n");
    }

    return guess;
}