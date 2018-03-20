//Dawid Paluszak Zadanie 1
#include <stdio.h>
#include <stdlib.h>

int nalezyDoZbioru(double a , double b)
{
    if((a*a + b*b) < 4) return 1;
    return 0;
}

int Iteracja(double a, double b, double c_r, double c_u)
{
    int licznik = 0;
    double pom;
    for(int i=0;i<200;i++)
    {
        if(nalezyDoZbioru(a,b))
        {
            pom = a;
            a = a*a - b*b;
            b = pom*b + b*pom;
            a -= c_r;
            b -= c_u;
            licznik++;
        }
    }
    if(licznik == 200)
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    double a = -1.0, b = -1.0;
    double c_r = 0.1, c_u = 0.83;
    int szer = 40, wys = 25, wynik = 0;
    if(argc > 1)
    {
        szer = atof(argv[1]);
        wys = atof(argv[2]);
    }
    if(argc > 3)
    {
        c_r = atof(argv[3]);
        c_u = atof(argv[4]);
    }
    for(int i=0;i<wys;i++)
    {
        for(int j=0;j<szer;j++)
        {
            wynik = Iteracja(a,b,c_r,c_u);
            if(wynik) printf("O");
            else printf(" ");
            a +=(1/(double)(szer/2));
        }
        a = -1.0;
        printf("\n");
        b += (1/(double)(wys/2));
    }
}
