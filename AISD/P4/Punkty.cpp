#include <iostream>
#include <algorithm>
#include <cmath>
#define FLT_MAX 3.40282e+38;

class CPoints{
    public:
        std::pair<int, int> a;
        std::pair<int, int> b;
        float dist;
        CPoints(std::pair<int, int> aa, std::pair<int, int> bb, double d){
            a = aa;
            b = bb;
            dist = d;
        }
};

double min(double x, double y) { return (x < y)? x : y; }
CPoints min(CPoints x, CPoints y) { return (x.dist < y.dist)? x : y; }

double dist(std::pair<int, int> p1, std::pair<int, int> p2){  
    long long x = (long long)(p1.first - p2.first) * (long long)(p1.first - p2.first);
    long long y = (long long)(p1.second - p2.second) * (long long)(p1.second - p2.second);
    return sqrt(x + y);  
}  

bool sortBySecond(const std::pair<int, int> &a, const std::pair<int, int> &b){
    return (a.second < b.second);
}

CPoints brute(std::pair<int, int> P[], int n){
    double min = FLT_MAX;  
    std::pair<int, int> a, b;
    for(int i=0; i<n; i++)  
        for(int j=i+1; j<n; j++)  
            if (dist(P[i], P[j]) < min){
                a = P[i];
                b = P[j];
                min = dist(P[i], P[j]);  
            }
    CPoints X(a, b, min);
    return X;
}

CPoints closest(std::pair<int, int> close[], int n, CPoints min)  
{  
    std::sort(close, close + n, sortBySecond);  
  
    for(int i=0; i<n; i++)  
        for(int j=i+1; j<n && (double)(close[j].second - close[i].second)<min.dist; j++)  
            if(dist(close[i], close[j]) < min.dist){
                min.dist = dist(close[i], close[j]);  
                min.a = close[i];
                min.b = close[j];
            }  
  
    return min;   
}  

CPoints findPoints(std::pair<int, int> points[], int n){
    if(n <= 3) return brute(points, n);

    int m = n/2;

    CPoints L = findPoints(points, m);
    CPoints R = findPoints(points + m, n - m);

    CPoints P = min(L, R);

    std::pair<int, int> close[n];
    int count = 0;
    for(int i=0; i<n; i++)  
        if((double)abs(points[i].first - points[m].first) < P.dist)
            close[count++] = points[i];

    return closest(close, count, P);
}

int main(){
    int n;
    scanf("%d", &n);
    std::pair<int, int> points[n];
    for(int i=0; i<n; i++)
        scanf("%d %d", &points[i].first, &points[i].second);

    std::sort(points, points + n);

    CPoints p = findPoints(points, n);
    
    printf("%d %d\n", p.a.first, p.a.second);
    printf("%d %d", p.b.first, p.b.second);
}