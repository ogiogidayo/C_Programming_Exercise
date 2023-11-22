#include<stdio.h>

int main(void){
    int input;
    printf("Digit: ");
    scanf("%d", &input);
    unsigned char x = (unsigned char)input;

    printf("Binary: ");
    for (int i= 7; i >= 0; i--)
        putchar((x & (1 << i)) ? '1' : '0');
    putchar('\n');

    return 0;
}