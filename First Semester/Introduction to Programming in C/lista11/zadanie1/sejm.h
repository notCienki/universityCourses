#ifndef SEJM_H
#define SEJM_H

#include <stdbool.h>

#define MAX_COMMITTEES 20
#define MAX_LINE_LENGTH 1024
#define MAX_NAME_LENGTH 64
#define MAX_ALLIANCES 10

typedef struct {
    char nazwa[MAX_NAME_LENGTH];
    long long glosy;
    int mandaty;
    bool mniejszosc_etniczna;
    bool w_sojuszu;
    double prog_wyborczy;
} Komitet;

typedef struct {
    char* nazwy_komitetow[MAX_COMMITTEES];
    int liczba_komitetow;
    long long suma_glosow;
    int mandaty;
} Sojusz;

typedef struct {
    bool metoda_sainte_lague;
    Komitet komitety[MAX_COMMITTEES];
    int liczba_komitetow;
    Sojusz sojusze[MAX_ALLIANCES];
    int liczba_sojuszy;
} Konfiguracja;

#endif
