#include <iostream>

void fix(std::pair<int, int> h[], int n, int at, long long v){
    if(2*at+1 <n){
        if(2*at+2 < n){  
            int largest = (long long)h[2*at+1].first * h[2*at+1].second < (long long)h[2*at+2].first * h[2*at+2].second ? 2*at+2 : 2*at+1;
            long long larvalue = (long long)h[largest].first * h[largest].second;
            if(v < larvalue){  
                swap(h[at], h[largest]);
                fix(h, n, largest, v);
            }
        }
        else{  
            long long larvalue = (long long)h[2*at+1].first * h[2*at+1].second;
            if(v < larvalue) swap(h[at], h[2*at+1]); 
            return;
        }
    }
}

void change(std::pair<int,int> h[], int n){
    h[0].second--; 
    long long v = (long long)h[0].first * h[0].second;
    fix(h, n, 0, v);
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    std::pair<int,int> h[n];
    for(int i=n,j=0; i>0; i--,j++)
        h[j] = std::pair<int,int>(i, i);
    long long lv = (long long)n * n;
    printf("%lld\n", lv);
    change(h, n); 
    k--;
    long long av = (long long)h[0].first * h[0].second;
    while(k>0){ 
        if(lv != av){  
            lv = av;
            printf("%lld\n", lv);
            k--;
        }
        change(h, n); 
        av = (long long)h[0].first * h[0].second;
    }
}