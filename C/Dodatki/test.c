//Dawid Paluszak Zadanie 7845
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int liczba1=0;
    char c,cc;
    c = '5';
    cc = '4';
    liczba1 = liczba1 + ( c-'0');
    liczba1 = liczba1 + ( (cc-'0') * 16);
    printf("%d",liczba1);
}
