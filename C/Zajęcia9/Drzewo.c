#include <stdio.h>
#include <stdlib.h>

typedef struct Drzewo{
    int val;
    int gle;
    struct Drzewo *rodzic;
    struct Drzewo *galaz[10];
}tree;
//tree *mam=NULL;
tree *SzukanieGalezi(tree *root,int jaka)
{
    /*if(mam == NULL)
        {
            for(int i=0;i<10;i++)
            {
                if(root->galaz[i]!=NULL)
                    if(root->galaz[i]->val==jaka)
                        {
                            mam = root->galaz[i];
                            return mam;
                        }
            }
            for(int i=0;i<10;i++)
            {
                if(mam!=NULL)
                SzukanieGalezi(root->galaz[i],jaka);
            }

        }
        return mam;
*/
    for(int i=0;i<10;i++)
    {
        if(root->galaz[i]->val==jaka)
            return root->galaz[i];
    }
    printf("znalazlo %d a szukam %d\n",root->val, jaka);
    return root;
}


void Dodawanie(tree *root,int co,int gdzie)
{
    tree *wsk=root,*nowy;
    if(gdzie != root->val)
        wsk = SzukanieGalezi(root,gdzie);
    //printf("%d ",wsk->val);
    int i=0;
    while(wsk->galaz[i]!=NULL)
    {
        i++;
    }
    nowy=malloc(sizeof(tree));
    nowy->gle = (wsk->gle)+1;
    nowy->val = co;
    nowy->rodzic = wsk;
    //printf("%d",nowy->gle);
    wsk->galaz[i]=nowy;
    for(int i=0;i<10;i++)
        nowy->galaz[i] = NULL;
}

void Zmiana(tree *root)
{
    for(int i=0;i<10;i++)
        if(root->galaz[i] != NULL)
    {
        root->galaz[i]->gle = (root->gle)++;
        Zmiana(root->galaz[i]);
    }
}

void Przenoszenie(tree *root,int co,int gdzie)
{
    tree *wsk,*wsk2;
    wsk = SzukanieGalezi(root,gdzie);
    wsk2 = SzukanieGalezi(root,co);
    //printf("%d %d",wsk->val,wsk2->val);
    int i=0;
    while(wsk->galaz[i]!=NULL)
        i++;
    wsk->galaz[i]=wsk2;
    tree *parent = wsk2->rodzic;
    for(int i=0;i<10;i++)
        if(parent->galaz[i]->val == co)
            parent->galaz[i]=NULL;
    wsk2->rodzic = wsk;
    wsk2->gle=(wsk->gle)+1;
    Zmiana(wsk2);
}
int gle;
void Szukanie(tree *root)
{
     //while(root->galaz[0] != NULL || root->galaz[1] != NULL || root->galaz[2] != NULL || root->galaz[3] != NULL || root->galaz[4] != NULL || root->galaz[5] != NULL || root->galaz[6] != NULL || root->galaz[7] != NULL || root->galaz[8] != NULL || root->galaz[9] != NULL )

        if(gle == 0)
        {
            for(int i=0;i<10;i++)
            {
                if(root->galaz[i]!=NULL)
                    if(root->galaz[i]->val==2)
                        {
                            gle = root->galaz[i]->gle;
                            return;
                        }
            }
            for(int i=0;i<10;i++)
                Szukanie(root->galaz[i]);
        }
        return;
}

int main()
{
    tree *root;
    root=malloc(sizeof(tree));
    root->val = 1;
    root->gle = 1;
    root->rodzic = NULL;
    for(int i=0;i<10;i++)
        root->galaz[i]=NULL;
    char in[100],znak;
    int gdzie,co;
    int n;
    fgets(in,100,stdin);
    sscanf(in,"%d",&n);
    for(int i=0;i<n;i++)
    {
        fgets(in,100,stdin);
        sscanf(in,"%c %d %d",&znak,&co,&gdzie);
        if(znak=='d')
            Dodawanie(root,co,gdzie);
        if(znak=='p')
            Przenoszenie(root,co,gdzie);
    }
    Szukanie(root);
    //printf("%d",gle);
    printf("%d",root->galaz[0]->gle);
}

