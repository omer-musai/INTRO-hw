/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define MASCULINE (1)
#define FEMININE (2)

#define UN (1)
#define UNO (2)
#define UNA (3)
#define UN_APOSTROPHE (4)

#define MALE 'o'
#define FEMALE 'a'
#define IA_LENGTH_4 4
#define IA_LENGTH_3 3

#define UN_STR "un "
#define UNO_STR "uno "
#define UNA_STR "una "
#define UN_APOSTROPHE_STR "un'"


/* put your #defines and typedefs here*/
int get_gender(char* noun);
int get_indefinite_article(char* noun);
int get_length_indefinite_article(char* noun);
void add_indefinite_article(char* noun, char* noun_with_article);
void handle_indefinite_article(int max_length);


bool is_sibilant(char first_letter, char following_letter);
bool is_vowel(char letter);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/
int get_gender(char* noun)
{
	if(noun[strlen(noun) - 1] == MALE)
	{
		return MASCULINE;
	}
	else if(noun[strlen(noun) - 1] == FEMALE)
	{
		return FEMININE;
	}
	return 0;
}

int get_indefinite_article(char* noun)
{
	int gender = get_gender(noun);

	if(gender == MASCULINE)
	{
		if(is_sibilant(noun[0], noun[1]))
		{
			return 	UNO;
		}
		else
		{
			return 	UN;	
		}
	}
	else if(gender == FEMININE)
	{
		if(is_vowel(noun[0]))
		{
			return UN_APOSTROPHE;
		}
		else
		{
			return UNA;
		}
	}
	return 0;
}

int get_length_indefinite_article(char* noun)
{
	int i_a = get_indefinite_article(noun);
	if (i_a == UNA || i_a == UNO)
	{
		return strlen(noun) + IA_LENGTH_4;
	}
	else if(i_a == UN || i_a == UN_APOSTROPHE)
	{
		return strlen(noun) + IA_LENGTH_3;
	}
	return 0;
}

void add_indefinite_article(char* noun, char* noun_with_article)
{
	int i_a = get_indefinite_article(noun);
	if(i_a == UNA)
	{
		strcpy(noun_with_article, UNA_STR);
		strcat(noun_with_article, noun);
	}
	else if (i_a == UN)
	{
		strcpy(noun_with_article, UN_STR);
		strcat(noun_with_article, noun);
	}
	else if (i_a == UN_APOSTROPHE)
	{
		strcpy(noun_with_article, UN_APOSTROPHE_STR);
		strcat(noun_with_article, noun);
	}
	else if (i_a == UNO)
	{
		strcpy(noun_with_article, UNO_STR);
		strcat(noun_with_article, noun);
	}
}

void handle_indefinite_article(int max_length)
{
	char* noun = malloc(sizeof(char) *(max_length +1));

	scanf("%s", noun);

	char* noun_with_article = malloc(sizeof(char) * (strlen(noun)+get_length_indefinite_article(noun)+1));

	add_indefinite_article(noun, noun_with_article);

	printf("%s\n", noun_with_article);
	
	free(noun);
	free(noun_with_article);

}


bool is_sibilant(char first_letter, char following_letter)
{
	if(first_letter == 'z' || first_letter == 'x' || first_letter == 'y' ||
	   (first_letter == 'g' && following_letter == 'n') || (first_letter == 'p' && following_letter == 's') ||
	    (first_letter == 'i' && is_vowel(following_letter)))
	{
		return true;
		
	}
	return false;
}

bool is_vowel(char letter)
{
	if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'h')
	{
		return true;
	}
	return false;
}
/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

/**
 * main - reads two integers and calls handle_indefinite_article() accordingly.
 * 
 * @returns the status, for the operating system.
 */
int main() {
	int max_length, num_of_nouns;
	scanf("%d %d", &max_length, &num_of_nouns);
	for(int i = 0; i < num_of_nouns; i++) {
		handle_indefinite_article(max_length);
	}
	return 0;
}