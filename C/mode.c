#include <stdlib.h>
#include<time.h>
#include<stdio.h>


int main() {
	int DATA[20],i, j, d, maxValue = 0, maxCount = 0, N=20,temp,maxV=0;
	float sum = 0, mean, median, mid1, mid2;

	/* Intializes random number generator */
	srand(time(NULL)); /* setting a seed value */

	/* Print 10 random numbers from 1 to 10 */
	printf("The set of numbers are: \n");
	for (int i = 0; i < N; i++) {
		DATA[i] = rand() % 10 + 1;
		printf("%d ", DATA[i]);
	}
	//sorts data in ascending order
	for (i = 0; i < N - 1; i++)
	{
		for (d = 0; d < N - i - 1; d++)
		{
			if (DATA[d] > DATA[d + 1]) /* For decreasing order use < */
			{
				temp = DATA[d];
				DATA[d] = DATA[d + 1];
				DATA[d + 1] = temp;
			}
		}
	}

	printf("\nSorted list in ascending order:\n");

	for (i = 0; i < N; i++)
	{
		printf("%d ", DATA[i]);
		sum = sum + DATA[i];
	}

	mean = sum / N;
	printf("\nMean of the data: %f", mean);
	mid1 = DATA[9];
	mid2 = DATA[10];
	median = (mid1+mid2) / 2;
	printf("\nMedian of the data: %f", median);

	for (i = 1; i <= 10; i++) {
		int count = 0;

		for (j = 0; j < N; j++) {
			if (DATA[j] == i)
				count++;
		}

		if (count >= maxCount) {
			maxCount = count;
			maxValue = i;
		}
	}
	printf("\nThe mode of the set is: %d for value %d\n", maxCount, maxValue);
	printf("Range of this data: %d\n", DATA[19] - DATA[0]);
	getchar();
}