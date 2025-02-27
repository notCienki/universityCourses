//Karol Nowocień 351907 Lista2 zadanie2
#include <stdio.h>

int rozneCzynnikiNieparzyste(int rozkladana)
{
    int ileCzynnikow=0, ostatniDzielnik=1;
    for(int dzielnik = 2; dzielnik <= rozkladana; dzielnik++) 
    {
        while(rozkladana % dzielnik == 0) 
        {
            if((dzielnik%2 != 0) && (dzielnik != ostatniDzielnik))
            {
                ileCzynnikow++;
                ostatniDzielnik=dzielnik;
            }
            rozkladana = rozkladana / dzielnik;
        }
    }

return ileCzynnikow;
}

int main(void)
{
    int n, liczba, najmniejsza1=1000000, najmniejsza2=1000000, najmniejsza3=1000000;

    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        scanf("%d", &liczba);
        if(liczba<najmniejsza1)
        {
            najmniejsza3=najmniejsza2;
            najmniejsza2=najmniejsza1;
            najmniejsza1=liczba;
        }
        else if(liczba<najmniejsza2)
        {
            najmniejsza3=najmniejsza2;
            najmniejsza2=liczba;
        }
        else if(liczba<najmniejsza3)
        {
            najmniejsza3=liczba;
        }

    }
    
    printf("\n");
    printf("%d\n", najmniejsza1);
    printf("%d\n", najmniejsza2);
    printf("%d\n", najmniejsza3);

    //int rozneCzynniki1=rozneCzynnikiNieparzyste(najmniejsza1);
    //int rozneCzynniki2=rozneCzynnikiNieparzyste(najmniejsza2);
    //int rozneCzynniki3=rozneCzynnikiNieparzyste(najmniejsza3);
    
    if(rozneCzynnikiNieparzyste(najmniejsza1)>=rozneCzynnikiNieparzyste(najmniejsza2) && rozneCzynnikiNieparzyste(najmniejsza1)>=rozneCzynnikiNieparzyste(najmniejsza3))
       printf("%d\n", najmniejsza1); 
    else if(rozneCzynnikiNieparzyste(najmniejsza2)>=rozneCzynnikiNieparzyste(najmniejsza1) && rozneCzynnikiNieparzyste(najmniejsza2)>=rozneCzynnikiNieparzyste(najmniejsza3))
        printf("%d\n", najmniejsza2);
    else if(rozneCzynnikiNieparzyste(najmniejsza3)>=rozneCzynnikiNieparzyste(najmniejsza1) && rozneCzynnikiNieparzyste(najmniejsza3)>=rozneCzynnikiNieparzyste(najmniejsza2))
        printf("%d\n", najmniejsza3);
return 0;
}