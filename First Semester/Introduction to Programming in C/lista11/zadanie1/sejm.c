#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    double iloraz;
    int indeks_komitetu;
    long long suma_glosow;
} Iloraz;

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

// Funkcja porównująca do qsort
int porownaj_ilorazy(const void* a, const void* b) {
    const Iloraz* i1 = (const Iloraz*)a;
    const Iloraz* i2 = (const Iloraz*)b;
    
    if (i1->iloraz > i2->iloraz) return -1;
    if (i1->iloraz < i2->iloraz) return 1;
    // W przypadku remisu, większa liczba głosów wygrywa
    if (i1->suma_glosow > i2->suma_glosow) return -1;
    if (i1->suma_glosow < i2->suma_glosow) return 1;
    return 0;
}

// Sprawdza czy komitet jest już w konfiguracji
bool czy_komitet_istnieje(Konfiguracja *konfig, const char *nazwa) {
    for (int i = 0; i < konfig->liczba_komitetow; i++) {
        if (strcmp(konfig->komitety[i].nazwa, nazwa) == 0) {
            return true;
        }
    }
    return false;
}

// Znajduje indeks komitetu po nazwie
int znajdz_komitet(Konfiguracja *konfig, const char *nazwa) {
    for (int i = 0; i < konfig->liczba_komitetow; i++) {
        if (strcmp(konfig->komitety[i].nazwa, nazwa) == 0) {
            return i;
        }
    }
    return -1;
}

// Obsługa opcji --minority
bool obsluz_opcje_mniejszosci(Konfiguracja *konfig, const char *nazwa_komitetu) {
    int idx = znajdz_komitet(konfig, nazwa_komitetu);
    if (idx == -1) {
        printf("Error: committee %s not found\n", nazwa_komitetu);
        return false;
    }
    konfig->komitety[idx].mniejszosc_etniczna = true;
    return true;
}

// Obsługa opcji --alliance
bool obsluz_opcje_sojuszu(Konfiguracja *konfig, const char *lista_komitetow) {
    char *list_copy = strdup(lista_komitetow);
    char *nazwa_komitetu = strtok(list_copy, ";");
    Sojusz *sojusz = &konfig->sojusze[konfig->liczba_sojuszy];
    sojusz->liczba_komitetow = 0;
    sojusz->suma_glosow = 0;
    sojusz->mandaty = 0;

    while (nazwa_komitetu != NULL) {
        int idx = znajdz_komitet(konfig, nazwa_komitetu);
        if (idx == -1) {
            printf("Error: committee %s not found\n", nazwa_komitetu);
            free(list_copy);
            return false;
        }
        if (konfig->komitety[idx].w_sojuszu) {
            printf("Error: committee %s already in alliance\n", nazwa_komitetu);
            free(list_copy);
            return false;
        }
        konfig->komitety[idx].w_sojuszu = true;
        konfig->komitety[idx].prog_wyborczy = 8.0;
        sojusz->nazwy_komitetow[sojusz->liczba_komitetow++] = strdup(nazwa_komitetu);
        nazwa_komitetu = strtok(NULL, ";");
    }
    
    konfig->liczba_sojuszy++;
    free(list_copy);
    return true;
}

// Parsowanie argumentów wiersza poleceń
bool parsuj_argumenty(int argc, char *argv[], Konfiguracja *konfig) {
    konfig->metoda_sainte_lague = false;
    konfig->liczba_sojuszy = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--sainte-lague") == 0) {
            if (konfig->metoda_sainte_lague) {
                printf("Error: duplicate --sainte-lague option\n");
                return false;
            }
            konfig->metoda_sainte_lague = true;
        }
        else if (strcmp(argv[i], "--minority") == 0) {
            if (i + 1 >= argc) {
                printf("Error: missing committee name after --minority\n");
                return false;
            }
            if (!obsluz_opcje_mniejszosci(konfig, argv[++i])) {
                return false;
            }
        }
        else if (strcmp(argv[i], "--alliance") == 0) {
            if (i + 1 >= argc) {
                printf("Error: missing committee list after --alliance\n");
                return false;
            }
            if (!obsluz_opcje_sojuszu(konfig, argv[++i])) {
                return false;
            }
        }
    }
    return true;
}

