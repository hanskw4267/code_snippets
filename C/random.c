#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int seed = 15;


int main()
{
	long count = 0;
	srand(seed);
	do
	{
		printf("%d\n", rand()%16+60);
		count+=1;
	}while(count <= 100);
	getchar();
	return 0;
}