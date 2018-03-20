#include <stdio.h>
int main()
{
    int ilosc_przystankow,czas_przejazdu[21],liczba_odjazdow[201],tablica[21][401],czas[21][201],min_przejazd=1441,przystanek=0,wynik=0,czas_pocz=0,wynik_o=0;
    scanf("%d",&ilosc_przystankow);
    for(int i=0;i<ilosc_przystankow;i++)
    {
        scanf("%d%d",&czas_przejazdu[i],&liczba_odjazdow[i]);
        for(int j=0;j<liczba_odjazdow[i]*2;j++)
        {
            scanf("%d",&tablica[i][j]);
            if(j%2==1)
            {
                czas[i][(j+1)/2]=tablica[i][j-1]*60+tablica[i][j];
            }
        }
    }
    for(int i=0;i+1<ilosc_przystankow;i++)
    {
        for(int j=1;j<=liczba_odjazdow[i];j++)
        {
            for(int k=1;k<=liczba_odjazdow[i+1];k++)
            {
                if((czas[i][j]+czas_przejazdu[i])>=1440)
                    czas_pocz=(czas[i][j]+czas_przejazdu[i])%1440;
                else
                    czas_pocz=(czas[i][j]+czas_przejazdu[i]);
                wynik=czas_pocz-czas[i+1][k];
                //printf("czas pocz %d \n Czas %d \n wynik %d \n",czas_pocz,czas[i+1][k],wynik);
                if(wynik<=0)
                {

                    wynik=wynik * -1;
                    wynik+=czas_przejazdu[i];
                    if(wynik < min_przejazd)
                    {
                         min_przejazd=wynik;
                         if(i==0)
                            przystanek=czas[i][j];
                    }
                }
            }
        }
        wynik_o+=min_przejazd;
        min_przejazd=1441;
    }
    wynik_o+=czas_przejazdu[ilosc_przystankow-1];
    int modulo=przystanek%60;
    przystanek = przystanek / 60;
    int modulo2 = wynik_o%60;
    wynik_o=wynik_o / 60;
    printf("%d %d %d %d",przystanek,modulo,wynik_o,modulo2);
}
