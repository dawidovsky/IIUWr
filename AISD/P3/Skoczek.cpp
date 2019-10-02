#include <iostream>
#include <map>

long long max(long long a, long long b){
    return a >= b ? a : b;
}

void twoup(int k, long long tab1[], long long tab2[], long long ftab[]){
    for(int i=0; i<k; i++){
            if(i-1 >= 0 && tab2[i-1] != 0){
                if(i+1 < k && tab2[i+1] != 0)
                    tab1[i] = max(tab2[i-1], tab2[i+1]) + ftab[i];
                else    
                    tab1[i] = tab2[i-1] + ftab[i];
            }
            else if(i+1 < k && tab2[i+1] != 0)
                tab1[i] = tab2[i+1] + ftab[i];
    }
}

void onedown(int k, long long tab1[], long long tab2[], long long ftab[]){
    for(int i=0; i<k; i++){
        if(i-2 >= 0 && tab2[i-2] != 0){
            if(i+2 < k && tab2[i+2] != 0)
                tab1[i] = max(tab1[i], max(tab2[i-2], tab2[i+2]) + ftab[i]);
            else
                tab1[i] = max(tab1[i], ftab[i] + tab2[i-2]);
        }
        else if(i+2 < k && tab2[i+2] != 0)
            tab1[i] = max(tab1[i], ftab[i] + tab2[i+2]);
    }
}

void rewrite(long long tab1[], long long tab2[], int k){
    for(int i=0; i<k; i++)
        tab1[i] = tab2[i];
}

void d(long long tab[], int k){
    for(int i=0; i<k; i++)
        std::cout << tab[i] << " ";
    std::cout << "\n";
}

int main(){
    std::map<char, int> power;
    power['0'] = 1; power['1'] = 7; power['2'] = 49; power['3'] = 343; power['4'] = 2401;
    power['5'] = 16807; power['6'] = 117649; power['7'] = 823543; 
    power['8'] = 5764801; power['9'] = 40353607;
    int w,k;
    scanf("%d %d", &w, &k);
    int count = w;
    char line[k];
    long long tab[3][k];
    long long first_tab[3][k];
    for(int i=0; i<w && i<3; i++){
        std::fgets(line, k+1, stdin);
        std::fgets(line, k+1, stdin);
        for(int j=0; j<k; j++){
            tab[i][j] = i==0 ? power[line[j]] : 0;
            first_tab[i][j] = power[line[j]];
        }
        count--;
    }
    twoup(k, tab[2], tab[0] , first_tab[2]);
    onedown(k, tab[1], tab[2], first_tab[1]);

    while(count>0){
        rewrite(tab[0], tab[1], k);
        rewrite(tab[1], tab[2], k);

        rewrite(first_tab[0], first_tab[1], k);
        rewrite(first_tab[1], first_tab[2], k);
        
        std::fgets(line, k+1, stdin);
        std::fgets(line, k+1, stdin);
        for(int j=0; j<k; j++){
            tab[2][j] = 0;
            first_tab[2][j] = power[line[j]];
        }
        count--;

        twoup(k, tab[2], tab[0] , first_tab[2]);
        onedown(k, tab[1], tab[2], first_tab[1]);
    }

    long long max = 0;
    for(int i=0; i<k; i++)
        if(max < tab[2][i]) max = tab[2][i];

    printf("%lld", max);
}