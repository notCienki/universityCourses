//Karol Nowocień 351907 lista8 zadanie1
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "beneficjent.h"

struct Osoba* nowa_osoba(char* imie, uint8_t wiek)
{
  struct Osoba* os = malloc(sizeof(struct Osoba));
  if (os == NULL)
    return NULL;

  // Zaalokowanie pamięci dla imienia i skopiowanie
  os->imie = malloc(strlen(imie) + 1);  // +1 na znak null kończący
  if (os->imie == NULL) {
    free(os);  // Zwolnij wcześniej zaalokowaną pamięć, jeśli nie udało się zaalokować pamięci dla imienia
    return NULL;
  }
  
  strcpy(os->imie, imie);  // Skopiuj imię do zaalokowanej pamięci

  os->wiek = wiek;
  os->zaslugi = 0;
  os->szelmostwa = 0;

  return os;
}


void usun_osobe(struct Osoba* osoba)
{
  if (osoba != NULL) {
    free(osoba->imie);  // Zwalniamy pamięć na imię
    free(osoba);        // Zwalniamy pamięć na strukturę
  }
}


void zmien_imie(struct Osoba* osoba, char* imie)
{
  if (osoba == NULL || imie == NULL)
    return;

  // Zwolnienie starej pamięci
  free(osoba->imie);

  // Zaalokowanie nowej pamięci i skopiowanie imienia
  osoba->imie = malloc(strlen(imie) + 1);  // +1 na znak '\0'
  if (osoba->imie != NULL) {
    strcpy(osoba->imie, imie);  // Skopiowanie imienia
  }
}


void zmien_wiek(struct Osoba* osoba, uint8_t wiek)
{
  osoba->wiek=wiek;
}


void dodaj_zasluge(struct Osoba* osoba)
{
  osoba->zaslugi+=1;
}


void dodaj_szelmostwo(struct Osoba* osoba)
{
  osoba->szelmostwa+=1;
}


void ustaw_statystyki(struct Osoba* osoba, unsigned int zaslugi, unsigned int szelmostwa)
{
  osoba->zaslugi=zaslugi;
  osoba->szelmostwa=szelmostwa;
}

int czy_dostanie_prezent(struct Osoba* osoba)
{
  if (osoba->zaslugi > osoba->szelmostwa)
    return 1;  // Dostanie prezent
  else
    return 0;  // Nie dostanie prezentu
}

void wypisz_info(struct Osoba* osoba)
{
  printf("Imie: %s\n", osoba->imie);
  printf("Wiek: %d\n", osoba->wiek);
  printf("Zaslugi: %d\n", osoba->zaslugi);
  printf("Szelmostwa: %d\n", osoba->szelmostwa);
}

int komparator(const struct Osoba* os1, const struct Osoba* os2)
{
  // Komparator do porównywania na podstawie zasług
  return os2->zaslugi - os1->zaslugi;  // Większe zasługi - wyższy priorytet
}