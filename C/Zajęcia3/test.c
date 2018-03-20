#include <stdio.h>
int main()
{
    int wysokosc,i,j;
    scanf("%d",&wysokosc);
    for(i=0;i<wysokosc-1;i++)
    {
        for(j=i;j<=wysokosc-3;j++)
            putchar(' ');
        for(j=wysokosc-i*2;j<=wysokosc;j++)
            putchar('X');
        putchar('\n');
    }
    if(wysokosc == 2 || wysokosc == 3)
    {
        for(j=0;j<wysokosc-2;j++)
        {
            putchar(' ');
        }
        putchar('|');
    }
    else
    {
        for(i=0;i<wysokosc/4;i++)
        {
            for(j=0;j<wysokosc-2;j++)
            {
                putchar(' ');
            }
            putchar('|');
            putchar('\n');
        }
    }
}
