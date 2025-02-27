//Karol Nowocień 351907 lista 10 zadanie 1
#include <stdio.h>   // Dla funkcji printf
#include <stdlib.h>  // Dla funkcji atoi
#include "tree.h"    // Własny plik nagłówkowy

int N;  // Zmienna globalna przechowująca liczbę hetmanów

int main(int argc, char* argv[]) {
    // Sprawdzenie poprawności argumentów
    if (argc != 2) {
        printf("Użycie: %s <liczba_hetmanow>\n", argv[0]);
        return 1;
    }

    // Konwersja argumentu na liczbę i sprawdzenie zakresu
    N = atoi(argv[1]);
    if (N <= 0 || N > MAX_N) {
        printf("Niepoprawna liczba hetmanów. Maksymalna wartość to %d.\n", MAX_N);
        return 1;
    }

    // Inicjalizacja tablicy przechowującej pozycje hetmanów
    int rows[MAX_N];
    for(int i = 0; i < MAX_N; i++) rows[i] = -1;
    
    // Utworzenie korzenia drzewa
    TreeNode* root = createNode(-1, -1, N);
    
    // Budowa drzewa rozwiązań
    buildTree(root, rows, 0);
    
    // Wyświetlenie drzewa
    printTreeFormatted(root, "", 1);
    
    // Zwolnienie pamięci
    freeTree(root);
    return 0;
}
