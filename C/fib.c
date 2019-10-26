#include <stdio.h>

int main()
{
	long n = 0;
	long i = 1; long count = 0;
	unsigned long long prev = 0; unsigned long long lastprev = 0; unsigned long long fib = 0; unsigned long long prod = 0;
	scanf("%ld", &n);
	getchar();
	while (i <= n)
	{
		if (i == 1)
		{
			printf("Iteration: %ld, Current fib number: 0\n==========\n", i);
		}
		else
		{
			if (prev == 0)
			{
				fib = 1;
			}
			else
			{
				fib = prev + lastprev;
			}
			prod = fib * prev;
			printf("Iteration: %ld, Current fib number: %llu\n", i, fib);
			printf("Product of current term and preceeding term: %llu\n", prod);
			if (prod % 5 == 0)
			{
				printf("The product %llu is divisible by 5\n", prod);
				count++;
			}
			printf("==========\n");
		}
		i++;
		lastprev = prev;
		prev = fib;
	}
	printf("Total number of product that are divisble by 5: %ld\n", count);
	getchar();
	return 0;
}