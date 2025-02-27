//Karol Nowocień 351907 lista 7 zadanie 3
#include<stdio.h>
#include<stdlib.h>

int gcd(int a, int b)
{
    // Find Minimum of a and b
    int result = ((a < b) ? a : b);
    while (result > 0) {
        // Check if both a and b are divisible by result
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }
    // return gcd of a nd b
    return result;
}

int lcm(int a, int b)
{
  return (a*b)/gcd(a,b);
}

int main(void)
{
  int n;
  scanf("%d", &n);
  if(n>1000000)
    return 1;

  int j[n];
  for(int i=0; i<n; i++)
  {
    int tmp;
    scanf("%d", &tmp);
    if(tmp>1000000)
      return 1;
    j[i]=tmp;
  }

  int r=0, p=0, q=0;
  scanf("%d %d %d", &r, &p ,&q);

  int m[n];
  for(int i=0; i<n; i++)
  {
    if(i==0)
      m[i]=lcm(j[n],lcm(j[i], j[i+1]));
    else if(i==n)
      m[i]=lcm(j[i-1],lcm(j[i], j[0]));
    else
      m[i]=lcm(j[i-1],lcm(j[i], j[i+1]));
  }

  int k[n];
  for(int i=0; i<n; i++)
  {
    k[i]=r*m[i];
  }
  int minimumK=k[0];
  for(int i=0; i<n; i++)
    if(k[i]<minimumK)
      minimumK=k[i];

  
  

  return 0;
}