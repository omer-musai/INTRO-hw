#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_palindrome(char* str, int n);

int main()
{
    int n = 0;
    printf("Enter the length of the array:\n");
    scanf("%d", &n);

    char* str = malloc(sizeof(int) * (n+1));
    if(!str)
    {
        return 0;
    }

    printf("Enter the array:\n");

    scanf("%s", str);

    if(is_palindrome(str, n))
    {
        printf("A palindrome\n");
        free(str);
        return 0;
    }
    else
    {
        printf("Not a palindrome\n");
        free(str);
        return 0;
    }
}


bool is_palindrome(char* str, int n)
{
    if(n == 1 || n == 0)
    {
        return true;
    }
    
    if(str[0] == str[n-1])
    {
        return is_palindrome(str + 1, n-2);
    }
    else
    {
        return false;
    }
}