// Dawid Paluszak Zadanie 2
#include <stdio.h>
void DrawElip(int x0, int y0, int r);
void DrawRect(int x0, int y0, int w , int h,char pole[2001]);
void DrawTria(int x0, int y0, int r);
void DrawTree(int x0, int y0, int h);
int main()
{
    int x0,y0,r,w=0,h=0;
    char tablica[501],znak[1],pole[2001] = {' '};
    for(int i=80;i<2001;i+=80)
        pole[i]='\n';
    fgets(tablica,501,stdin);
    while(tablica[0] != 'q')
    {
        sscanf(tablica,"%s %d %d %d %d",znak,&x0,&y0,&w,&h);
        if(znak[0] == 'c')
        {
            r=w;
            DrawElip(x0,y0,r);
        }
        if(znak[0] == 'r')
        {
            DrawRect(x0,y0,w,h,pole);
        }
        if(znak[0] == 't')
        {
            r=w;
            DrawTria(x0,y0,r);
        }
        if(znak[0] == 'x')
        {
            h=w;
            DrawTree(x0,y0,h);
        }
        if(znak[0] == 'p')
        {
            for(int i=0;i<2001;i++)
                putchar(pole[i]);
        }
        if(znak[0] == 'm')
        {
            int licznik=80;
            char pole_pomocnicze[2001];
            for(int i=1921;i>=0;i-=80)
                if(i==1921)
                    for(int j=0;j<81;j++)
                        pole_pomocnicze[j]=(pole[i+j]);
                else
                    for(int j=1;j<=81;j++)
                    {
                        pole_pomocnicze[j+licznik]=(pole[i+j]);
                        licznik+=80;
                    }
            for(int i=0;i<2001;i++)
                pole[i]=pole_pomocnicze[i];

        }
        if(znak[0] == 'z')
        {
            for(int i=0;i<2001;i++)
                pole[i]=' ';
        }
        fgets(tablica,501,stdin);
    }
}
void DrawElip(int x0,int y0, int r)
{
    int i,j,x,y;
    for(i=0;i<x0+r+1;i++)
    {
        for(j=0;j<y0+r+1;j++)
        {
            x = i - x0;
            y = j - y0;
            if(((x*x)+(y*y)) <= r*r)
                putchar('X');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}
void DrawRect(int x0,int y0,int w, int h, char pole[2001])
{
    int i,j;
    h=80*h;
    y0=y0*80+1;
    for(i=y0;i<h;i+=80)
    {
        if(i==0)
            for(j=0;j<w;j++)
            {
                pole[i+j+x0-1]='X';
            }
        else
            for(j=0;j<w;j++)
            {
                pole[i+j+x0]='X';
            }
        putchar('\n');
    }
}
void DrawTria(int x0,int y0,int r)
{
    int i,j;
    for(i=0;i<y0;i++)
    {
        for(j=0;j<r+x0;j++)
            putchar(' ');
        putchar('\n');
    }
    for(i=0;i<(r/2)+1;i++)
    {
        for(j=r-i;j<x0+r;j++)
        {

            putchar(' ');
        }
        for(j=i*2;j<r;j++)
        {
            putchar('X');
        }
        putchar('\n');
    }
}
void DrawTree(int x0,int y0,int h)
{
    int i,j;
    for(i=0;i<y0;i++)
    {
        for(j=0;j<x0;j++)
            putchar(' ');
        putchar('\n');
    }
    for(i=0;i<h-1;i++)
    {
        for(j=i;j<=h-3+x0;j++)
            putchar(' ');
        for(j=h-i*2;j<=h;j++)
            putchar('X');
        putchar('\n');
    }
    //rysowanie pnia
    if(h == 2 || h == 3)
    {
        for(j=0;j<h-2;j++)
        {
            putchar(' ');
        }
        putchar('|');
        putchar('\n');
    }
    else
    {
        for(i=0;i<h/4;i++)
        {
            for(j=0;j<h-2+x0;j++)
            {
                putchar(' ');
            }
            putchar('|');
            putchar('\n');
        }
    }
}
