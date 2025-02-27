#ifndef KOMITET_H
#define KOMITET_H

#include "sejm.h"

bool czy_komitet_istnieje(Konfiguracja *konfig, const char *nazwa);
int znajdz_komitet(Konfiguracja *konfig, const char *nazwa);
bool wczytaj_dane_csv(Konfiguracja *konfig);
bool przekroczyl_prog(Konfiguracja *konfig, int indeks_komitetu, long long suma_glosow);

#endif
