//Dawid Paluszak Zadanie 2
#include <stdio.h>
typedef unsigned short TypDaty;
char *DniTyg[] = {"pon","wto","sro","czw","pia","sob","nie"};
int DzienMiesiaca[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *Miesiac[] = {"sty","lut","mar","kwi","maj","cze","lip","sie","wrz","paz","lis","gru"};
char *Rok[] = {"malpy","koguta","swini","szczura","tygrysa","krolika","smoka","weza","konia","owcy","kozy","psa"};
// zamiana reprezentacji na poszczegolne liczby
TypDaty CzytanieDniTygodnia(TypDaty data)
{
    data &= 7;
    return data;
}
TypDaty CzytanieDniMiesiaca(TypDaty data)
{
    data = data >> 3;
    data &= 31;
    return data;
}
TypDaty CzytanieMiesiaca(TypDaty data)
{
    data = data >> 8;
    data &= 15;
    return data;
}
TypDaty CzytanieRoku(TypDaty data)
{
    data = data >> 12;
    data &= 15;
    return data;
}
//zamiana liczb na reprezentacje
TypDaty DataDzienTyg(TypDaty data, short dt)
{
    data = data << 3;
    data |= dt;
    return data;
}
TypDaty DataDzienMiesiaca(TypDaty data, short d)
{
    data = data << 5;
    data |= d;
    return data;
}
TypDaty DataMiesiac(TypDaty data, short m)
{
    data = data << 4;
    data |= m;
    return data;
}
TypDaty DataRok(TypDaty data, short rok)
{
    data |= rok;
    return data;
}
//sprawdzanie bledu
TypDaty BladDaty(TypDaty data)
{
    int dzienTyg = CzytanieDniTygodnia(data);
    int dzienMie = CzytanieDniMiesiaca(data);
    int mie = CzytanieMiesiaca(data);
    int r = CzytanieRoku(data);
    if(dzienTyg < 1 || dzienTyg > 7) return 1;
    if(dzienMie < 1 || dzienMie > DzienMiesiaca[mie - 1])  return 1;
    if(mie < 1 || mie > 12) return 1;
    if(r < 1 || r > 12) return 1;
    return 0;
}
//funckja tworzoca reprezentacje
TypDaty ZrobDate(short dt,short d, short m, short rok)
{
    TypDaty data = 0;
    data = DataRok(data, rok);
    data = DataMiesiac(data, m);
    data = DataDzienMiesiaca(data, d);
    data = DataDzienTyg(data, dt);
    return data;
}
//funkcja liczaca ile dni nalezy dodac zaleznie od miesiaca do odleglosci
int KtoryMiesiac(int mie)
{
    if(mie == 1) return 0;
    if(mie == 2) return 31;
    if(mie == 3) return 59;
    if(mie == 4) return 90;
    if(mie == 5) return 120;
    if(mie == 6) return 151;
    if(mie == 7) return 182;
    if(mie == 8) return 212;
    if(mie == 9) return 243;
    if(mie == 10) return 273;
    if(mie == 11) return 304;
    if(mie == 12) return 334;
    return 0;
}
//funkcja liczaca odleglosc
int Odleglosc(TypDaty d1,TypDaty d2)
{
    int ilosc_dni_pierwsza=0,ilosc_dni_druga=0;
    int mie1 = CzytanieMiesiaca(d1);
    int mie2 = CzytanieMiesiaca(d2);
    ilosc_dni_pierwsza = CzytanieDniMiesiaca(d1);
    ilosc_dni_pierwsza += KtoryMiesiac(mie1);
    ilosc_dni_pierwsza += ((CzytanieRoku(d1)*365)-365);
    ilosc_dni_druga = CzytanieDniMiesiaca(d2);
    ilosc_dni_druga += KtoryMiesiac(mie2);
    ilosc_dni_druga += ((CzytanieRoku(d2)*365)-365);
    int wynik = ilosc_dni_druga - ilosc_dni_pierwsza;
    if(wynik<0) return wynik * -1;
    return wynik;
}
//funkcja wypisujaca
void WypiszDate(TypDaty d1,TypDaty d2)
{
    int dzienTyg = CzytanieDniTygodnia(d1);
    int dzienMie = CzytanieDniMiesiaca(d1);
    int mie = CzytanieMiesiaca(d1);
    int r = CzytanieRoku(d1);
    printf("Data Pierwsza - %hu : %s, %d %s, rok %s(%d)\n",d1,DniTyg[dzienTyg - 1],dzienMie,Miesiac[mie - 1],Rok[r - 1],r);
    dzienTyg = CzytanieDniTygodnia(d2);
    dzienMie = CzytanieDniMiesiaca(d2);
    mie = CzytanieMiesiaca(d2);
    r = CzytanieRoku(d2);
    printf("Data Druga - %hu : %s, %d %s, rok %s(%d)\n",d2,DniTyg[dzienTyg - 1],dzienMie,Miesiac[mie - 1],Rok[r - 1],r);
    printf("Odleglosc : %d dni\n",Odleglosc(d1, d2));
}
int main()
{
    TypDaty data_pierwsza,data_druga;
    char Data1[20],Data2[20];
    int dt1=1,d1=1,m1=1,r1=1,dt2=1,d2=1,m2=1,r2=1;
    while(dt1!=0 || dt2!=0)
    {
        fgets(Data1,20,stdin);
        sscanf(Data1,"%d %d %d %d",&r1,&m1,&d1,&dt1);
        fgets(Data2,20,stdin);
        sscanf(Data2,"%d %d %d %d",&r2,&m2,&d2,&dt2);
        if(dt1 == 0 || dt2 == 0) break;
        data_pierwsza = ZrobDate(dt1,d1,m1,r1);
        data_druga = ZrobDate(dt2,d2,m2,r2);
        //wypisanie bledow
        if(BladDaty(data_pierwsza) != 0)
        {
            printf("Pola niepoprawne w dacie pierwszej: ");
            if(dt1 < 1 || dt1 > 7)
                printf("dzienTygodnia ");
            if(d1 < 1 || d1 > DzienMiesiaca[m1 - 1])
                printf("dzienMiesiaca ");
            if(m1 < 1 || m1 > 12)
                printf("miesiac ");
            if(r1 < 1 || r1 > 12)
                printf("rok");
            printf("\n");
            if(BladDaty(data_druga) != 0)
                {
                    printf("Pola niepoprawne w dacie drugiej: ");
                    if(dt2 < 1 || dt2 > 7)
                        printf("dzienTygodnia ");
                    if(d2 < 1 || d2 > DzienMiesiaca[m2 - 1])
                        printf("dzienMiesiaca ");
                    if(m2 < 1 || m2 > 12)
                        printf("miesiac ");
                    if(r2 < 1 || r2 > 12)
                        printf("rok");
                    printf("\n");
                    continue;
                }
            continue;
        }
        if(BladDaty(data_druga) != 0)
        {
            printf("Pola niepoprawne w dacie drugiej: ");
            if(dt2 < 1 || dt2 > 7)
                printf("dzienTygodnia ");
            if(d2 < 1 || d2 > DzienMiesiaca[m2 - 1])
                printf("dzienMiesiaca ");
            if(m2 < 1 || m2 > 12)
                printf("miesiac ");
            if(r2 < 1 || r2 > 12)
                printf("rok");
            printf("\n");
            continue;
        }
        else
        {
            WypiszDate(data_pierwsza,data_druga);
        }
    }
}
