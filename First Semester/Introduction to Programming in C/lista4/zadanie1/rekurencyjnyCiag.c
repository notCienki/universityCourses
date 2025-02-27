#include<stdio.h>
#include<stdlib.h>

// Funkcja rekurencyjna obliczająca wartość n-tego wyrazu ciągu. 
// `n` - indeks wyrazu do obliczenia,
// `k` - liczba współczynników,
// `a[]` - współczynniki rekurencji,
// `f[]` - wartości początkowe ciągu.
double ciag(int n, int k, double a[], double f[]) 
{
  // Jeśli `n` jest mniejsze niż `k`, zwracam gotową wartość z tablicy początkowych.
  if(n < k)
    return f[n];

  // Jeśli `n >= k`, muszę obliczyć wartość jako sumę ważoną.
  double suma = 0;
  // Pętla: sumuję iloczyny współczynników `a[i]` i wyrazów ciągu wyznaczonych rekurencyjnie.
  for(int i = 0; i < k; i++) {
    suma += a[i] * ciag(n - i - 1, k, a, f); // Wywołanie rekurencyjne.
  }

  // Debugowy print wyniku w trakcie obliczeń.
  printf("Wynik f(%d) = %.6f\n", n, suma);

  // Zwracam wynik dla f(n).
  return suma;
}

int main(int argc, char *argv[]) 
{
  // Sprawdzam, czy liczba argumentów jest wystarczająca.
  if (argc < 3) {
    printf("Użyj: %s k a_0 a_1 ... a_(k-1) f(0) f(1) ... f(k-1)\n", argv[0]);
    return 1; // Błąd: za mało argumentów.
  }

  // Wczytuję `k` jako liczbę współczynników.
  int k = atoi(argv[1]);
  if (k <= 0) {
    printf("k musi być liczbą całkowitą większą od zera.\n");
    return 1; // Błąd: `k` nie jest poprawne.
  }

  // Sprawdzam, czy liczba podanych argumentów jest zgodna z oczekiwaniem.
  if (argc != 2 * k + 2) {
    printf("Nieprawidłowa liczba argumentów. Oczekiwano %d argumentów.\n", 2 * k + 1);
    return 1; // Błąd: złe dane wejściowe.
  }

  // Wczytuję współczynniki `a` z argumentów.
  double a[k];
  for(int i = 0; i < k; i++) {
    a[i] = atof(argv[2 + i]); // Konwersja argumentu na double.
  }

  // Wczytuję początkowe wartości ciągu `f` z argumentów.
  double f[k];
  for(int i = 0; i < k; i++) {
    f[i] = atof(argv[2 + k + i]); // Konwersja argumentu na double.
  }

  // Pytam użytkownika o wartość `n`, którą chcemy obliczyć.
  int n;
  printf("Podaj nieujemną liczbę n: ");
  if (scanf("%d", &n) != 1 || n < 0) {
    printf("n musi być nieujemną liczbą całkowitą.\n");
    return 1; // Błąd: `n` niepoprawne.
  }

  // Obliczam f(n) przy użyciu funkcji rekurencyjnej.
  double fn = ciag(n, k, a, f);

  // Wyświetlam końcowy wynik.
  printf("f(%d) = %f\n", n, fn);

  return 0; // Zakończenie programu.
}
