#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned int rep;
    int minwl=0;
    int maxwl=0;
int max=0;
int zamien1=0;
int zamien2=0;
int h1m=0;
int m1m=0;
int s1m=0;
int mi1m=0;
int dmi1m=0;
int h2m=0;
int m2m=0;
int s2m=0;
int mi2m=0;
int dmi2m=0;
int h1=0;
int h2=0;
int m1=0;
int m2=0;
int s1=0;
int s2=0;
int mi1=0;
int mi2=0;
int dmi1=0;
int dmi2=0;
rep miesiac=0; ///5
rep dmiesiac=0;///4
rep godzina=0; ///3
rep minuta=0;  ///2
rep sekunda=0; ///1
rep Zamien(char tab [16]){
rep wynik=0; /// 26 jedynek poczynaj1c od najmniej znacz1cego bitu
rep temp1=67108863;
rep temp2=67108863;
rep temp3=67108863;
rep temp4=67108863;
rep temp5=67108863;
miesiac=0; ///5
dmiesiac=0;///4
godzina=0; ///3
minuta=0;  ///2
sekunda=0; ///1
sscanf(tab,"%d %d %d %d %d",&miesiac,&dmiesiac,&godzina,&minuta,&sekunda);
temp1=temp1&sekunda;
temp2=temp2&minuta;
temp2=temp2<<6;
temp3=temp3&godzina;
temp3=temp3<<12;
temp4=temp4&dmiesiac;
temp4=temp4<<17;
temp5=temp5&miesiac;
temp5=temp5<<22;
wynik=temp1|temp2|temp3|temp4|temp5;
return wynik;
}

void Odmien(rep liczba){
int liczba2=liczba;
int zmienna=0;
rep data2=0;
data2=63;
zmienna=data2&liczba;
int sekun=zmienna;
liczba=liczba>>6;
data2=63;
zmienna=data2&liczba;
int minut=zmienna;
liczba=liczba>>6;
data2=31;
zmienna=data2&liczba;
int godz=zmienna;
liczba=liczba>>5;
data2=31;
zmienna=data2&liczba;
int dmie=zmienna;
liczba=liczba>>5;
data2=15;
zmienna=data2&liczba;
int mie=zmienna;

printf("%d: %d %d %d %d %d\n",liczba2,mie,dmie,godz,minut,sekun);

}

int main()
{
    int indeks[4];
    int n=0;
    char c;
    int roznicawl=0;
    while((c=getchar())!='\n'){
        n=n*10;
        n=n+c-'0';
    }
    int tab2 [n][2];
    int tab3 [n][2];
    int zmienne[n];
for(int i=0;i<n*2;i=i+2){
char tablica [16];
fgets(tablica,15,stdin);
rep liczba1 = Zamien(tablica);
h1=godzina;
m1=minuta;
s1=sekunda;
mi1=miesiac;
dmi1=dmiesiac;
char tablica1 [16];
fgets(tablica1,15,stdin);
rep liczba2 = Zamien(tablica1);
h2=godzina;
m2=minuta;
s2=sekunda;
mi2=miesiac;
dmi2=dmiesiac;
int roznica = liczba2-liczba1;
tab2[i/2][0]=roznica;
tab2[i/2][1]=i/2;
tab3[i/2][0]=Zamien(tablica);
tab3[i/2][1]=Zamien(tablica1);
zmienne[i/2]=i/2;
if(roznica>max){
h1m=h1;
m1m=m1;
s1m=s1;
mi1m=mi1;
dmi1m=dmi1;
h2m=h2;
m2m=m2;
s2m=s2;
mi2m=mi2;
dmi2m=dmi2;
zamien1=liczba1;
zamien2=liczba2;
max=roznica;
}

}
int zmienna3=0;
int zmienna4=0;
int zmienna5=0;
for (int j = 0; j < n; ++j)
   {
      for (int k = j + 1; k < n; ++k)
      {
         if (tab3[j][0] > tab3[k][0])
         {
            zmienna3 = tab3[j][0];
            zmienna4 = tab3[j][1];
            zmienna5 = zmienne[j];
            tab3[j][0] = tab3[k][0];
            tab3[k][0] = zmienna3;
            tab3[j][1] = tab3[k][1];
            tab3[k][1] = zmienna4;
            zmienne[j] = zmienne[k];
            zmienne[k] = zmienna5;
         }
      }
   }
for(int i=0;i<n;i++)


//

for(int a=0;a<n-3;a++){
    for(int b=a+1;b<n-2;b++){
        for(int c=b+1;c<n-1;c++){
            for(int d=c+1;d<n;d++){
                    int min=tab3[0][1];
                for(int e=1;e<4;e++){//sprawdzenie najmniejszego koncowego przedzialu
                    if(tab3[e][1]<min){
                        min=tab3[e][1];
                    }

                    int max=tab3[0][0];
                    for(int e=1;e<4;e++){//sprawdzenie najwiekszego poczatkowego przedzialu
                    if(tab3[e][0]>max){
                        max=tab3[e][0];
                    }
                    if(tab3[a][1]>=min&&tab3[b][1]>=min&&tab3[c][1]>=min&&tab3[d][1]>=min&&tab3[a][0]<=max&&tab3[b][0]<=max&&tab3[c][0]<=max&&tab3[d][0]<=max){
                         if(min-max>roznicawl){
                         roznicawl=min-max;
                         minwl=max;
                         maxwl=min;
                         indeks[0]=zmienne[a];
                         indeks[1]=zmienne[b];
                         indeks[2]=zmienne[c];
                         indeks[3]=zmienne[d];
                         }
                    }
                }
            }
        }
    }
}}
int tmp=0;
for(int i=0;i<4;i++)
     {
           for(int j=0;j<4-i;j++)
           {
                 if(indeks[j]<indeks[j+1])
                 {
                       tmp=indeks[j+1];
                       indeks[j+1]=indeks[j];
                       indeks[j]=tmp;
                 }
           }
     }

//
    if(tab2[0][0]!=0){
    printf("%d %d %d %d %d\n",roznicawl,indeks[0],indeks[1],indeks[2],indeks[3]);
    Odmien(minwl);
    Odmien(maxwl);
    }
    else{
        printf("NOT FOUND!");
    }

}

