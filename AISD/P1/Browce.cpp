#include <iostream>

long long abs(long long x){
    return x < 0 ? -x : x;
}

int main(){
    int t;
    long long sum = 0;
    scanf("%d", &t);
    int path[t];
    for(int i=0; i<t; i++){
        scanf("%d", &path[i]);
        sum += path[i];
    }
    long long closeToHalf = sum;
    int start = 0;
    int end = 0;
    long long currentPath = 0;
    long long halfSum = sum/2;
    while(end < 2 * t){
        int s = start%t;
        int e = end%t;
        if(currentPath < halfSum){
            currentPath += path[e];
            end++;
        }
        else{
            currentPath -= path[s];
            start++;
        }
        // std::cout << "start " << start << " end " << end << " current " << currentPath; 
        long long temp = abs(halfSum - currentPath);
        if(temp < closeToHalf) closeToHalf = temp; 
        // std::cout << " max " << closeToHalf << std::endl;
    }
    printf("%lld", halfSum - closeToHalf);
}