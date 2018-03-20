#include <stdio.h>
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
    int x[n*m+1],y[n*m+1],start=0,koniec=0,max=0;
    int wynik[n][m];
    int i,j;
    for(i=0;i<n;i++)
        {
            fgets(dane,101,stdin);
            for(j=0;j<m;j++)
            {
                pole[i][j] = dane[j];
            }
        }
    int xa=-1,ya=-1;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(pole[i][j] == '!')
            {
                xa = j;
                ya = i;
            }
    if(xa!=-1 && ya!=-1)
        {
        x[start]=xa;
        y[start]=ya;
        koniec++;
        wynik[ya][xa]=0;
        while(start<koniec)
            {
                xa=x[start];
                ya=y[start];
                if(wynik[ya][xa]>max)
                    max=wynik[ya][xa];
                pole[ya][xa]='#';
                if(xa>0 && pole[ya][xa-1]=='-')
                {
                    x[koniec]=xa-1;
                    y[koniec]=ya;
                    koniec++;
                    pole[ya][xa-1]='#';
                    wynik[ya][xa-1]=wynik[ya][xa]+1;
                }
                if(xa<m-1 && pole[ya][xa+1]=='-')
                {
                    x[koniec]=xa+1;
                    y[koniec]=ya;
                    koniec++;
                    pole[ya][xa+1]='#';
                    wynik[ya][xa+1]=wynik[ya][xa]+1;
                }
                if(ya>0 && pole[ya-1][xa]=='-')
                {
                    x[koniec]=xa;
                    y[koniec]=ya-1;
                    koniec++;
                    pole[ya-1][xa]='#';
                    wynik[ya-1][xa]=wynik[ya][xa]+1;
                }
                if(ya<n-1 && pole[ya+1][xa]=='-')
                {
                    x[koniec]=xa;
                    y[koniec]=ya+1;
                    koniec++;
                    pole[ya+1][xa]='#';
                    wynik[ya+1][xa]=wynik[ya][xa]+1;
                }
                start++;
        }
	}
    int wynik2 = Sprawdzenie(n,m,pole);
    if(wynik2 == 0)
        printf("%d",max);
    else printf("%d",wynik2);
}
