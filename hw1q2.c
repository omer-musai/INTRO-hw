#include <stdio.h>
#define a 'a'
#define z 'z'
#define A 'A'
#define Z 'Z'
#define SYMBOL '#'

int main()
{
    char letter, seq;
    int counter=0;

    //prompt the user for a letter
    printf("Enter letter to count:\n");
    if(!scanf("%c", &letter))
    {
        return 0;
    }

    //not a letter
    if(!((letter >= a && letter <= z) || (letter >= A && letter <= Z)))
    {
        return 0;
    }

    printf("Enter the char sequence:\n");
    while(scanf("%c", &seq))
    {
        if(seq == SYMBOL)
        {
            break;
        }
        else if((letter >= a && letter <= z) && (seq == letter || seq == letter - (a - A)))
        {
            counter++;
        }
        else if((letter >= A && letter <= Z) && (seq == letter || seq == letter + (a - A)))
        {
            counter++;
        }
    }
    printf("The letter appeared %d times\n", counter);
    return 0;
}