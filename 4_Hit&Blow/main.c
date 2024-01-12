#include <stdio.h>
#include "main.h"

int main(void) {
    int num, input, hit, blow;
    int score = 1;
    num = generateNumber();
    while (checkNumber(num) == 0) {
        num = generateNumber();
    }
    printf("Hit & Blow\n");
    
    
    // a loop that displays hit and blow by inputting until a correct answer is given, and terminates when the answer is correct
    // if the number entered is not 4 digits, an error is displayed.
    while (1) {
        printf("%d: Guess the number: ", score);
        scanf("%d", &input);
        if (input < 1000 || input > 9999) {
            printf("Error: Input 4-digit number.\n");
            continue;
        }
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