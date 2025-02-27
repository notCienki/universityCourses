#include "mandaty.h"
#include "komitet.h"
#include <stdlib.h>

typedef struct {
    double iloraz;
    int indeks_komitetu;
    long long suma_glosow;
} Iloraz;

static int porownaj_ilorazy(const void* a, const void* b) {
    // ...existing code...
}

void rozdziel_mandaty(Konfiguracja *konfig, int mandaty_okregu, long long *glosy_okregu) {
    // ...existing code...
}
