#include <stdio.h>
#include <stdbool.h>

#define GRADES_RANGE 9
void printHistogram(int hist[GRADES_RANGE],char axis,char symbol,int max);
void printDownAxis(int hist[GRADES_RANGE], char symbol, int max);
void printUpAxis(int hist[GRADES_RANGE], char symbol, int max);
void printLeftAxis(int hist[GRADES_RANGE], char symbol);
void printRightAxis(int hist[GRADES_RANGE], char symbol, int max);

int main()
{   
    char symbol, axis;
    int x, max=0, hist[GRADES_RANGE] = {0};
    
    printf("Please enter a character:\n");
    scanf("%c", &symbol);

    printf("Please enter histogram axis:(U/D/R/L)\n");
    
    while(scanf(" %c", &axis))
    {
        if (axis == 'U' || axis == 'R' || axis == 'L' || axis == 'D')
        {
            break;
        }
        printf("Wrong direction, try again!\n");
        printf("Please enter histogram axis:(U/D/R/L)\n");
    }

    printf("Please enter grades:\n");
    while(scanf("%d", &x) != EOF)
    {
        hist[x-1]++;
        if(hist[x-1] > max)
        {
            max = hist[x-1];
        }
    }
    printHistogram(hist, axis, symbol, max);
}

void printHistogram(int hist[GRADES_RANGE],char axis,char symbol,int max)
{
    printf("Histogram:\n");
    if (axis == 'D')
    {
        printDownAxis(hist, symbol, max);
    }
    else if (axis == 'U')
    {
        printUpAxis(hist, symbol, max);
    }
    else if (axis == 'R')
    {
        printRightAxis(hist, symbol, max);
    }
    else if (axis == 'L')
    {
        printLeftAxis(hist, symbol);
    }
    
}

void printDownAxis(int hist[GRADES_RANGE], char symbol, int max)
{
    for (int i=0; i < max; i++)
        {
            for (int j=0; j < GRADES_RANGE; j++)
            { 
                if(j == GRADES_RANGE-1)
                {
                    if(hist[j] >= max - i)
                    {
                        printf("%c\n", symbol);
                    }
                    else printf(" \n");
                    
                    continue;
                }
                if(hist[j] >= max - i)
                {
                    printf("%c ", symbol);
                }
                else printf("  ");
            }
        }
        for(int i=0; i<GRADES_RANGE; i++)
        {
            if(i == GRADES_RANGE-1)
            {
                printf("%d\n", i+1);
            }
            else printf("%d ", i+1);
        }
}

void printUpAxis(int hist[GRADES_RANGE], char symbol, int max)
{
    for(int i=0; i<GRADES_RANGE; i++)
        {
            if(i == GRADES_RANGE-1)
            {
                printf("%d\n", i+1);
            }
            else printf("%d ", i+1);
        }

    for (int i=0; i < max; i++)
        {
            for (int j=0; j < GRADES_RANGE; j++)
            { 
                if(j == GRADES_RANGE-1)
                {
                    if(hist[j] >= i + 1)
                    {
                        printf("%c\n", symbol);
                    }
                    else printf(" \n");
                    
                    continue;
                }
                if(hist[j] >= i + 1)
                {
                    printf("%c ", symbol);
                }
                else printf("  ");
            }
        }  
}

void printLeftAxis(int hist[GRADES_RANGE], char symbol)
{
    for (int i=0; i < GRADES_RANGE; i++)
    {
        printf("%d ", i+1);
    
        for(int j =0; j < hist[i]; j++)
        {
            if (j == hist[i] - 1)
            {
                printf("%c", symbol);
            }
            else
            {
                printf("%c ", symbol);
            }
        }
        printf("\n");
    }
}

void printRightAxis(int hist[GRADES_RANGE], char symbol, int max)
{
    for (int i=0; i < GRADES_RANGE; i++)
    {
        for(int j =0; j < max; j++)
        {
            if(j < hist[i])
            {
                printf("%c ", symbol);
            }
            else
            {
                printf("  ");
            }
        }
        printf("%d\n", i+1);
    }
}