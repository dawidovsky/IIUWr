#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct PtList{
    int numer;
    float x;
    float y;
    float z;
    char nazwa[37];
    struct PtList *next;
}lista;

int main()
{
    lista *pierwszy;
    if((pierwszy = (lista*)malloc(sizeof(lista))) == NULL)
    {
        printf("123");
    }
    char liczba1[]={"50.3123123"};
    double szer = atolf(liczba1);
    printf("%lf",szer);
}
