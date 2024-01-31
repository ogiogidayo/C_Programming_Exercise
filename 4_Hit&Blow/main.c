#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int findSolution(int previousHits, int previousBlows, int lastGuess);
int setDigit(int number, int digit, int newDigit);
int getDigit(int number, int digit);

int main(void) {
    int num, input;
    int hit = 0, blow = 0;
    int score = 1;
    int before = 0;
    num = generateNumber();
    while (checkNumber(num) == 0) {
        num = generateNumber();
    }
    printf("Hit & Blow\n");

    while (1) {
        input = findSolution(hit, blow, before);
        before = input;
        printf("solveHitBlow's input: %d\n", input);
        countHitBlow(input, num, &hit, &blow);
        printf("Hit: %d, Blow: %d\n", hit, blow);
        if (hit == 4) {
            break;
        }
        score++;
    }
    
    printf("Congratulations! You answered correctly. [Score %d]\n", score);

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

// HitまたはBlowだった数字を保持し、それ以外の数字を変更する関数
int findSolution(int previousHits, int previousBlows, int lastGuess) {
    // 前回の推測が0（初回）の場合、ランダムな数を生成
    if (lastGuess == 0) {
        return 1000 + rand() % 9000; // 1000から9999の範囲で生成
    }

    int guess = lastGuess;
    int digitsUsed[10] = {0}; // 既に使用された数字を記録する配列

    // 使用された数字を記録
    for (int i = 0; i < 4; ++i) {
        digitsUsed[getDigit(lastGuess, i)] = 1;
    }

    int changeCount = 4 - previousHits - (previousBlows / 2); // 変更する桁の数を決定

    // 指定された数の桁を変更
    for (int i = 0; i < changeCount; ++i) {
        int digitToChange = rand() % 4;
        int newDigit;
        do {
            newDigit = rand() % 10;
        } while (digitsUsed[newDigit]); // 新しい数字が既に使用されていないか確認

        guess = setDigit(guess, digitToChange, newDigit);
        digitsUsed[newDigit] = 1; // 新しい数字を使用済みとして記録
    }

    // 結果が4桁であることを保証
    if (guess < 1000) {
        guess += 1000;
    }

    return guess;
}