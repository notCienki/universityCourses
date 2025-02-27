#include<stdio.h>
#include<stdio.h>
int main(void)
{
  unsigned int n; //deklaracja liczy naturalnej n
  printf("Podaj N: \n");
  scanf("%u", &n);
  //sprawdzenie warunku zadania
    while(n<12)
    {
      printf("N nie jest zgodne z poleceniem!\n");
      scanf("%u", &n);
    }
    printf("\n");

  unsigned int tablica[n+1];//deklaracja tablicy w ktorej będą przechowywane wartości tego ile ktore M ma trojkatow
  //petla ktora ustwi wszystkie wartosci w tablicy na 0
  for(unsigned int i=0; i<=n; i++)
    tablica[i]=0;
  
  //pętla po wszystkich m'ach
  for(unsigned int m=12; m<=n; m++)
  {
    //teraz zrobimy petle ktore beda sprawdzaly trzy boki a b c
    for(unsigned int a=1; a<=m/3; a++)
      for(unsigned int b=a+1; b<=(m-a)/2; b++)
      {
          unsigned int c=m-a-b;
          //teraz majac trzy boki sprawdzimy warunek trojkata
          //a nastepnie warunek trojkata pitagorejskiego
          if(a<b && b<c && (a+b>c) && (a+c>b) && (c+b>a) && (a*a+b*b==c*c))
            tablica[m]++;
      }
  }

  //deklaracja zmiennej przechowujacej najwieksze m i zmiennej najwiekszej ilosci trojkatow
  unsigned int najwieksze_m=0, najwieksza_ilosc_trojkatow=0;
  
  //petla ktora iteruje po tablicy i szuka najwiekszego m;
  for(unsigned int i=12; i<=n; i++)
  {
    if(tablica[i]>najwieksza_ilosc_trojkatow)
    {
      najwieksza_ilosc_trojkatow=tablica[i];
      najwieksze_m=i;
    }
  }
  printf("Dla liczby %u maksimum wynosi %u i jest osiągane przez liczbe %u\n", n, najwieksza_ilosc_trojkatow, najwieksze_m);

  return 0;
}
