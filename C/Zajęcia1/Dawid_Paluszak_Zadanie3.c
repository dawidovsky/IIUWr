#include <stdio.h>
#include <math.h>
int pierwsze (int liczba)
{
    if(liczba == 2 || liczba == 3)
        return 1;
    else if(liczba % 2 != 0)
    {
        for (int i=3;i<=sqrt(liczba);i=i+2)
        {
            if (liczba % i == 0)
            {
                return 0;
            }
        }
                return 1;
    }
    return 0;
}
int main ()
{
    int n,liczba_pierwsza_1,wynik=0,liczba_pierwsza_2;
    scanf ("%d", &n);
    int p=2,q=n-p;
    if(n > 2 && n % 2 == 0)
    {
        for(int i=2;i<=n/2;i++)
        {
                liczba_pierwsza_1 = pierwsze(p);
                liczba_pierwsza_2 = pierwsze(q);
                if(liczba_pierwsza_1 == 1 && liczba_pierwsza_2 == 1)
                     wynik++;
                p++;
                q--;
        }
      printf("%d",wynik);
    }
    else
        printf("NIEPOPRAWNA LICZBA");
}
