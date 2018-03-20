#include <stdio.h>
#include <limits.h>
typedef unsigned int Czas;
Czas czas_p = 0,czas_k = 0;
void swap(unsigned int *a,unsigned int *b){
    int c = *a;
    *a = *b;
    *b = c;
}
void Qsort(unsigned int *tab, int lewa, int prawa)
{
	int p = (lewa + prawa) / 2, i, j;
	swap(&tab[p], &tab[prawa]);
	for(i = j = lewa; i < prawa; i++)
		if(tab[i] < tab[prawa])
		{
			swap(&tab[i], &tab[j]);
			j++;
		}
	swap(&tab[j], &tab[prawa]);
	if( lewa < j - 1 ) Qsort(tab, lewa, j -1);
	if( j + 1 < prawa) Qsort(tab, j + 1, prawa);
}
Czas Sekundy(Czas czas_p,Czas s)
{
    czas_p = czas_p << 6;
    czas_p |= s;
    return czas_p;
}
Czas Minuty(Czas czas_p,Czas m)
{
    czas_p = czas_p << 6;
    czas_p |= m;
    return czas_p;
}
Czas Godziny(Czas czas_p,Czas g)
{
    czas_p = czas_p << 5;
    czas_p |= g;
    return czas_p;
}
Czas Dzien(Czas czas_p,Czas d)
{
    czas_p = czas_p << 5;
    czas_p |= d;
    return czas_p;
}
Czas Miesiac(Czas czas_p,Czas ms)
{
    czas_p = czas_p << 4;
    czas_p |=ms;
    return czas_p;
}
Czas SekundyWDS(Czas czas_p)
{
    czas_p &= 63;
    return czas_p;
}
Czas MinutyWDS(Czas czas_p)
{
    czas_p = czas_p >> 6;
    czas_p &= 63;
    return czas_p;
}
Czas GodzinyWDS(Czas czas_p)
{
    czas_p = czas_p >> 12;
    czas_p &= 31;
    return czas_p;
}
Czas DzienWDS(Czas czas_p)
{
    czas_p = czas_p >> 17;
    czas_p &= 31;
    return czas_p;
}
Czas MiesiacWDS(Czas czas_p)
{
    czas_p = czas_p >> 22;
    czas_p &= 7;
    return czas_p;
}
Czas TworzenieRep(Czas s,Czas m,Czas g,Czas d,Czas ms)
{
    Czas c = 0;
    c = Miesiac(c,ms);
    c = Dzien(c,d);
    c = Godziny(c,g);
    c = Minuty(c,m);
    c = Sekundy(c,s);
    return c;
}
void TworzenieDaty(Czas rep)
{
    Czas mie = MiesiacWDS(rep);
    Czas dz = DzienWDS(rep);
    Czas go = GodzinyWDS(rep);
    Czas mi = MinutyWDS(rep);
    Czas se = SekundyWDS(rep);
    printf("%u %u %u %u %u \n",mie,dz,go,mi,se);
}
int main()
{
    Czas miesiac_p,dzien_p,godzina_p,minuty_p,sekundy_p;
    Czas miesiac_k,dzien_k,godzina_k,minuty_k,sekundy_k;
    int ilosc;
    char czas_pocz[20],czas_konc[20],gra[5];
    fgets(gra,5,stdin);
    sscanf(gra,"%d",&ilosc);
    Czas pocz_gry[ilosc],koniec_gry[ilosc],pocz_gry2[ilosc];
    for(int i=0;i<ilosc;i++)
    {
        fgets(czas_pocz,20,stdin);
        sscanf(czas_pocz,"%u %u %u %u %u",&miesiac_p,&dzien_p,&godzina_p,&minuty_p,&sekundy_p);
        fgets(czas_konc,20,stdin);
        sscanf(czas_konc,"%u %u %u %u %u",&miesiac_k,&dzien_k,&godzina_k,&minuty_k,&sekundy_k);
        czas_p = TworzenieRep(sekundy_p,minuty_p,godzina_p,dzien_p,miesiac_p);
        czas_k = TworzenieRep(sekundy_k,minuty_k,godzina_k,dzien_k,miesiac_k);
        pocz_gry[i] = czas_p;
        koniec_gry[i] = czas_k;
        pocz_gry2[i] = czas_p;
    }
    Qsort(pocz_gry,0,ilosc - 1);
    Qsort(koniec_gry,0,ilosc - 1);
    Czas najprzed=UINT_MAX,koniec,pocz;
    unsigned int tab[4];
    for(int i=ilosc;i>2;i--)
    {
        if(pocz_gry[i-1]<koniec_gry[i-4])
        {
            if(najprzed>koniec_gry[i-4] - pocz_gry[i-1])
            {
                koniec = koniec_gry[i-4];
                pocz = pocz_gry[i-1];
                for(int j=0;j<ilosc;j++)
                {
                    if(pocz_gry2[j]==pocz_gry[i-4])
                        tab[0]=j;
                    if(pocz_gry2[j]==pocz_gry[i-3])
                        tab[1]=j;
                    if(pocz_gry2[j]==pocz_gry[i-2])
                        tab[2]=j;
                    if(pocz_gry2[j]==pocz_gry[i-1])
                        tab[3]=j;
                }
                najprzed = koniec_gry[i-4] - pocz_gry[i-1];
            }
        }
    }
    if(najprzed == UINT_MAX)
        printf("NOT FOUND");
    else
    {
        printf("%u ",najprzed);
        Qsort(tab,0,4);
        for(int i=3;i>=0;i--)
            printf("%d ",tab[i]);
        printf("\n%u: ",pocz);
        TworzenieDaty(pocz);
        printf("%u: ",koniec);
        TworzenieDaty(koniec);
    }
}
