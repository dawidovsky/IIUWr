//Dawid_Paluszak_Zadanie_2
#include <stdio.h>
int RysowanieSpirali(int X,int Y, int n)
{
    int x=n/2;
    int y=n/2;
    if(n%2==1)
        x++,y++;
    int krok=0;
    for(int i=1;i<n*n+1;)
    {
        int kierunek = krok % 4;
        int krok_do_wyk = krok / 2 + 1;
        for(int j=0;j<krok_do_wyk;j++,i++)
        {
            if(X==x && Y==y)
                return i;
            if(kierunek==0)
                x++;
            if(kierunek==1)
                y++;
            if(kierunek==2)
                x--;
            if(kierunek==3)
                y--;
        }
        krok++;
    }
    return 0;
}
int czy_pierwsza(int n)
{
  if(n<2)
    return 0;
  for(int i=2;i*i<=n;i++)
    if(n%i==0)
      return 0;
  return 1;
}
int main(int argc ,char **argv)
{
    int n = 15;
    if(argc > 1)
        sscanf(argv[1],"%d",&n);
    if(argc > 2)
    {
        FILE *f = fopen(argv[2],"w");
        fprintf(f,"P3\n%d %d\n255\n",n,n);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                int wynik = RysowanieSpirali(j,i,n);
                int lpierwsza = czy_pierwsza(wynik);
                if(lpierwsza) fprintf(f,"255 255 0 \t");
                else fprintf(f,"0 0 255 \t");
            }
            fprintf(f,"\n");
        }
        fclose(f);
    }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
                printf("%4d",RysowanieSpirali(j,i,n));
            printf("\n");
        }
}
