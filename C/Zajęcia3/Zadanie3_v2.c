#include <stdio.h>
#include <stdbool.h>
int main()
{
    int i,j,k,ilosc_przystankow,czas_przejazdu[21],liczba_odjazdow[201];
    int godziny,minuty,czas[21][201],min_przejazd,czas_start,nastepny;
    int przejazd;
    scanf("%d",&ilosc_przystankow);
    for(i=0;i<ilosc_przystankow;i++)
    {
        scanf("%d%d",&czas_przejazdu[i],&liczba_odjazdow[i]);
        for(j=0;j<liczba_odjazdow[i];j++)
        {
            scanf("%d%d",&godziny,&minuty);
                czas[i][j]=godziny*60+minuty;
        }
    }
    bool przesiadka;
    for(i=0;i<liczba_odjazdow[0];i++)
    {
    	// Zaczynamy z czasem 1 przystanku
    	nastepny=czas[0][i]+czas_przejazdu[0];
    	nastepny%=1440;
    	przejazd=czas_przejazdu[0];
    	for(j=1;j<ilosc_przystankow;j++)
    	{
    		// lecimy od nastepnego do ostatniego przystanku
    		przesiadka=false;
    		for(k=0;k<liczba_odjazdow[j];k++)
    		{
    			if(czas[j][k]>=nastepny){
    				// jezeli znalezlismy pierwszy na kolejnej stacji to stopujemy
    				przesiadka=true;
    				break;
    			}
    		}
    		if(przesiadka)
    		{
    			// jezeli byl taki zeby do neigo wsiasc dodajemy roznice czasu podrozy i czas na przejazd do nastepnego
    			przejazd=przejazd+(czas[j][k]+czas_przejazdu[j])-nastepny;
    			nastepny=czas[j][k]+czas_przejazdu[j];
    			nastepny%=1440;
    		}else
    		{
    			// jezeli nie bylo takiego to wsiadamy do 1 z nastepnego dnia
    			// dodajemy do czasu roznice do polnocy i dodajemy czas przejazdu do nastepnego
    			przejazd=przejazd+(24*60)-nastepny+czas[j][0]+czas_przejazdu[j];
    			nastepny=czas[j][0]+czas_przejazdu[j];
    			nastepny%=1440;
    		}

    	}
    	if(i==0){
    		// wiadomo ze pierwsza mozliwosc jest minimalna na poczatek
    		min_przejazd=przejazd;
    		czas_start=czas[0][i];
    	}else
    	if(przejazd<min_przejazd){
    		// to ty chyba wiesz xD
    		min_przejazd=przejazd;
    		czas_start=czas[0][i];
    	}

    }

    printf("%d %d %d %d",czas_start/60,czas_start%60,min_przejazd/60,min_przejazd%60);
}
