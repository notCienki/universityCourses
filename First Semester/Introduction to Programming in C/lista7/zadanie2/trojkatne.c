//Karol Nowocien 351907 lista 7 zadanie 2
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int dividers(int n)
{
  if(n==1)
    return 1;

  int counter=0;
  for(int i=1; i<=sqrt(n); i++)
  {
    if(n%i==0)
    {
      if(n/i==1)
        counter++;
      else
        counter+=2;
    }
  }
  return counter;
}

void liczba_trojkatna(int n)
{
  unsigned long liczba=1, i=1;
  while(dividers(liczba)<=n)
  {
    i++;
    liczba+=i;
  }
  printf("Indeks: %lu\n", i);
  printf("Liczba trójkątna: %lu\n", liczba);
  //print debug:
  //printf("Ilość dzielników: %d\n", dividers(liczba));
}

int main(int argc, char *argv[])
{
  if(argc<=1)
    return 1;

  char *endptr;
  unsigned long n = strtoul(argv[1], &endptr, 10);

  // Sprawdzenie, czy konwersja była poprawna
  if (*endptr != '\0') 
  {
    printf("Niepoprawny argument: %s\n", argv[1]);
    return 1;
  }
  
  liczba_trojkatna(n);

  return 0;
}