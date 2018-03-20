#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct znaki{
    char el;
    int size;
    int wart;
    struct znaki *next;
}znak;

int pot(int a,int b)
{
    if(!b) return 1;
    int pom = a;
    for(int i=0;i<b-1;i++)
        a = a*pom;
    return a;
}

int implikacja(int p,int q)
{
    if(p == 0)
        return 1;
    else
        if(q == 1)return 1;
    return 0;
}

int koniunkcja(int p,int q)
{
    if(p == 1 && q == 1)
        return 1;
    else return 0;
}

int alternatywa(int p,int q)
{
    if (p == 1 || q == 1)
        return 1;
    else return 0;
}

int rownowaznosc(int p,int q)
{
    if(p == q)
        return 1;
    else return 0;
}

int negacja(int p)
{
    if(p == 0)
        return 1;
    return 0;
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

void fromBoolArr(bool arr[32], int limit,unsigned int wynik[]) {
	limit = (limit > 32) ? 32 : limit;
	for (int i = 0; i < limit; i++) {
		wynik[i]=arr[i];
	}
}


void dodajPierwszy(znak *pierwszy,char p)
{
    pierwszy->el = p;
    pierwszy->size = 1;
    pierwszy->next = NULL;
}

void dodajZnak(znak *pierwszy,char p)
{
    znak *wsk = pierwszy;
    if(pierwszy->el == p) return;
    while(wsk->next != NULL)
    {
        if(wsk->next->el == p) return;
        wsk = wsk->next;
    }
    znak *nowy;
    nowy = malloc(sizeof(znak));
    nowy->el = p;
    (pierwszy->size)++;
    nowy->next = NULL;
    wsk->next = nowy;
}

int main()
{
    znak *pierwszy;

    char stos[1001];
    int ws = 0;
    int t;
    char wiersz[1001],ONP[1001];
    fgets(wiersz,1001,stdin);
    sscanf(wiersz,"%d",&t);
    for(int x = 0;x<t;x++)
    {
        for(int z=0;z<1001;z++)
            stos[z]='\0';
        pierwszy = malloc(sizeof(znak));
        pierwszy->size=0;
        ws = 0;
        fgets(wiersz,1001,stdin);
        int i=0,j=0;
        while(wiersz[i] != ';')
        {
            if(wiersz[i] >= 'a' && wiersz[i] <= 'z')
            {
                ONP[j++]=wiersz[i];
                if(pierwszy->size == 0)
                    dodajPierwszy(pierwszy,wiersz[i]);
                else
                    dodajZnak(pierwszy,wiersz[i]);
            }
            else if(wiersz[i] == '1' || wiersz[i] == '0')
                ONP[j++]=wiersz[i];
            else
            {
                if(ws != 0)
                {
                        switch(wiersz[i])
                        {
                            case '~':
                            if(stos[ws-1] == '~') {stos[ws-1]='\0';ws-=2;}
                            else{
                                while(stos[ws-1] == '~') {ONP[j++]=stos[ws-1];ws--;}
                                stos[ws]='~';}
                            break;
                            case '&': while(stos[ws-1] == '~' ||stos[ws-1] == '&') {ONP[j++]=stos[ws-1];ws--;}
                            stos[ws]='&';
                            break;
                            case '|': while(stos[ws-1] == '~' || stos[ws-1] == '&' || stos[ws-1] == '|') {ONP[j++]=stos[ws-1];ws--;}
                            stos[ws]='|';
                            break;
                            case '>': while(stos[ws-1] == '~' || stos[ws-1] == '&' || stos[ws-1] == '|'  ) {ONP[j++]=stos[ws-1];ws--;}
                            stos[ws]='>';
                            break;
                            case '=': while(stos[ws-1] == '~' || stos[ws-1] == '&' || stos[ws-1] == '|' || stos[ws-1] == '>' || stos[ws-1] == '=' ) {ONP[j++]=stos[ws-1];ws--;}
                            stos[ws]='=';
                            break;
                            case '(':stos[ws]='(';
                            break;
                            case ')': while(stos[ws-1] != '(') {ONP[j++]=stos[ws-1];ws--;}
                            ws-=2;
                            break;
                        }
                    ws++;
                }

                else
                    stos[ws++] = wiersz[i];
            }
            i++;
        }
        ws--;
        while(ws >= 0)
        {
             ONP[j++]=stos[ws];
             ws--;

        }
        ONP[j] = ';';
        int ilosc = pierwszy->size;
        char stos2[1001];
        unsigned int wynik[513];
        bool wart[513];
        znak *wsk = pierwszy,*wsk2 = pierwszy;
        int wartosciowania = 0;
        int war_wyn,war_1,war_2;
        ws = 0;
        for(int i=0;i<pot(2,ilosc);i++)
        {
            j=0;ws=0;
            toBoolArr(wart,i) ;
            fromBoolArr(wart,ilosc,wynik);
            wsk = pierwszy;
            for(int k=0;k<ilosc;k++)
                {
                    wsk->wart = wynik[k];
                    wsk = wsk->next;
                }
            while(ONP[j] != ';')
            {
                if(ONP[j] >= 'a' && ONP[j] <= 'z')
                {
                    stos2[ws++] = ONP[j];
                }
                if(ONP[j] == '1' || ONP[j] == '0')
                    stos2[ws++] = ONP[j];
                else
                {
                    if(ONP[j] == '~')
                    {
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z') // jezeli zmienna to czyta jej wartosc
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_1 = wsk2->wart;
                        }
                        else war_1 = stos2[ws] - '0';   // jezeli 1 lub 0 to 1 lub 0 xD
                        war_wyn = negacja(war_1);   // neguje
                        stos2[ws++] = war_wyn + '0';  //wynik zapisuje w tym samym miejscu na stosie
                        wsk2 = pierwszy;

                    }
                    if(ONP[j] == '&')
                    {
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_1 = wsk2->wart;
                        }
                        else war_1 = stos2[ws] - '0';
                        wsk2 = pierwszy;
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_2 = wsk2->wart;
                        }
                        else war_2 = stos2[ws] - '0';
                        war_wyn = koniunkcja(war_1,war_2);
                        stos2[ws++] = war_wyn  + '0';
                        wsk2 = pierwszy;
                    }
                    if(ONP[j] == '|')
                    {
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_1 = wsk2->wart;
                        }
                        else war_1 = stos2[ws] - '0';
                        wsk2 = pierwszy;
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_2 = wsk2->wart;
                        }
                        else war_2 = stos2[ws] - '0';
                        war_wyn = alternatywa(war_1,war_2);
                        stos2[ws++] = war_wyn  + '0';
                        wsk2 = pierwszy;
                    }
                    if(ONP[j] == '=')
                    {
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_1 = wsk2->wart;
                        }
                        else war_1 = stos2[ws] - '0';
                        wsk2 = pierwszy;
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_2 = wsk2->wart;
                        }
                        else war_2 = stos2[ws] - '0';
                        war_wyn = rownowaznosc(war_1,war_2);
                        stos2[ws++] = war_wyn + '0';
                        wsk2 = pierwszy;
                    }
                    if(ONP[j] == '>')
                    {

                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_2 = wsk2->wart;
                        }
                        else war_2 = stos2[ws] - '0';
                        wsk2 = pierwszy;
                        ws--;
                        if(stos2[ws] >= 'a' && stos2[ws] <= 'z')
                        {
                            while(wsk2->el != stos2[ws])
                                wsk2 = wsk2->next;
                            war_1 = wsk2->wart;
                        }
                        else war_1 = stos2[ws] - '0';
                        war_wyn = implikacja(war_1,war_2);
                        stos2[ws++] = war_wyn + '0';
                        wsk2 = pierwszy;
                    }
                }
                j++;
            }
            wsk2 = pierwszy;
            if(stos2[0] == '1') wartosciowania++;
            else if(stos2[0] >= 'a' && stos2[0] <= 'z')
            {
                while(wsk2->el != stos2[0])
                    wsk2 = wsk2->next;
                if(wsk2->wart == 1)wartosciowania++;
            }
            wsk2 = pierwszy;
        }
        printf("%d\n",wartosciowania);
        free(pierwszy);
    }
}