// Funkcja wczytująca dane z CSV
bool wczytaj_dane_csv(Konfiguracja *konfig) {
    char line[MAX_LINE_LENGTH];
    char *token;
    
    // Wczytaj nagłówek
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
        printf("Error: empty input\n");
        return false;
    }
    
    // Pomiń "okreg" i "mandatow"
    token = strtok(line, ";");
    if (token == NULL) return false;
    token = strtok(NULL, ";");
    if (token == NULL) return false;
    
    // Wczytaj nazwy komitetów
    konfig->liczba_komitetow = 0;
    while ((token = strtok(NULL, ";\n")) != NULL) {
        if (konfig->liczba_komitetow >= MAX_COMMITTEES) {
            printf("Error: too many committees\n");
            return false;
        }
        strncpy(konfig->komitety[konfig->liczba_komitetow].nazwa, token, MAX_NAME_LENGTH-1);
        konfig->komitety[konfig->liczba_komitetow].glosy = 0;
        konfig->komitety[konfig->liczba_komitetow].mandaty = 0;
        konfig->komitety[konfig->liczba_komitetow].mniejszosc_etniczna = false;
        konfig->komitety[konfig->liczba_komitetow].w_sojuszu = false;
        konfig->komitety[konfig->liczba_komitetow].prog_wyborczy = 5.0;
        konfig->liczba_komitetow++;
    }

    return true;
}

// Sprawdza czy komitet przekroczył próg wyborczy
bool przekroczyl_prog(Konfiguracja *konfig, int indeks_komitetu, long long suma_glosow) {
    if (konfig->komitety[indeks_komitetu].mniejszosc_etniczna) {
        return true;
    }
    
    double procent_glosow = (double)konfig->komitety[indeks_komitetu].glosy * 100.0 / suma_glosow;
    return procent_glosow >= konfig->komitety[indeks_komitetu].prog_wyborczy;
}

void rozdziel_mandaty(Konfiguracja *konfig, int mandaty_okregu, long long *glosy_okregu) {
    long long suma_glosow = 0;
    for (int i = 0; i < konfig->liczba_komitetow; i++) {
        suma_glosow += glosy_okregu[i];
    }

    // Aktualizuj głosy dla sojuszy
    for (int i = 0; i < konfig->liczba_sojuszy; i++) {
        Sojusz *sojusz = &konfig->sojusze[i];
        sojusz->suma_glosow = 0;
        for (int j = 0; j < sojusz->liczba_komitetow; j++) {
            int idx = znajdz_komitet(konfig, sojusz->nazwy_komitetow[j]);
            sojusz->suma_glosow += glosy_okregu[idx];
        }
    }

    Iloraz *ilorazy = malloc(sizeof(Iloraz) * konfig->liczba_komitetow * mandaty_okregu);
    int liczba_ilorazow = 0;
    
    // Oblicz ilorazy tylko dla komitetów, które przekroczyły próg
    for (int i = 0; i < konfig->liczba_komitetow; i++) {
        if (!konfig->komitety[i].w_sojuszu && przekroczyl_prog(konfig, i, suma_glosow)) {
            for (int j = 1; j <= mandaty_okregu; j++) {
                double dzielnik = konfig->metoda_sainte_lague ? (2 * j - 1) : j;
                ilorazy[liczba_ilorazow].iloraz = glosy_okregu[i] / dzielnik;
                ilorazy[liczba_ilorazow].indeks_komitetu = i;
                ilorazy[liczba_ilorazow].suma_glosow = glosy_okregu[i];
                liczba_ilorazow++;
            }
        }
    }

    // Dodaj ilorazy dla sojuszy
    for (int i = 0; i < konfig->liczba_sojuszy; i++) {
        Sojusz *sojusz = &konfig->sojusze[i];
        if (((double)sojusz->suma_glosow * 100.0 / suma_glosow) >= 8.0) {
            for (int j = 1; j <= mandaty_okregu; j++) {
                double dzielnik = konfig->metoda_sainte_lague ? (2 * j - 1) : j;
                ilorazy[liczba_ilorazow].iloraz = sojusz->suma_glosow / dzielnik;
                ilorazy[liczba_ilorazow].indeks_komitetu = -i - 1; // Użyj ujemnych indeksów dla sojuszy
                ilorazy[liczba_ilorazow].suma_glosow = sojusz->suma_glosow;
                liczba_ilorazow++;
            }
        }
    }
    
    qsort(ilorazy, liczba_ilorazow, sizeof(Iloraz), porownaj_ilorazy);
    
    // Przydziel mandaty
    for (int i = 0; i < mandaty_okregu && i < liczba_ilorazow; i++) {
        if (ilorazy[i].indeks_komitetu >= 0) {
            konfig->komitety[ilorazy[i].indeks_komitetu].mandaty++;
        } else {
            konfig->sojusze[-(ilorazy[i].indeks_komitetu + 1)].mandaty++;
        }
    }
    
    free(ilorazy);
}

