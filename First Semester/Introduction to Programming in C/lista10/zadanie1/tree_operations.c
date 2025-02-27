//Karol Nowocień 351907 lista 10 zadanie 1
#include <stdio.h>   // Dla funkcji printf, sprintf
#include <stdlib.h>  // Dla funkcji malloc, free
#include "tree.h"    // Własny plik nagłówkowy z deklaracjami

// Funkcja tworząca nowy węzeł drzewa
TreeNode* createNode(int row, int col, int n) {
    // Alokacja pamięci dla nowego węzła
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    
    // Inicjalizacja pól węzła
    node->row = row;           // Ustawienie wiersza
    node->col = col;           // Ustawienie kolumny
    node->attackingCol = -1;   // Początkowo węzeł nie jest atakowany
    node->isSuccess = 0;       // Początkowo nie jest to rozwiązanie
    node->childrenCount = 0;   // Początkowo nie ma dzieci
    
    // Alokacja pamięci na tablicę dzieci
    node->children = (TreeNode**)malloc(n * sizeof(TreeNode*));
    // Inicjalizacja wskaźników na NULL
    for (int i = 0; i < n; i++) node->children[i] = NULL;
    return node;
}

// Funkcja sprawdzająca czy pole nie jest atakowane przez inne hetmany
int isFree(int rows[], int row, int col) {
    for (int i = 0; i < row; i++) {
        // Sprawdzenie kolumny i przekątnych
        if (rows[i] == col || abs(rows[i] - col) == row - i) {
            return 0;  // Pole jest atakowane
        }
    }
    return 1;  // Pole jest bezpieczne
}

// Funkcja znajduje kolumnę hetmana, który atakuje dane pole
int findAttackingColumn(int rows[], int row, int col) {
    for (int i = 0; i < row; i++) {
        // Sprawdzenie kolumny i przekątnych
        if (rows[i] == col || abs(rows[i] - col) == row - i) {
            return i;  // Zwraca indeks atakującego hetmana
        }
    }
    return -1;  // Brak atakującego hetmana
}

// Funkcja rekurencyjnie budująca drzewo decyzyjne
void buildTree(TreeNode* parent, int rows[], int row) {
    // Warunek końcowy - wszystkie hetmany zostały ustawione
    if (row == N) {
        parent->isSuccess = 1;
        return;
    }

    // Próbujemy ustawić hetmana w każdej kolumnie bieżącego wiersza
    for (int col = 0; col < N; col++) {
        // Sprawdzamy czy pole jest atakowane
        int attackingCol = findAttackingColumn(rows, row, col);
        // Tworzymy nowy węzeł dla tej próby
        TreeNode* child = createNode(row, col, N);
        child->attackingCol = attackingCol;
        
        if (attackingCol == -1) {  // Jeśli pole jest bezpieczne
            rows[row] = col;        // Ustawiamy hetmana
            parent->children[parent->childrenCount++] = child;
            buildTree(child, rows, row + 1);  // Rekurencja dla następnego wiersza
            rows[row] = -1;         // Cofamy ruch
        } else {  // Jeśli pole jest atakowane
            parent->children[parent->childrenCount++] = child;
        }
    }
}

// Funkcja wyświetlająca drzewo w prostym formacie
void printTree(TreeNode* root, int depth) {
    if (!root) return;

    // Wyświetlanie wcięć
    for (int i = 0; i < depth; i++) printf("  ");
    printf("(%d, %d)\n", root->row, root->col);

    // Rekurencyjne wyświetlanie dzieci
    for (int i = 0; i < root->childrenCount; i++) {
        printTree(root->children[i], depth + 1);
    }
}

// Funkcja zwalniająca pamięć zajętą przez drzewo
void freeTree(TreeNode* root) {
    if (!root) return;
    // Rekurencyjne zwalnianie pamięci dzieci
    for (int i = 0; i < root->childrenCount; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);  // Zwolnienie tablicy dzieci
    free(root);           // Zwolnienie węzła
}

// Funkcja wyświetlająca drzewo w ładnym formacie
void printTreeFormatted(TreeNode* node, char* prefix, int isLast) {
    if (!node) return;

    // Wyświetlamy informacje tylko dla właściwych węzłów (nie dla roota)
    if (node->row >= 0) {
        printf("%s", prefix);  // Wyświetl prefiks
        
        // Wybierz odpowiedni symbol dla gałęzi
        if (node->childrenCount > 0)
            printf("+-\\");
        else
            printf("+--");
        
        // Wyświetl informacje o węźle
        if (node->attackingCol == -1) {
            printf(" Kolumna %d wiersz %d nie jest atakowany, stawiamy hetmana",
                   node->col, node->row);
            if (node->isSuccess) printf(" - SUKCES!");
            printf("\n");
        } else {
            printf(" Kolumna %d wiersz %d jest atakowany przez hetmana z kolumny %d\n",
                   node->col, node->row, node->attackingCol);
        }
    }

    // Rekurencyjne wyświetlanie dzieci z odpowiednimi prefiksami
    char newPrefix[1000];
    for (int i = 0; i < node->childrenCount; i++) {
        if (node->row >= 0) {
            sprintf(newPrefix, "%s%s", prefix, 
                    isLast ? "  " : "| ");
        } else {
            sprintf(newPrefix, "%s", prefix);
        }
        
        printTreeFormatted(node->children[i], newPrefix, 
                          i == node->childrenCount - 1);
    }
}
