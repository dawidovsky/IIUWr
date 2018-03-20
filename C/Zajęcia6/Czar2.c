#include <stdio.h>
void Znajdowanie(int wys,int szer ,int maxw , int maxs,int plansza[][maxs])
{
    plansza[wys][szer] = 0;
    if(wys>0)
    {
        if(szer>0)
            if(plansza[wys-1][szer-1]==1)
            {
                Znajdowanie(wys-1,szer-1,maxw,maxs,plansza);
            }
        if(plansza[wys-1][szer]==1)
        {
            Znajdowanie(wys-1,szer,maxw,maxs,plansza);
        }
        if(szer<maxs)
            if(plansza[wys-1][szer+1]==1)
            {
                Znajdowanie(wys-1,szer+1,maxw,maxs,plansza);
            }
    }
    if(szer>0)
    {
        if(plansza[wys][szer-1]==1)
        {
            Znajdowanie(wys,szer-1,maxw,maxs,plansza);
        }
        if(wys<maxw)
            if(plansza[wys+1][szer-1]==1)
            {
                 Znajdowanie(wys+1,szer-1,maxw,maxs,plansza);
            }
    }
    if(szer<maxs)
    {
        if(plansza[wys][szer+1]==1)
        {
             Znajdowanie(wys,szer+1,maxw,maxs,plansza);
        }
        if(wys<maxw)
            if(plansza[wys+1][szer+1]==1)
            {
                 Znajdowanie(wys+1,szer+1,maxw,maxs,plansza);
            }
    }
    if(wys<maxw)
        if(plansza[wys+1][szer]==1)
        {
             Znajdowanie(wys+1,szer,maxw,maxs,plansza);
        }

}
int main()
{
    int szer,wys;
    scanf("P1\n%d %d\n", &szer, &wys);
    int plansza[wys][szer];
    for(int i=0;i<wys;i++)
        for(int j=0;j<szer;j++)
            scanf("%d", &plansza[i][j]);
    int wynik=0;
    for(int i=0;i<wys;i++)
    {
        for(int j=0;j<szer;j++)
        {
            if(plansza[i][j]==1)
            {
                Znajdowanie(i,j,wys,szer,plansza);
                wynik++;
            }
        }
    }
    printf("%d",wynik);
}
