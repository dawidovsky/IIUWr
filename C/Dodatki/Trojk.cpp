#include <stdio.h>

using namespace std;

int main()
{
    int a;
    cin>>a;
    int suma=0;
    int suma2=0;
    for(int i=1;i<=a;i++)
    {
        suma+=i*2;
        suma+=i-1;
    }
    cout<<suma<<endl;
}
