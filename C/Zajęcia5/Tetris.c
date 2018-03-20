#include <stdio.h>
struct gra{
    char plansza[201][201];
}pole;
struct gra TypK(int kolumna,struct gra pole,int wys)
{
    int i=0;
    while(pole.plansza[i][kolumna] != 'X' && pole.plansza[i][kolumna+1] != 'X' && i<wys)
    {
        i++;
    }
    pole.plansza[i-1][kolumna] = 'X';
    pole.plansza[i-2][kolumna] = 'X';
    pole.plansza[i-1][kolumna+1] = 'X';
    pole.plansza[i-2][kolumna+1] = 'X';
    return pole;
}
struct gra TypT(int kolumna,struct gra pole,int wys)
{
    int i=0;
    while(pole.plansza[i-1][kolumna] != 'X' && pole.plansza[i][kolumna+1] != 'X'&& pole.plansza[i-1][kolumna+2] != 'X' && i<wys)
    {
        i++;
    }
    pole.plansza[i-1][kolumna+1] = 'X';
    pole.plansza[i-2][kolumna+1] = 'X';
    pole.plansza[i-2][kolumna+2] = 'X';
    pole.plansza[i-2][kolumna] = 'X';
    return pole;
}
struct gra TypI(int kolumna,struct gra pole,int wys)
{
    int i=0;
    while(pole.plansza[i][kolumna] != 'X' && i<wys)
    {
        i++;
    }
    pole.plansza[i-1][kolumna] = 'X';
    pole.plansza[i-2][kolumna] = 'X';
    pole.plansza[i-3][kolumna] = 'X';
    pole.plansza[i-4][kolumna] = 'X';
    return pole;
}
struct gra TypF(int kolumna,struct gra pole,int wys)
{
    int i=0;
    while(pole.plansza[i][kolumna] != 'X' && pole.plansza[i-2][kolumna+1] != 'X' && i<wys)
    {
        i++;
    }
    pole.plansza[i-1][kolumna] = 'X';
    pole.plansza[i-2][kolumna] = 'X';
    pole.plansza[i-3][kolumna] = 'X';
    pole.plansza[i-3][kolumna+1] = 'X';
    return pole;
}
struct gra TypW(int kolumna,struct gra pole,int wys)
{
    int i=0;
    while(pole.plansza[i][kolumna] != 'X' && pole.plansza[i][kolumna+1] != 'X' && pole.plansza[i][kolumna+2] != 'X' && pole.plansza[i][kolumna+3] != 'X' && pole.plansza[i][kolumna+4] != 'X' && i<wys)
    {
        i++;
    }
    pole.plansza[i-1][kolumna] = 'X';
    pole.plansza[i-1][kolumna+1] = 'X';
    pole.plansza[i-1][kolumna+2] = 'X';
    pole.plansza[i-1][kolumna+3] = 'X';
    pole.plansza[i-1][kolumna+4] = 'X';
    pole.plansza[i-2][kolumna] = 'X';
    pole.plansza[i-2][kolumna+2] = 'X';
    pole.plansza[i-2][kolumna+4] = 'X';
    pole.plansza[i-3][kolumna] = 'X';
    pole.plansza[i-3][kolumna+2] = 'X';
    pole.plansza[i-3][kolumna+4] = 'X';
    return pole;
}
struct gra Bomba(int kolumna,struct gra pole,int wys)
{
    int i=0;
    while(pole.plansza[i][kolumna] != 'X' && i<wys)
    {
        i++;
    }
    pole.plansza[i-1][kolumna] = '.';
    pole.plansza[i-1][kolumna-1] = '.';
    pole.plansza[i-1][kolumna+1] = '.';
    pole.plansza[i-2][kolumna] = '.';
    pole.plansza[i-2][kolumna-1] = '.';
    pole.plansza[i-2][kolumna+1] = '.';
    pole.plansza[i][kolumna] = '.';
    pole.plansza[i][kolumna-1] = '.';
    pole.plansza[i][kolumna+1] = '.';
    return pole;
}
struct gra RysowanieFigury(char c,int kolumna,struct gra pole,int wys)
{
    if(c == 'K')
        pole=TypK(kolumna,pole,wys);
    if(c == 'T')
        pole=TypT(kolumna,pole,wys);
    if(c == 'I')
        pole=TypI(kolumna,pole,wys);
    if(c == 'F')
        pole=TypF(kolumna,pole,wys);
    if(c == 'W')
        pole=TypW(kolumna,pole,wys);
    if(c == '*')
        pole=Bomba(kolumna,pole,wys);
    return pole;
}
struct gra Przesuniecie(struct gra pole,int szer, int miejsce)
{
    while(miejsce-1 >= 0)
    {
        for(int i=0;i<szer;i++)
            pole.plansza[miejsce][i]=pole.plansza[miejsce-1][i];
        miejsce-=1;
    }
    for(int i=0;i<szer;i++)
        pole.plansza[0][i]='.';
    return pole;
}
struct gra SprawdzanieLinii(struct gra pole,int wys,int szer)
{
    int licznik=0;
    for(int i=wys-1;i>=0;i--)
    {
        for(int j=szer-1;j>=0;j--)
        {
            if(pole.plansza[i][j] == 'X')
                licznik++;
        }
        if(licznik == szer)
        {
            pole=Przesuniecie(pole,szer,i);
            SprawdzanieLinii(pole,wys,szer);
        }
        licznik=0;
    }
    return pole;
}
void Wypisz(struct gra pole,int wys,int szer)
{
    for(int i=0;i<wys;i++)
    {
        for(int j=0;j<szer;j++)
            putchar(pole.plansza[i][j]);
        putchar('\n');
    }
}
int main()
{
    int szer=0,wys=0,t=0,kolumna=0;
    char c,tab[10];
    scanf("%d%d%d",&szer,&wys,&t);
    for(int i=0;i<wys;i++)
        for(int j=0;j<szer;j++)
            pole.plansza[i][j]='.';
    for(int i=0;i<=t;i++)
    {
        fgets(tab,10,stdin);
        sscanf(tab,"%c %d",&c,&kolumna);
        if(kolumna<=szer)
        {
            pole=RysowanieFigury(c,kolumna,pole,wys);
            pole=SprawdzanieLinii(pole,wys,szer);
        }
    }
    pole=SprawdzanieLinii(pole,wys,szer);
    Wypisz(pole,wys,szer);
}
