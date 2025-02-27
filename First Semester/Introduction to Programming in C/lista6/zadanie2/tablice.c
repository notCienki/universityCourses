#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
  int dlugosc=0;
  scanf("%d", &dlugosc);

  int S[dlugosc], T[dlugosc];
  for(int i=0; i<dlugosc; i++)
  {
    int tmp=0;
    scanf("%d", &tmp);
    S[i]=tmp;
  }
  for(int i=0; i<dlugosc; i++)
  {
    int tmp=0;
    scanf("%d", &tmp);
    T[i]=tmp;
  }


  int r[1001];
  srand=(time(NULL));
  for(int i=0; i<1001; i++)
  {
    r[i]=rand();
  }


  int P[dlugosc], Q[dlugosc];
  P[0]=r[S[0]];
  Q[0]=r[T[0]];
  for(int i=1; i<dlugosc; i++)
  {
    P[i]=P[i-1]^r[S[i]];
  }
  for(int i=1; i<dlugosc; i++)
  {
    Q[i]=Q[i-1]^r[T[i]];
  }


  int liczbaZ=0;
  scanf("%d", &liczbaZ);

  for(int z=0; z<liczbaZ; z++)
  {
    int i=0,j=0,k=0;
    scanf("%d %d %d", &i, &j, &k);

    int hashS=0, hashT=0;
    if(i==0)
      hashS=P[i+k];
    else
      hashS=P[i+k]^P[i-1];

   if(j==0)
      hashT=Q[j+k];
    else
      hashT=Q[j+k]^Q[j-1];
      
    if(hashS==hashT)
      printf("TAK\n");
    else
      printf("NIE\n");

  }

  return 0;
}