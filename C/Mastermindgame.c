/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Mastermind
 *
 * @file: mastermind.c
 * @author: Hans Kurnia (Group C01A)
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cs1010.h"

#define max_length 3

bool checkcode(char code[], char guess[])
{
	//variables to store number of black and white pegs
	long black_pegs = 0;
	long white_pegs = 0;

	//arrays to store if variables have been checked
	bool checked_code[4] = {false};
	bool checked_guess[4] = {false};

	//check for pegs with correct color and position
	for (long i = 0; i <= max_length; i += 1)
	{
		if (code[i] == guess[i])
		{
			black_pegs += 1;
			checked_code[i] = true;
			checked_guess[i] = true;
		}
	}

	//checks for pegs with correct color but wrong position
	for (long k = 0; k <= max_length; k += 1)
	{
		for (long m = 0; m <= max_length; m += 1)
		{
			if ((m != k) && (code[k] == guess[m]) && !checked_code[k] && !checked_guess[m])
			{
				white_pegs += 1;
				checked_code[k] = true;
				checked_guess[m] = true;
			} 
		}
	}

	//prints black and white pegs
	cs1010_print_long(black_pegs);
	cs1010_print_string(" ");
	cs1010_print_long(white_pegs);
	cs1010_println_string("");

	//check if guess is all correct
	if(black_pegs == 4 && white_pegs == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void getcode(char code[])
{
	srand(time(NULL));
	char colors[6] = {'0', '1', '2', '3', '4', '5'};
	for (long t = 0; t <= 3; t += 1)
	{
		code[t] = colors[rand()%5];
	}
}

int main()
{
	/**
	@param[in] code the correct code user selected
	@param[in] guess the code the user guessed
	*/
	//char *code = cs1010_read_word();
	
	bool try_again = true;
	char code[4];
	printf("Welcome to Mastermind!!\n");
	printf("You have 8 guesses to guess the code\n");
	printf("4 digits of numbers 0, 1, 2, 3, 4, 5\n ");
	//loop to continously as for a guess and checks it till guess is correct
	while (try_again == true)
	{
		printf("\nCode generated\n");
		printf("Good luck! Start guessing now\n");
		try_again = false;
		char again, hint;
		bool correct = false; //variable to store if user guessed correct
		long guess_count = 0;
		long lastt = 10;

		getcode(code);
		do
		{
			guess_count += 1;
			char *guess = cs1010_read_word();
			if (strlen(guess) != 4 )
			{
				printf("Your guess need 4 digits!!!\n");
				guess_count -= 1;
				continue;
			}
			correct = checkcode(code, guess);
			free(guess);
			if(correct == false)
			{
				printf("Wrong, %ld guesses left\n", 8-guess_count);
			}
			if(guess_count % 3 == 0)
			{
				printf("Need an hint???  [y/n]: \n");
				scanf("%c", &hint);
				if(hint == 'y')
				{
					long t = rand()%3;
					printf("the correct code consists of,");
					for(long i = 0; i <= 3; i+=1)
					{
						if (i != t && i != lastt)
						printf("*");
						else
						printf("%c", code[i]);
					}
					printf("\n\n");
					lastt = t;
					continue;
				}
				else
				{
					continue;
				}
			}
		} while (correct == false && guess_count < 8);

		if(correct == true)
		{
			printf("Correct, congratulations!!!\n");
			printf("%ld wrong guesses\n", guess_count);
		}
		else
		{
			printf("Sorry, you ran out of guesses...\n");
			printf("Correct code was ");
			printf("%c%c%c%c", code[0], code[1], code[2], code[3]);
		}
		printf("\n\n New game? [y/n] : ");
		scanf("%c", &again);
		if(again == 'y')
		{
			try_again = true;
			again = 'n';
		}
		printf("\n");
	}
	return 0;
}