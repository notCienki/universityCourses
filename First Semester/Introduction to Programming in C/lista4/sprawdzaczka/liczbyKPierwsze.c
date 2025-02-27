#include <stdio.h>
#include <stdbool.h>

#define MAX_N 40000

// Funkcja do znalezienia liczb pierwszych za pomocą sita Eratostenesa
void sitoEratostenesa(bool *sito, int n) {
    for (int i = 2; i * i <= n; i++) {
        if (sito[i]) {
            for (int j = i * i; j <= n; j += i) {
                sito[j] = false;
            }
        }
    }
}

// Funkcja do obliczenia liczby czynników pierwszych (z powtórzeniami) dla każdej liczby
void liczbaCzynnikowPierwszych(int *czynniki, int n) {
    for (int i = 2; i <= n; i++) {
        if (czynniki[i] == 0) { // liczba i jest liczbą pierwszą
            for (int j = i; j <= n; j += i) {
                int temp = j;
                while (temp % i == 0) {
                    czynniki[j]++;
                    temp /= i;
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    bool sito[MAX_N + 1];
    int czynniki[MAX_N + 1] = {0};

    // Inicjalizacja
    for (int i = 0; i <= n; i++) sito[i] = true;
    sitoEratostenesa(sito, n); // Sito Eratostenesa do liczb pierwszych
    liczbaCzynnikowPierwszych(czynniki, n); // Obliczanie liczby czynników pierwszych dla każdej liczby
    
    // Zbieranie liczb 1-pierwszych, 5-pierwszych i 7-pierwszych
    int liczby_1_pierwsze[MAX_N + 1] = {0};
    int liczby_5_pierwsze[MAX_N + 1] = {0};
    int liczby_7_pierwsze[MAX_N + 1] = {0};
    
    for (int i = 2; i <= n; i++) {
        if (sito[i]) liczby_1_pierwsze[i] = 1; // Liczba pierwsza jest 1-pierwsza
        if (czynniki[i] == 5) liczby_5_pierwsze[i] = 1; // Liczba 5-pierwsza
        if (czynniki[i] == 7) liczby_7_pierwsze[i] = 1; // Liczba 7-pierwsza
    }

    // Zliczanie rozwiązań
    int liczbaRozwiazan = 0;
    for (int a = 2; a <= n; a++) {
        if (liczby_1_pierwsze[a]) {
            for (int b = 2; b <= n; b++) {
                if (liczby_5_pierwsze[b]) {
                    int c = n - a - b;
                    if (c >= 2 && c <= n && liczby_7_pierwsze[c]) {
                        liczbaRozwiazan++;
                    }
                }
            }
        }
    }

    // Wypisanie wyniku
    printf("%d\n", liczbaRozwiazan);

    return 0;
}
