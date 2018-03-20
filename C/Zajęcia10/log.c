#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int pot(int a,int b)
{
    if(!b) return 1;
    int pom = a;
    for(int i=0;i<b-1;i++)
        a = a*pom;
    return a;
}

void toBoolArr(bool arr[32], int d) {
	int temp = 0;
	for (int i = 31; i >= 0; i--) {
		temp = d >> i;

		if (temp & 1) {
			arr[i] = 1;
		} else {
			arr[i] = 0;
		}
	}
}

void fromBoolArr(bool arr[32], unsigned int limit,unsigned int wynik[]) {
	limit = (limit > 32) ? 32 : limit;
	for (unsigned int i = 0; i < limit; i++) {
		wynik[i]=arr[i];
	}
}

int main()
{
    unsigned int wynik[4];
    bool wart[32];
    for(int i=0;i<pot(2,5);i++)
    {
        toBoolArr(wart,i);
        fromBoolArr(wart,5,wynik);
        printf("%d%d%d%d\n",wynik[0],wynik[1],wynik[2],wynik[3]);
    }
}
