#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stała definiująca maksymalny rozmiar kolejki
#define ROZMIAR 10100

// Struktura danych reprezentująca klienta z imieniem i wiekiem
typedef struct {
    char *nazwa;  // Wskaźnik na ciąg znaków przechowujący imię
    int lata;     // Liczba reprezentująca wiek
} klient;

// Tablice do przechowywania danych klientów
klient kolejka[ROZMIAR];   // Kolejka oczekujących
klient klubowicze[ROZMIAR]; // Lista osób w klubie

// Indeksy do zarządzania kolejką
int poczatek = 0, koniec = 0;
int liczba_klubowiczow = 0;
int wolne_miejsca = 0;

// Funkcja kopiująca tekst do nowego miejsca w pamięci
char *kopiuj_tekst(const char *tekst) {
    size_t dlugosc = strlen(tekst) + 1; // Oblicz długość tekstu z miejscem na znak null
    char *kopia = malloc(dlugosc); // Alokacja pamięci
    if (kopia != NULL) {           // Sprawdzenie, czy pamięć została przydzielona
        memcpy(kopia, tekst, dlugosc); // Skopiowanie tekstu do nowego miejsca
    }
    return kopia; // Zwrócenie wskaźnika na kopię tekstu
}

// Dodawanie klienta do końca kolejki
void dodaj_klienta(klient k) {
    k.nazwa = kopiuj_tekst(k.nazwa); // Skopiowanie imienia
    kolejka[koniec++] = k;          // Dodanie do kolejki i zwiększenie indeksu końca
}

// Usuwanie klienta z początku kolejki
klient usun_klienta() {
    return kolejka[poczatek++]; // Zwraca klienta i przesuwa początek kolejki
}

// Sprawdzenie, czy kolejka jest pusta
int czy_kolejka_pusta() {
    return poczatek == koniec; // Porównuje początek i koniec - jeśli są równe, kolejka jest pusta
}

// Usuwanie klienta na podstawie jego pozycji w kolejce
void usun_pozycji(int indeks) {
    free(kolejka[indeks].nazwa); // Zwolnienie pamięci przypisanej do imienia
    for (int i = indeks; i < koniec - 1; i++) {
        kolejka[i] = kolejka[i + 1]; // Przesunięcie elementów w lewo
    }
    koniec--; // Zmniejszenie indeksu końca
}

// Przetwarzanie komend podanych przez użytkownika
void obsluz_polecenie(char *wiadomosc) {
    char rodzaj; // Zmienna przechowująca typ operacji
    sscanf(wiadomosc, "%c", &rodzaj); // Odczytanie pierwszego znaku (rodzaj operacji)

    // Obsługa różnych typów operacji
    if (rodzaj == 'D') { // Dodanie nowego klienta
        klient k;
        char temp_nazwa[1001]; // Tymczasowy bufor na imię
        sscanf(wiadomosc, "D %s %d", temp_nazwa, &k.lata); // Wczytanie danych
        k.nazwa = temp_nazwa;
        dodaj_klienta(k);
    } else if (rodzaj == 'U') { // Usunięcie klienta po imieniu
        char nazwa[1001];
        sscanf(wiadomosc, "U %s", nazwa); // Odczytanie imienia
        for (int i = poczatek; i < koniec; i++) { // Przeszukanie kolejki
            if (strcmp(kolejka[i].nazwa, nazwa) == 0) { // Znalezienie osoby
                usun_pozycji(i); // Usunięcie osoby
                break;
            }
        }
    } else if (rodzaj == 'M') { // Zarządzanie miejscami w klubie
        int miejsca;
        sscanf(wiadomosc, "M %d", &miejsca); // Liczba dostępnych miejsc
        wolne_miejsca += miejsca; // Dodanie miejsc
        while (wolne_miejsca && !czy_kolejka_pusta()) { // Wpuszczanie do klubu
            klient k = usun_klienta();
            if (k.lata >= 18) { // Wiek powyżej 18 lat
                klubowicze[liczba_klubowiczow++] = k; // Dodanie do listy klubowiczów
                wolne_miejsca--;
            } else {
                free(k.nazwa); // Zwolnienie pamięci dla osób poniżej 18 lat
            }
        }
    } else if (rodzaj == 'Z') { // Dodanie osoby przed znajomym
        char nazwa[1001], znajomy[1001];
        int lata;
        sscanf(wiadomosc, "Z %s %d %s", nazwa, &lata, znajomy); // Odczytanie danych
        int pozycja = -1; // Pozycja znajomego w kolejce
        for (int i = poczatek; i < koniec; i++) {
            if (strcmp(kolejka[i].nazwa, znajomy) == 0) { // Znalezienie znajomego
                pozycja = i;
                break;
            }
        }
        if (pozycja != -1) { // Jeśli znaleziono znajomego
            for (int i = koniec; i > pozycja; i--) {
                kolejka[i] = kolejka[i - 1]; // Przesunięcie elementów w prawo
            }
            klient k;
            k.nazwa = kopiuj_tekst(nazwa); // Tworzenie nowej osoby
            k.lata = lata;
            kolejka[pozycja] = k; // Dodanie osoby w odpowiednim miejscu
            koniec++;
        }
    }
}

// Funkcja główna programu
int main() {
    char wejscie[1024]; // Bufor na wejście użytkownika

    // Odczytywanie komend do momentu zakończenia
    while (fgets(wejscie, sizeof(wejscie), stdin)) {
        if (wejscie[0] == 'K') { // Komenda kończąca
            break;
        }
        obsluz_polecenie(wejscie); // Przetwarzanie komendy
    }

    // Wpuszczanie osób do klubu po zakończeniu wprowadzania komend
    while (!czy_kolejka_pusta() && wolne_miejsca) {
        klient k = usun_klienta();
        if (k.lata >= 18) {
            klubowicze[liczba_klubowiczow++] = k;
            wolne_miejsca--;
        } else {
            free(k.nazwa);
        }
    }

    // Wypisywanie listy klubowiczów
    for (int i = 0; i < liczba_klubowiczow; i++) {
        printf("%s\n", klubowicze[i].nazwa);
        free(klubowicze[i].nazwa); // Zwolnienie pamięci po wypisaniu
    }

    // Zwolnienie pamięci dla pozostałych w kolejce
    for (int i = poczatek; i < koniec; i++) {
        free(kolejka[i].nazwa);
    }

    return 0; // Zakończenie programu
}
