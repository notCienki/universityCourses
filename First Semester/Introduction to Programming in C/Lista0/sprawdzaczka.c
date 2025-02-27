#include<stdio.h>
#include<math.h>

int main(void)
{
  int A=0;
  
  printf(u8"Podaj liczbę: \n");
  scanf("%d", &A);

  for(int i=A; i<=A+1000; i++)
  {
    int counter=0;
    for(int x=2; x<i; x++)
    {
      if(i%(x*x)==0)
      {
        counter=1;
        break;
      }
      else
        x++;
    }
    if(counter==0)
    {
      printf("%d\n", i);
    }

  }
  
  return 0;
}