#include<stdio.h>

int main(void)
{
  int n;//n naturalne oznaczajace dlugosc ciagu
  scanf("%d", &n);//wprowadzenie n
  int tab[1000005];//deklaracja tablicy zaelznosci mniejszej o 1 od n
  for(int i=0; i<n-1; i++)//petla ktora wprowadza liczby do tablicy
  {
    scanf("%d", &tab[i]);
  }

  int ciag[1000005];//deklaracja tablicy ktora bedzie zawierala ostateczny ciag
  ciag[0]=0;//pierwszy elemnt ciagu jako najmniejsza naturalna
  for(int i=1; i<n; i++)//przechodzimy po zaleznosciach i ustawiamy ciag
  {
    if(tab[i-1]==-1)
      ciag[i]=ciag[i-1]-1;
    else
      ciag[i]=ciag[i-1]+1;
  }

  //szukamy najmniejszej wartosci w ciagu
  int najmniejsza=ciag[0];
  for(int i=1; i<n; i++)
    if(ciag[i]<najmniejsza)
        najmniejsza=ciag[i];
  
  for(int i = 0; i < n; i++) 
  {
    ciag[i] -= najmniejsza;
  }

  for(int i=0; i<n; i++)
  {
    //przechodze po ciagu od pierwszego elementu
    if(ciag[i]==0)//jezeli element jest rowny 0 to zwiekszam go na 1
      ciag[i]+=1;
  }
  
  while(najmniejsza<=0){
  for(int i=1; i<n; i++)
  {
    if(ciag[i]==ciag[i-1])
    {
      if(tab[i-1]==-1)
        ciag[i-1]+=1;
      else
        ciag[i]+=1;
    }
  }
  najmniejsza++;
  }

  for(int i=0; i<n; i++)
    printf("%d ", ciag[i]);

  return 0;
}