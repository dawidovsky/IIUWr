// Dawid Paluszak Zadanie 1
#include <stdio.h>
void DrawElip(int x0, int y0, int r);
void DrawRect(int x0, int y0, int w , int h);
int main()
{
    int x0,y0,r,w=0,h=0;
    char tablica[501],znak[1];
    printf("Witamy w programie\n");
    x0 = 4;
    y0 = 5;
    r = 4;
    DrawElip(x0,y0,r);
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
            DrawRect(x0,y0,w,h);
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
                putchar('.');
        }
        putchar('\n');
    }
}
void DrawRect(int x0,int y0,int w, int h)
{
    int i,j;
    for(i=0;i<y0;i++)
    {
        for(j=0;j<w+x0;j++)
            putchar('.');
        putchar('\n');
    }
    for(i=0;i<h;i++)
    {
        for(j=0;j<x0;j++)
        {
            putchar('.');
        }
        for(j=0;j<w;j++)
        {
            putchar('X');
        }
        putchar('\n');
    }
}
