#include <stdio.h>
#include <stdlib.h>
int spiral(int w, int h, int x, int y)
{
	if(y!=0)
    {
        int wynik = w + spiral(h - 1, w, y - 1, w - x - 1);
        return wynik;
    }
    else
        return x;
}

int main(int argc, char *argv[])
{
	int w,i, j;
	if(!argv) w=17;
	else w=atoi(argv);
	int max=w*w;
	for (i = 0; i < w; i++) {
		for (j = 0; j < w; j++)
			printf("%4d", max-spiral(w, w, j, i));
		putchar('\n');
	}
}
