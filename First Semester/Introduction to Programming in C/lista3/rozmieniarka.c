//Karol Nowocień 351907 Lista3 Zadanie2
#include<stdio.h>//biblioteka do printf
#include<string.h>//biblioteka do strlen
#include<ctype.h>//biblioteka do isdigit

int konwersja_na_grosze(char znaki[])//funkcja ktora bedzie konwertowala naszego stringa na inta w groszach
{
    int dlugosc=strlen(znaki);//dlugosc ktora bedzie potrzebna do petli
    int grosze=0;//tu bedziemy przechowywac ostateczny wynik w groszach
    int przecinek=0;//flaga ktora bedzie mowila o przecinku badz kropce
    int liczby_po_przecinku=0;//bedziemy liczyc aby byly tylko 2 liczby po przecinku

    for(int i=0; i<dlugosc; i++)//petla po calym stringu
    {
      if(isdigit(znaki[i]))
      {
        grosze=grosze*10+(znaki[i]-'0');//dodajemy kolejne cyfry do wyniku
        if(przecinek) liczby_po_przecinku++;//jeśli jesteśmy juz po przecinku to dopisujemy ktora to liczba po nim

      }
      else if(znaki[i]==',' || znaki[i]=='.')//jesli znak jest przecinkiem badz kropka
        przecinek=1;//ustawiamy flage
      else
        return -1;//jesli znak nie jest ani liczba ani separatorem zwracamy blad
    }
    if(liczby_po_przecinku>2)
      return -1;//jesli liczb po separatorze jest wiecej niz 2 zwracamy blad
    if(liczby_po_przecinku==1)
      grosze*=10;//jesli jest tylko jedna liczba po separatorze to mnozymy przez 10 aby otrzymac wynik w groszach
    if(liczby_po_przecinku==0)
      grosze*=100;//analogicznie do poprzedniego

  return grosze;
}

void rozmieniarka(int grosze)
{
  int kasa[]={500, 200, 100, 50, 20, 10, 5, 2, 1};//tablica zawierajca wartosci naszych monet
  for(int i=0; i<9; i++)//iterujemy po kazdym nominale
  {
    int ilosc=0;//zliczamy ilosc danego nominalu
    while(grosze>=kasa[i])//petla ktora odejmuje dany nominal tyle ile moze
    {
        ilosc++;
        grosze-=kasa[i];
    }

    if(ilosc>0 && i<=2)//jesli jest jakis nominal ale jest w zl
    {
      kasa[i]/=100;//tu zamieniamy grosze na zl aby wyjscie bylo dobre
      printf("%dx%dzl\n", ilosc, kasa[i]);
    }
    else if(ilosc>0)//jesli jest jakis nominal ale w groszach
    {
      printf("%dx%dgr\n", ilosc, kasa[i]);
    }
  }
}

int main(int argc, char *argv[])
{
  if(argc<=1)//kiedy nie podamy zadnego wejscia poza ./a.out
  {
    printf("Blad\n");
    return 1;
  }
  
  int kwota=konwersja_na_grosze(argv[1]);
  if(kwota == -1)//kiedy nie zostala podana poprawna kwota
  {
    printf("Blad\n");
    return 1;
  }

  if(kwota==0)
    printf("0zl\n");

  if(kwota>0)//kiedy zostalo podane poprawne wejscie
  {
    rozmieniarka(kwota);
  }

  return 0;
}