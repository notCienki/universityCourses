#include<stdint.h>

struct Osoba{
  char* imie;
  uint8_t wiek;
  unsigned int zaslugi;
  unsigned int szelmostwa;
};

/******************** PROTOTYPY FUNKCJI *********************/

struct Osoba* nowa_osoba(char* imie, uint8_t wiek);
void usun_osobe(struct Osoba* osoba);
void zmien_imie(struct Osoba* osoba, char* imie);
void zmien_wiek(struct Osoba* osoba, uint8_t wiek);
void dodaj_zasluge(struct Osoba* osoba);
void dodaj_szelmostwo(struct Osoba* osoba);
void ustaw_statystyki(struct Osoba* osoba, unsigned int zaslugi, unsigned int szelmostwa);
int czy_dostanie_prezent(struct Osoba* osoba);
void wypisz_info(struct Osoba* osoba);
int komparator(const struct Osoba* os1, const struct Osoba* os2);