int main(int argc, char *argv[]) {
    Konfiguracja konfig = {0};  // Inicjalizacja zerami
    
    // Parsuj argumenty wiersza poleceń
    if (!parsuj_argumenty(argc, argv, &konfig)) {
        return 1;
    }
    
    // Wczytaj dane wejściowe
    if (!wczytaj_dane_csv(&konfig)) {
        return 1;
    }
    
    // Wczytaj i przetwórz dane z okręgów
    char wiersz[MAX_LINE_LENGTH];
    while (fgets(wiersz, MAX_LINE_LENGTH, stdin) != NULL) {
        char *token = strtok(wiersz, ";");
        if (token == NULL) continue;
        
        // Wczytaj liczbę mandatów w okręgu
        token = strtok(NULL, ";");
        if (token == NULL) {
            printf("Error: invalid input format\n");
            return 1;
        }
        int mandaty_okregu = atoi(token);
        
        // Wczytaj głosy na komitety
        long long glosy_okregu[MAX_COMMITTEES] = {0};
        for (int i = 0; i < konfig.liczba_komitetow; i++) {
            token = strtok(NULL, ";\n");
            if (token == NULL || (*token == '\0')) {
                glosy_okregu[i] = 0;
            } else {
                glosy_okregu[i] = atoll(token);
                konfig.komitety[i].glosy += glosy_okregu[i];
            }
        }
        
        rozdziel_mandaty(&konfig, mandaty_okregu, glosy_okregu);
    }
    
    // Wyświetl wyniki
    for (int i = 0; i < konfig.liczba_komitetow; i++) {
        if (!konfig.komitety[i].w_sojuszu && konfig.komitety[i].mandaty > 0) {
            printf("%s %d\n", konfig.komitety[i].nazwa, konfig.komitety[i].mandaty);
        }
    }
    
    // Wyświetl wyniki sojuszy
    for (int i = 0; i < konfig.liczba_sojuszy; i++) {
        if (konfig.sojusze[i].mandaty > 0) {
            printf("Sojusz(");
            for (int j = 0; j < konfig.sojusze[i].liczba_komitetow; j++) {
                printf("%s%s", konfig.sojusze[i].nazwy_komitetow[j],
                       j < konfig.sojusze[i].liczba_komitetow - 1 ? ";" : "") ;
            }
            printf(") %d\n", konfig.sojusze[i].mandaty);
        }
    }
    
    // Zwolnij pamięć
    for (int i = 0; i < konfig.liczba_sojuszy; i++) {
        for (int j = 0; j < konfig.sojusze[i].liczba_komitetow; j++) {
            free(konfig.sojusze[i].nazwy_komitetow[j]);
        }
    }
    
    return 0;
}
