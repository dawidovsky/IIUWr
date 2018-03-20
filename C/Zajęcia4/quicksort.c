#include <stdio.h>
void swap(unsigned int *a,unsigned int *b){
    int c = *a;
    *a = *b;
    *b = c;
}
void Qsort(unsigned int *tab, int lewa, int prawa)
{

	int p = (lewa + prawa) / 2, i, j;
	swap(&tab[p], &tab[prawa]);
	for(i = j = lewa; i < prawa; i++)
		if(tab[i] < tab[prawa])
		{
			swap(&tab[i], &tab[j]);
			j++;
		}
	swap(&tab[j], &tab[prawa]);
	if( lewa < j - 1 ) Qsort(tab, lewa, j -1);
	if( j + 1 < prawa) Qsort(tab, j + 1, prawa);
}
int main()
{
    unsigned int tab[] = {10,2,12,13,414,2,12,31,51};
    Qsort(tab,0,9);
    for(int i=0;i<9;i++)
        printf("%u ",tab[i]);
}
