#include<stdio.h>

int isPrimeNumber(unsigned int n) {
    if (n < 2) {
        return 0;
    }

    for (unsigned int i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    unsigned int primes[30] = {0};
    for (unsigned int n = 2; n <= 100; n++) {
        int primeIndex = 0;
        if (isPrimeNumber(n)) {
            int arrayIndex = (primeIndex * 7) / 32;
            int bitPosition = (primeIndex * 7) % 32;

            primes[arrayIndex] |= n << bitPosition;

            primeIndex++;
        }
    }  
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 7 && (i * 7 + j) < 25; j++) {
            int bitPosition = j * 7;
            unsigned int value = (primes[i] >> bitPosition) & ((1 << 7) - 1);
            printf("%u ", value);
        }
    }
    printf("\n");
}
