#include <stdio.h>
#include <stdbool.h>

int main()
{
    bool tab[101][101];
    char in[100],znak;
    int gdzie,co,n;
    for(int i=0;i<101;i++)
        for(int j=0;j<101;j++)
            tab[i][j]=false;
    tab[1][0]=true;
    fgets(in,100,stdin);
    sscanf(in,"%d",&n);
    for(int i=0;i<n;i++)
    {
        fgets(in,100,stdin);
        sscanf(in,"%c %d %d",&znak,&co,&gdzie);
        if(znak=='d')
            tab[co][gdzie]=true;
        if(znak=='p')
        {
            for(int i=0;i<101;i++)
                tab[co][i]=false;
            tab[co][gdzie]=true;
        }
    }
    int licznik=1,zmienna=2;
    while(zmienna != 1)
    {
        for(int i=0;i<101;i++)
            if(tab[zmienna][i]==true)
            {
                zmienna = i;
                break;
            }
        licznik++;
    }
    printf("%d",licznik);
}
