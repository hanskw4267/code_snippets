#include "cs1010.h"
#include <windows.h>
#include <stdbool.h>

long filter_sentence(char *sentence, char *filtered)
{
	long count = 0;
	long length = strlen(sentence);
	for (long i = 0; i < length; i += 1)
	{
		if (sentence[i] >= 'a' && sentence[i] <= 'z')
		{
			filtered[count] = sentence[i];
			count += 1;
		}
		else if (sentence[i] >= 'A' && sentence[i] <= 'Z')
		{
			filtered[count] = sentence[i] - 'A' + 'a';
			count += 1;
		}
		
	}
	cs1010_print_string(filtered);
	return count;
}

bool check_palindrome(char *filtered, long count)
{
	long start = 0;
	long end = count - 1;
	while(start <= end)
	{
		if (filtered[start] != filtered[end])
		{
			return false;
		}
		start += 1;
		end -= 1;
	}
	return true;
}

int main()
{
	char *sentence = cs1010_read_line();
	char *filtered;

	filtered = calloc(strlen(sentence), sizeof(char));

	long count = filter_sentence(sentence, filtered);

	bool palindrome = check_palindrome(filtered, count);
	
	if (palindrome == false)
	{
		cs1010_println_string(" is NOT a palindrome");
	}
	else
	{
		cs1010_println_string(" IS a palindrome");
	}
	
	free(sentence);
	free(filtered);
	system("pause");
	return 0;
}