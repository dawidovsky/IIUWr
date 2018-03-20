#include <stdio.h>
#include <stdlib.h>
void Znajdowanie(int wys,int szer ,int maxw , int maxs,int **plansza)
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
    char znaki[71],asd[100];
    int szer,wys;
    fgets(asd,100,stdin);
    fgets(asd,100,stdin);
    sscanf(asd,"%d %d",&szer,&wys);
    int **plansza;
    plansza=malloc(sizeof(**plansza));
    for(int i=0;i<wys;i++)
    {
        fgets(znaki,71,stdin);
        for(int j=0;j<szer;j++)
        {
            plansza[i][j]=znaki[j*2]-48;
        }
    }
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
