#include <stdio.h>
int Szukanie(int x,int y, int n, int m, char pole[][m],int czas)
{
    pole[x][y] = '#';
    if(pole[x+1][y] == '-' && x < n)
    {
        czas = Szukanie(x+1,y,n,m,pole,czas);
    }
    if(pole[x-1][y] == '-' && x >= 0)
    {
        czas = Szukanie(x-1,y,n,m,pole,czas);
    }
    if(pole[x][y+1] == '-' && y < m)
    {
        czas = Szukanie(x,y+1,n,m,pole,czas);
    }
    if(pole[x][y-1] == '-' && y >= 0)
    {
        czas = Szukanie(x,y-1,n,m,pole,czas);
    }
    return ++czas;
}
int Sprawdzenie(int n, int m, char pole[][m])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(pole[i][j] == '-') return -1;
    return 0;
}
int main()
{
    int n,m;
    scanf("%d %d\n",&n,&m);
    char pole[n][m],dane[101];
    for(int i=0;i<n;i++)
        {
            fgets(dane,101,stdin);
            for(int j=0;j<m;j++)
            {
                pole[i][j] = dane[j];
            }
        }
    int x,y;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(pole[i][j] == '!')
            {
                x = i;
                y = j;
            }
    int czas = 0;
    czas = Szukanie(x,y,n,m,pole,czas);
    int wynik = Sprawdzenie(n,m,pole);
    if(wynik == 0)
        printf("%d",czas);
    else printf("%d",wynik);
}
