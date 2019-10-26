#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int seed = 15; // Do not change this line

int main(void) {
	int d = 3, N = 5; // d is the number of features; N is the sample size
	int data[N][d]; // 2d array to store all the data
	float average[d]; // 1d array to store all the averages 
	float matrix[d][d]; // 2d array representing to covariance matrix
	int i, j, k;
	float sum;
	/* < Declare, if any, other local variables here > */
	srand(seed);

	/* Generate random values in the respective domains and store in data[][] */
	for (i = 0; i < N; i++) { // Replace ??? with appropriate expression
		for (j = 0; j < d; j++) { // Replace ??? with appropriate expression
			switch (j) { // Replace ??? with appropriate expression
				 /* < Fill in the different cases here > */
			case 0:
				data[i][j] = rand() % 16 + 60;//Height (X) variable in the range [60,75]; 
        break;
			case 1:
				data[i][j] = rand() % 151 + 550;//Test Score (Y) variable in the range [550, 700]; 
        break;
			case 2:
				data[i][j] = rand() % 36 + 25;//Age (Z) variable in the range [25,60] 
        break;

			}
		}
	}

	/* Display data */
	printf("Data used:\n");
	for (i = 0; i < N; i++) { // Replace ??? with appropriate expression
		for (j = 0; j < d; j++) { // Replace ??? with appropriate expression
			printf("%d ", data[i][j]); // Replace ??? with appropriate expression
		}
		printf("\n");
	}

	/* Compute averages and store in average[] */
   /* Display averages */
	for (i = 0; i < d; i++) { // Replace ??? with appropriate expression
		sum = 0;
		for (j = 0; j < N; j++) { // Replace ??? with appropriate expression
			sum += data[j][i]; // Replace ??? with appropriate statement
		}
		average[i] = (float)sum / N;
		/* < Fill in your code here > */
	}

	/* Display averages */

	printf("\n\nAverage Height: %.2f\n", average[0]);
	printf("Average Test Score: %.2f\n", average[1]);
	printf("Average Age: %.2f\n", average[2]);
	/* < Fill in your code here > */


/* Compute variances & covariances and store in matrix[][] */

	/* Display variances */
	for (i = 0; i < d; i++) { // Replace ??? with appropriate expression
		sum = 0;
		for (j = 0; j < d; j++) { // Replace ??? with appropriate expression
			for (k = 0; k < N; k++) {
				if (i == j)
				{
					sum += (data[k][i] - average[i]) * (data[k][j] - average[j]);
				}
				else
				{
					sum += (data[k][i] - average[i]) * (data[k][j] - average[j]);
				}
			}
			matrix[i][j] = sum / (N - 1);
			sum = 0;
		}
	}
	printf("\n\nVar(Height): %f\n", matrix[0][0]);
	printf("Var(Test Score): %f\n", matrix[1][1]);
	printf("Var(Age): %f\n\n", matrix[2][2]);

	/* Display covariance matrix (Remember to align the matrix; see Lab 1 Q2)*/
	printf("Covariance Matrix:\n");
	for (i = 0; i < d; i++) { // Replace ??? with appropriate expression
	    for (j = 0; j < d; j++) { // Replace ??? with appropriate expression
	        printf("%.2f ", matrix[i][j]);
	    }
	    printf("\n");
	}
	getchar();
	return 0;
}