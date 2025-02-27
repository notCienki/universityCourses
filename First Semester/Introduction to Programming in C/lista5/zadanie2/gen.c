#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int Funkcja(int x)
{
  return (int)(sin(x)*14);
}

int main(int argc, char *argv[])
{
  int n=80;

  if(argc>1 && atoi(argv[1])<0)
  {
    printf("n powinno byc liczba calkowita!\n");
    return 1;
  } 

  if(argc>1 && atoi(argv[1])>0)
    n = atoi(argv[1]);  
  printf("%d\n", n);

  
  int y[n];
  for(int i=0; i<n; i++)
  {
    y[i]=Funkcja(i);
    printf("%d ", y[i]);
  }


  int max=y[0], min=y[0];
  for(int i=1; i<n; i++)
  {
    if (y[i] > max) max = y[i];
    if (y[i] < min) min = y[i];
  }
  if (0 > max) max = 0;
  if (0 < min) min = 0;


  int roznica = max - min;
  if (roznica < 10 || roznica > 40)
  {
    printf("Różnica NIE mieści się w wymaganym zakresie (10-40)\n");
    return 1;
  }
  
  
  return 0;
}