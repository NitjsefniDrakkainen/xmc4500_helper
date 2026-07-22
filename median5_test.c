/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define SWAP(a,b) \
    if ((a) > (b)) { \
        uint8_t t = (a); \
        (a) = (b); \
        (b) = t; \
    }
    
static uint32_t testCount = 0;
static uint32_t failCount = 0;

static inline uint8_t median5_swap(const uint8_t input[5])
{
    uint8_t a = input[0];
    uint8_t b = input[1];
    uint8_t c = input[2];
    uint8_t d = input[3];
    uint8_t e = input[4];

    SWAP(a, b);
    SWAP(d, e);
    SWAP(a, c);
    SWAP(b, c);
    SWAP(a, d);
    SWAP(c, d);
    SWAP(b, e);
    SWAP(b, c);

    return c;
}

void insertion_sort_u8(uint8_t *arr, uint8_t n)
{
    for (uint8_t i = 1; i < n; i++)
    {
        uint8_t key = arr[i];
        uint8_t j = i;

        while ((j > 0U) && (arr[j - 1U] > key))
        {
            arr[j] = arr[j - 1U];
            j--;
        }

        arr[j] = key;
    }
}

static void swap_u8(uint8_t *a, uint8_t *b)
{
    uint8_t t = *a;
    *a = *b;
    *b = t;
}

static void test_permutation(uint8_t perm[5])
{
    uint8_t tmp[5];
    uint8_t median;
    uint8_t expected;

    memcpy(tmp, perm, 5);

    median = median5_swap(tmp);

    insertion_sort_u8(perm, 5);
    expected = perm[2];

testCount++;

if (median != expected)
{
    failCount++;

    printf("FAIL: ");
    for (uint8_t i = 0; i < 5; i++)
        printf("%u ", perm[i]);

    printf("\n");
}
}

static void generate(uint8_t a[], uint8_t n)
{
    if (n == 1U)
    {
        uint8_t perm[5];
        memcpy(perm, a, 5);
        test_permutation(perm);
        return;
    }

    for (uint8_t i = 0; i < n; i++)
    {
        generate(a, n - 1U);

        if ((n & 1U) == 0U)
            swap_u8(&a[i], &a[n - 1U]);
        else
            swap_u8(&a[0], &a[n - 1U]);
    }
}

typedef struct
{
    uint8_t buffer[5];
    uint8_t writeIndex;
}FreqBin_t;

uint8_t cfarWithSort(FreqBin_t * inArray, uint8_t, uint8_t guard, uint8_t locWindow, uint8_t threshold)
{
    
}

int main()
{

    
    uint8_t values[5] = {0,1,2,3,4};

    generate(values, 5);
    printf("Tests : %u\n", testCount);
    printf("Fails : %u\n", failCount);
    printf("Done.\n");
    
    testCount = 0;
    uint8_t values_2[5] = {1, 1, 2, 3, 4};
    generate(values_2, 5);
    printf("Tests : %u\n", testCount);
    printf("Fails : %u\n", failCount);
    printf("Done.\n");

    testCount = 0;
    uint8_t values_3[5] = {5, 5, 1, 5, 5};
    generate(values_3, 5);
    printf("Tests : %u\n", testCount);
    printf("Fails : %u\n", failCount);
    printf("Done.\n");
    
    testCount = 0;
    uint8_t values_4[5] = {7, 3, 7, 3, 5};
    generate(values_4, 5);
    printf("Tests : %u\n", testCount);
    printf("Fails : %u\n", failCount);
    printf("Done.\n");
    
    testCount = 0;
    uint8_t values_5[5] = {8, 8, 1, 2, 8};
    generate(values_5, 5);
    printf("Tests : %u\n", testCount);
    printf("Fails : %u\n", failCount);
    printf("Done.\n");
    
    testCount = 0;
    uint8_t values_6[5] = {4, 4, 4, 4, 4};
    generate(values_6, 5);
    printf("Tests : %u\n", testCount);
    printf("Fails : %u\n", failCount);
    printf("Done.\n");
    return 0;
}
