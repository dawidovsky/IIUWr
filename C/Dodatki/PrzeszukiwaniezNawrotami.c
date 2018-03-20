#include <stdio.h>

#define n 4

int b[n];

void init()
{
  int i;
  for(i=0;i<n;i++)
    b[i]=-1;
}

int isfree(int x, int y)
{
  int i;
  for(i=0;i<x;i++)
    if(b[i]-i==y-x || b[i]+i==y+x || b[i]==y) return 0;
  return 1;
}

int queens()
{
  int k=1;
  b[0]=0;
  while(k<n && k>=0)
  {
    do {
      b[k]++;
    } while(b[k]<n && !isfree(k,b[k]));
    if(b[k]<n)k++;
    else {b[k]=-1;k--;}
  }
  return k;
}

void drawresult()
{
  int i,j;
  printf("\n");
  for(i=0;i<n;i++)
    printf("%d ",b[i] );
  printf("\n\n");
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
      {
        if(b[j]==i) printf("x ");
        else printf("o ");
      }
      printf("\n");
  }
}

int main()
{
  init();
  if(queens()==n) drawresult();
  else printf("brak rozwiazania");
}
