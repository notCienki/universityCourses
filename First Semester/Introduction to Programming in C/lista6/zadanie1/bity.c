#include <stdbool.h>
#include <limits.h>

const int maks_numer_bitu = (CHAR_BIT*sizeof(unsigned int)) - 1;

bool bit_jedynka(unsigned int liczba, int k)
{
    if (k < 0 || k > maks_numer_bitu)
        return false;
    return liczba & (1 << k);
}

void ustaw_bit_na_1(unsigned int* liczba, int k)
{
    if (0 <= k && k <= maks_numer_bitu)
        *liczba |= (1 << k);
}

void ustaw_bit_na_0(unsigned int* liczba, int k)
{
    if (0 <= k && k <= maks_numer_bitu)
        *liczba &= ~(1 << k);
}
