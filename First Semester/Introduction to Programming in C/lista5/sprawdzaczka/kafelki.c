#include<stdio.h>
#include<limits.h>  // Biblioteka do użycia INT_MAX

int main(void)
{
  int n, m;
  // Wczytujemy liczby n (wiersze) i m (kolumny)
  scanf("%d %d", &n, &m);

  // Sprawdzamy, czy n jest zgodne z wymaganiem (n <= 1000)
  if (n > 1000)
  {
    printf("n nie zgodne ze specyfikacja!\n");  // Jeśli n jest większe niż 1000, wyświetlamy komunikat o błędzie
    return 1;  // Kończymy program z kodem błędu 1
  }

  // Tworzymy tablicę podloga, która przechowuje kary na każdym kafelku (n wierszy i m kolumn)
  int podloga[n][m];
  // Wczytujemy wartości kar dla każdego kafelka
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      int tmp;
      // Sprawdzamy, czy wczytano poprawną liczbę (całkowitą) i czy nie jest większa niż 1000
      if (scanf("%d", &tmp) != 1 || tmp > 1000)
        return 1;  // Jeśli wczytanie się nie powiedzie lub wartość jest za duża, kończymy program

      podloga[i][j] = tmp;  // Przypisujemy wartość do odpowiedniego kafelka na posadzce
    }

  // Tworzymy tablicę najmniejszePrzejscie, która będzie przechowywać minimalną karę do każdego kafelka
  int najmniejszePrzejscie[n][m];

  // Inicjalizujemy pierwszą kolumnę: minimalne przejście na pierwszą kolumnę to po prostu kara kafelka
  for (int i = 0; i < n; i++)
    najmniejszePrzejscie[i][0] = podloga[i][0];

  // Dla każdej kolejnej kolumny (od drugiej do ostatniej) obliczamy minimalną karę przejścia
  for (int j = 1; j < m; j++)
  {
    for (int i = 0; i < n; i++)
    {
      // Skok z poprzedniej kolumny (z tego samego wiersza)
      int skok = najmniejszePrzejscie[i][j-1]; 

      // Sprawdzamy, czy możemy przejść z wiersza powyżej (i-1), biorąc minimalną karę
      if (i > 0 && skok > najmniejszePrzejscie[i-1][j-1])
        skok = najmniejszePrzejscie[i-1][j-1];

      // Sprawdzamy, czy możemy przejść z wiersza poniżej (i+1), biorąc minimalną karę
      if (i < n - 1 && skok > najmniejszePrzejscie[i+1][j-1])
        skok = najmniejszePrzejscie[i+1][j-1];

      // Aktualizujemy wartość minimalnego przejścia dla danego kafelka (w wierszu i, kolumnie j)
      najmniejszePrzejscie[i][j] = podloga[i][j] + skok;
    }
  }

  // Szukamy minimalnej kary przejścia na samą prawą stronę posadzki
  int minimalnaKara = INT_MAX;  // Inicjalizujemy minimalną karę na największą możliwą wartość

  // Sprawdzamy w ostatniej kolumnie (m-1) wszystkie wiersze i wybieramy najmniejszą karę
  for (int i = 0; i < n; i++)
    if (najmniejszePrzejscie[i][m-1] < minimalnaKara)
      minimalnaKara = najmniejszePrzejscie[i][m-1];  // Aktualizujemy minimalną karę, jeśli znajdziemy mniejszą

  // Wyświetlamy minimalną karę, jaką należy zapłacić, aby przejść przez posadzkę
  printf("\n%d\n", minimalnaKara);

  return 0;  // Zakończenie programu
}
