#include <stdio.h>
#include <math.h>

#define DELTA 0.000001
#define FOUR 4
#define TWO 2
#define THREE 3

int main()
{
    //variables declaration
    double a=0, b=0, c=0, first_root=0, second_root=0, discriminant =0;

    //prompt the user for input
    while(a < DELTA && a > -DELTA)
    {
        printf("Enter the coefficients of a polynomial:\n");
        if(scanf("%lf %lf %lf", &a, &b, &c) < THREE)
        {
            return 0;
        }
    }

    //calculate discriminant
    discriminant = (b*b - FOUR*a*c); 
    
    //discriminant is 0
    if (discriminant < DELTA && discriminant > -DELTA)
    {
        if(b < DELTA && b > -DELTA)
        {
            printf("The root is %.3lf\n", b);    
            return 0;
        }
        first_root = -b / (TWO*a);
        printf("The root is %.3lf\n", first_root);
        return 0;
    }
    else if (discriminant > DELTA) //discriminant is positive
    {
        first_root = ((-b - sqrt(discriminant)) / TWO*a);
        second_root = ((-b + sqrt(discriminant)) / TWO*a);
        printf("The roots are %.3lf, %.3lf\n", first_root, second_root);
        return 0;
    }
    else //discriminant is negative
    {
        printf("There are no roots\n");
        return 0;
    }
}

