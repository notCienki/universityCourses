#include<stdio.h>
#include<string.h>

int main(void)
{
  char wzorzec[61], ciag[10001];
  scanf("%s %s", wzorzec, ciag);

  int wzorzecLiczba=0, dlugoscWzorca=strlen(wzorzec);
  for(int i=0; i<dlugoscWzorca; i++)
  {
    wzorzecLiczba=(wzorzecLiczba<<1) | (wzorzec[i]-'0');
  }
  printf("wzorzec: %s\nwzorzecLiczba: %d\n", wzorzec, wzorzecLiczba);

  int dlugoscCiagu=strlen(ciag), okno=0;
  for (int j = 0; j < dlugoscWzorca; j++) 
  {
    okno = (okno << 1) | (ciag[j] - '0');
  }

  for (int i = 0; i <= dlugoscCiagu - dlugoscWzorca; i++) 
  {
    okno = ((okno << 1) | (ciag[i + dlugoscWzorca] - '0')) & ((1 << dlugoscWzorca) - 1);
    
    if(okno == wzorzecLiczba) 
    {
      printf("%d, ", i+1);
    }
  }

  return 0;
}