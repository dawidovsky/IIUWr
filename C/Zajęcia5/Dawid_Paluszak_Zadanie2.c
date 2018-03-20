//Dawid_Paluszak_Zadanie2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct samochody
{
    char producent[101];
    char model[101];
    int rok[5];
    int pojemnosc[100];
};
int SortowanieRok(const void * a,const void * b)
{
    if(*(int*)a > *(int*)b) return 1;
    if(*(int*)a == *(int*)b) return 0;
    else return -1;
}
int SortowanieProMod(const void * a, const void *b)
{
    return strcmp((char*)a,(char*)b);
}
int main(int argc, char *argv[])
{
    int i=0;
    struct samochody auta[1001];
    if(argc>1)
    {
        FILE *f = fopen(argv[1],"r");
        while(!feof(f))
        {
            fgets(auta[i].producent,101,f);
            fgets(auta[i].model,101,f);
            fscanf(f,"%d",auta[i].rok);
            fscanf(f,"%d",auta[i].pojemnosc);
            i++;
        }
        if(*argv[2]=='r') qsort((*auta).rok,5,sizeof(*auta),SortowanieRok);
        if(*argv[2]=='p') qsort((*auta).producent,101,sizeof(*auta),SortowanieProMod);
        if(*argv[2]=='m') qsort((*auta).model,101,sizeof(*auta),SortowanieProMod);
        fclose(f);
    }
    while(i>=0)
    {
        printf("%s %s %d %d\n",auta[i].producent,auta[i].model,auta[i].rok,auta[i].pojemnosc);
        i--;
    }

}
