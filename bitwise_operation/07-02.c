#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Is_Prime(int n);
void store(unsigned char *prime);

int main() {
    unsigned char prime[22];
    memset(prime, 0, sizeof(prime));
    store(prime);

    for (int i = 0; i < 22; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (prime[i] >> j) & 1);
        }
        printf(" ");
    }

    printf("\n");

    return 0;
}

int Is_Prime(int n) {
    if (n <= 1) 
        return 0;
    if (n <= 3) 
        return 1;
    if (n % 2 == 0 || n % 3 == 0) 
        return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) 
            return 0;
    }
    return 1;
}

void store(unsigned char *prime) {
    int bit_index = 0;
    for (int i = 2; i <= 100; i++) {
        if (Is_Prime(i)) {
            for (int j = 7 - 1; j >= 0; j--) {
                if (bit_index / 8 >= 22) {
                    break;
                }
                int bit = (i >> j) & 1;
                prime[bit_index / 8] |= bit << (7 - bit_index % 8);
                bit_index++;
            }
        }
    }
}