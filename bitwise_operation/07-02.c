#include <stdio.h>
#include <stdbool.h>

bool prime_found(int n);
void store(unsigned char *a);
void print_bits(unsigned char *a, int size);

int main()
{
    unsigned char prime_array[25 * 7 / 8 + 1] = {0};
    store(prime_array);
    print_bits(prime_array, sizeof(prime_array));
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
    int prime_count = 0;
    for (int i = 2; i <= 100; i++)
    {
        if (prime_found(i))
        {
            int char_index = (prime_count * 7) / 8;
            int bit_offset = (prime_count * 7) % 8;
            a[char_index] |= (i & 0x7F) << bit_offset;
            if (bit_offset + 7 > 8)
            {
                a[char_index + 1] |= (i & 0x7F) >> (8 - bit_offset);
            }
            prime_count++;
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
