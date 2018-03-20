#include <stdio.h>
#include <limits.h>
typedef unsigned int Czas;
struct brydzysta{
Czas poczatek;
Czas koniec;
Czas id_osoba;
};
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
void Sortowanie(Czas poczatek, Czas koniec ,struct brydzysta brydzysci[],struct brydzysta pomocnicza[])
{
	if (poczatek==koniec)
		return;
	Czas srodek = (poczatek + koniec) / 2;
	Sortowanie(poczatek, srodek,brydzysci,pomocnicza);
	Sortowanie(srodek+1, koniec,brydzysci,pomocnicza);
	Czas i = poczatek,j = srodek+1,k;
	for (k = poczatek; k <= koniec; k++)
		if (j>koniec || ( i<=srodek && brydzysci[i].poczatek < brydzysci[j].poczatek ) )
		{
			pomocnicza[k] = brydzysci[i];
			i++;
		}
		else
		{
			pomocnicza[k] = brydzysci[j];
			j++;
		}
	for(k = poczatek ; k <= koniec; k++)
	{
		brydzysci[k] = pomocnicza[k];
	}
}


Czas czas_p = 0,czas_k = 0;
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
    czas_p &= 15;
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

Czas max_in_four(Czas a,Czas b,Czas c,Czas d){
	if(a>b && a>c && a>d)return a;
	if(b>c && b>d)return b;
	if(c>d)return c;
	return d;
}
Czas min_in_four(Czas a,Czas b,Czas c,Czas d){
	if(a<b && a<c && a<d)return a;
	if(b<c && b<d)return b;
	if(c<d)return c;
	return d;
}
int main()
{
    Czas miesiac_p,dzien_p,godzina_p,minuty_p,sekundy_p;
    Czas miesiac_k,dzien_k,godzina_k,minuty_k,sekundy_k;
    int ilosc;
    char czas_pocz[20],czas_konc[20],gra[5];
    fgets(gra,5,stdin);
    sscanf(gra,"%d",&ilosc);
    struct brydzysta brydzysci[ilosc],pomocnicza[ilosc];
    for(int i=0;i<ilosc;i++)
    {
        fgets(czas_pocz,20,stdin);
        sscanf(czas_pocz,"%u %u %u %u %u",&miesiac_p,&dzien_p,&godzina_p,&minuty_p,&sekundy_p);
        fgets(czas_konc,20,stdin);
        sscanf(czas_konc,"%u %u %u %u %u",&miesiac_k,&dzien_k,&godzina_k,&minuty_k,&sekundy_k);
        czas_p = TworzenieRep(sekundy_p,minuty_p,godzina_p,dzien_p,miesiac_p);
        czas_k = TworzenieRep(sekundy_k,minuty_k,godzina_k,dzien_k,miesiac_k);
        brydzysci[i].id_osoba=i;
        brydzysci[i].poczatek=czas_p;
        brydzysci[i].koniec=czas_k;
    }
    Sortowanie(0,ilosc-1,brydzysci,pomocnicza);
    Czas najprzed=0,koniec,pocz;
    Czas tab[4],start,meta;
    int i,j,k,l;
    for(i=0;i<ilosc-3;i++)
    {
    	for(j=i+1;j<ilosc-2;j++)
    	{
    		if(brydzysci[i].koniec<brydzysci[j].poczatek)break;
    		for(k=j+1;k<ilosc-1;k++)
    		{
    			if(brydzysci[i].koniec<brydzysci[k].poczatek)break;
    			if(brydzysci[j].koniec<brydzysci[k].poczatek)break;
    			for(l=k+1;l<ilosc;l++)
    			{
    				if(brydzysci[i].koniec<brydzysci[l].poczatek)break;
    				if(brydzysci[j].koniec<brydzysci[l].poczatek)break;
    				if(brydzysci[k].koniec<brydzysci[l].poczatek)break;
    				start=max_in_four(brydzysci[i].poczatek,brydzysci[j].poczatek,brydzysci[k].poczatek,brydzysci[l].poczatek);
    				meta=min_in_four(brydzysci[i].koniec,brydzysci[j].koniec,brydzysci[k].koniec,brydzysci[l].koniec);
    				if(meta-start>najprzed){
    					najprzed=meta-start;
    					tab[0]=brydzysci[i].id_osoba;
    					tab[1]=brydzysci[j].id_osoba;
    					tab[2]=brydzysci[k].id_osoba;
    					tab[3]=brydzysci[l].id_osoba;
    					pocz=start;
    					koniec=meta;
    				}

    			}
    		}
    	}
    }

    if(najprzed == 0)
        printf("NOT FOUND!");
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
