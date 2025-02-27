//Karol Nowocień 351907 lista8 zadanie1
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "beneficjent.h"


int main(void)
{
  struct Osoba* os1 = nowa_osoba("Jan", 4);
  if (os1 == NULL) {
    printf("Blad alokacji pamieci!\n");
    return -1;
  }

  wypisz_info(os1);
  ustaw_statystyki(os1, 5, 6);
  wypisz_info(os1);

  printf("Wiek przed zmiana: %d\n", os1->wiek);
  uint8_t nowyWiek = 15;
  zmien_wiek(os1, nowyWiek);
  printf("Wiek po zmianie: %d\n", os1->wiek);
  
  dodaj_zasluge(os1);
  printf("Zaslugi po dodaniu: %d\n", os1->zaslugi);
  
  if (czy_dostanie_prezent(os1))
    printf("%s dostanie prezent!\n", os1->imie);
  else
    printf("%s nie dostanie prezentu.\n", os1->imie);

  wypisz_info(os1);

  free(os1);

  return 0;
}
