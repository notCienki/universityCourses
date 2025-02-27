#include<stdio.h>

int main(void)
{
  int k, n;
  scanf("%d %d", &k, &n);

  int wagi[n];
  for(int i=0; i<n; i++)
    scanf("%d", &wagi[i]);
  
  int ile=0;
  for(int i=0; i<(1<<n); i++)
  {
    int sumaWag=0;
    for(int j=0; j<n; j++)
    {
      if(i & (1<<j))
        sumaWag+=wagi[j];
    }
    if(sumaWag<k)
      ile++;
  }
  printf("odpowiedz: %d\n", ile);

  return 0;
}