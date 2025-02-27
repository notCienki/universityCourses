//Karol Nowocień 351907 lista 10 zadanie 1
#ifndef TREE_H  // Zabezpieczenie przed wielokrotnym dołączeniem pliku nagłówkowego
#define TREE_H

#define MAX_N 20  // Maksymalna liczba hetmanów na szachownicy

// Struktura reprezentująca węzeł w drzewie decyzyjnym
typedef struct TreeNode {
    int row, col;           // Pozycja hetmana (wiersz, kolumna)
    int attackingCol;       // Kolumna, z której hetman jest atakowany (-1 jeśli nie jest)
    int isSuccess;         // Flaga oznaczająca czy ta ścieżka prowadzi do rozwiązania
    int childrenCount;     // Liczba dzieci węzła
    struct TreeNode** children;  // Tablica wskaźników na dzieci węzła
} TreeNode;

// Deklaracje funkcji do operacji na drzewie
TreeNode* createNode(int row, int col, int n);  // Tworzy nowy węzeł drzewa
void freeTree(TreeNode* root);                  // Zwalnia pamięć zajętą przez drzewo
void printTree(TreeNode* root, int depth);      // Wyświetla drzewo w prostym formacie
void printTreeFormatted(TreeNode* node, char* prefix, int isLast);  // Wyświetla drzewo w ładnym formacie

// Deklaracje funkcji logiki gry
int isFree(int rows[], int row, int col);  // Sprawdza czy pole nie jest atakowane
int findAttackingColumn(int rows[], int row, int col);  // Znajduje kolumnę atakującego hetmana
void buildTree(TreeNode* parent, int rows[], int row);  // Buduje drzewo decyzyjne

extern int N;  // Deklaracja zewnętrznej zmiennej globalnej przechowującej rozmiar szachownicy

#endif
