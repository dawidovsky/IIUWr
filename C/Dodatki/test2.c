#include <stdio.h>
#include <stdlib.h>
int main ( )
{
    char *c;
    int i=0;
    c[0]=getchar();
    do
    {
        i++;
    }
    while((c[i]=getchar()) != EOF);
    int liczba = atoi(c);
    printf("%d",liczba);
}
