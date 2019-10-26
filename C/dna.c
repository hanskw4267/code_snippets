#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 150 // Length of DNA sequence
int seed = 696;

/* Function Prototypes */
void dnaGenerator(char[], int); // Generate the DNA sequence
void statAnalyzer(char[], int); // Count the occurrences of each base
void motifFinder(char[], int, char[][3], int); // Count the occurrences of each motif

int main(void) {
	char dna[N + 1]; // Store DNA sequence
	char motif[][3] = { "AG", "CT", "TA", "GC", "AA" }; // Motifs to be counted
	srand(time(NULL));

	printf("DNA Sequence:\n");
	dnaGenerator(dna, N);
	printf("==================================\n");
	printf("Nucleotide Frequency:\n");
	statAnalyzer(dna, N);
	printf("==================================\n");
	printf("Motif Frequency:\n");
	motifFinder(dna, N, motif, 5);
	getchar();
	return 0;
}

/**
 * Generates a DNA sequence comprising of 'A', 'T', 'G' and 'C';
 * Displays the DNA sequence generated.
 *
 * @param dna[] (char) is an array to store the DNA sequence
 * @param size (int) is the length of DNA sequence
 *
 * @pre size is a non-negative integer
 * @pre Length of dna[] array >= size + 1
 *
 * @post Each element in dna[] is from the set {'A', 'T', 'G', 'C'}
 */
void dnaGenerator(char dna[], int size) {
	// Fill in your code here
	int i = 0, input;
	char alpha[4] = {"ATGC"};
	while (i < size)
	{
		input = rand() % 4;
		dna[i] = alpha[input];
		printf("%c", dna[i]);
		i++;
	}
	printf("\n");
}

/**
 * Counts and displays the number of occurrences of each base;
 * Evaluates and displays the probability of occurrence of each base.
 *
 * @param dna[] (char) is the DNA sequence
 * @param size (int) is the length of DNA sequence
 *
 * @pre size is a non-negative integer
 * @pre Each element in dna[] from the set {'A', 'T', 'G', 'C'}
 */
void statAnalyzer(char dna[], int size) {
	// Fill in your code here
	int i = 0, j =0,k=0,q=0,r=0;
	float P = 0;
	for (i = 0; i < size; i++) {
		if ('A' == dna[i])
			j++;
		if ('T' == dna[i])
			k++;
		if ('G' == dna[i])
			q++;
		if ('C' == dna[i])
			r++;
	}
	P = ((float)j / size) * 100;
	printf("'A': Occurrences = %d, Probability = %.2f %\n", j, P);
	
	P = ((float)k / size * 100);
	printf("'T': Occurrences = %d, Probability = %.2f %\n", k, P);
	j = 0;
	
	P = ((float)q / size * 100);
	printf("'G': Occurrences = %d, Probability = %.2f %\n", q, P);
	
	P = ((float)r / 150 * 100);
	printf("'C': Occurrences = %d, Probability = %.2f %\n", r, P);

}

/**
 * Counts and displays the number of occurrences of each motif in the DNA sequence;
 * Finds and displays the indices of the occurrence of each motif in the DNA sequence;
 * Displays the most frequent motif in the DNA sequence.
 *
 * @param dna[] (char) is the DNA sequence
 * @param dna_size (int) is the length of DNA sequence
 * @param motif[][] (char) contains the motifs to search for in the DNA sequence
 * @param motif_size (int) is the number of motifs to search for in the DNA sequence
 *
 * @pre Each element in dna[] from the set {'A', 'T', 'G', 'C'}
 * @pre Each element in motif[][] is a combination of elements in set {'A', 'T', 'G', 'C'}
 * @pre dna_size is a non-negative integer
 * @pre motif_size is a non-negative integer
 * @pre Length of each element in motif[][] <= length of dna[]
 */
void motifFinder(char dna[], int dna_size, char motif[][3], int motif_size) {
	long occurences[dna_size][5];
	long count = 0;
	for (long i = 0; i < motif_size; i += 1)
	{
		count = 0;
		for (long k = 1; k < dna_size; k += 1)
		{
			if (dna[k] == motif[i][1] && dna[k-1] == motif[i][0])
			{
				occurences[count][i] = k-1;
				count += 1;
			}
		}
		printf("\"%s\" Occurrences: = %ld, Indices: (", motif[i], count);
		for (long m = 0; m < count; m += 1)
		{
			printf("%ld", occurences[m][i]);
			if (m+1 != count)
			{
				printf(", ");
			}
		}
		printf(")\n");
	}
  
}
