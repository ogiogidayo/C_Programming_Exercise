#include <stdio.h>
#include <stdbool.h>

bool prime_found(int n);
void store(unsigned char *a);
void print_bits(unsigned char *a, int size);

int main()
{
    unsigned char prime[22] = {0};
    store(prime);
    print_bits(prime, sizeof(prime));
    return 0;
}

bool prime_found(int n)
{
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}
void store(unsigned char *a)
{
    int count = 0;
    for (int i = 2; i <= 100; i++)
    {
        if (prime_found(i))
        {
            int char_index = (count * 7) / 8;
            int bit_offset = (count * 7) % 8;
            a[char_index] |= (i & 0x7F) << bit_offset;
            if (bit_offset + 7 > 8)
            {
                a[char_index + 1] |= (i & 0x7F) >> (8 - bit_offset);
            }
            count++;
        }
    }
}

void print_bits(unsigned char *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            printf("%d", (a[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}
