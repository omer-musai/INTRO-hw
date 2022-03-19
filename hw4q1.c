
/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define N 50
#define M 50
#define RECT 4
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3
#define TWO 2



/* put your #defines and typedefs here*/
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);
int sum_rect(int integral_image[][M], int rect[RECT]);
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);
void print_array(int a[N][M], int n, int m);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/

//nest loop with mn iterations and in each iteration O(1) operations. overall, time complexity: O(mn) space complexity: O(1)
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M])
{
    int curr_row_sum =0;

    for (int i=0; i < n; i++)
    {
        curr_row_sum = 0;

        for (int j=0; j < m; j++)
        {
            curr_row_sum += image[i][j];
            if(i > 0)
            {
                integral_image[i][j] = curr_row_sum + integral_image[i-1][j];
            }
            else if(i == 0)
            {
                integral_image[i][j] = curr_row_sum;
            }
            
        }
    }
}

//checks condition and return value in time complexity of O(1), no space used: space complexity O(1)
int sum_rect(int integral_image[][M], int rect[RECT])
{
    if(rect[TOP] == -1 && rect[LEFT] == -1)
    {
        return integral_image[rect[BOTTOM]][rect[RIGHT]];
    }
    else if(rect[TOP] == -1)
    {
        return integral_image[rect[BOTTOM]][rect[RIGHT]] - integral_image[rect[BOTTOM]][rect[LEFT]];
    }
    else if(rect[LEFT] == -1)
    {
        return integral_image[rect[BOTTOM]][rect[RIGHT]] - integral_image[rect[TOP]][rect[RIGHT]];
            
    }
    else{
        return integral_image[rect[BOTTOM]][rect[RIGHT]] - integral_image[rect[TOP]][rect[RIGHT]] - integral_image[rect[BOTTOM]][rect[LEFT]]
            + integral_image[rect[TOP]][rect[LEFT]];
    }
}

//nest loop with mn iterations and in each iteration O(1) operations, sum_rect also in O(1)., overall, time complexity: O(mn) space complexity: O(1)
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M])
{
    int sum = 0;
    int rect[RECT];
    double avg =0;

    for(int i=0; i < n; i++)
    {
        if(i - (h/TWO) < 1) {rect[TOP] = -1;}
        else {rect[TOP] = i - (h/TWO) - 1;}
     
        if(i + (h/TWO) >= n) {rect[BOTTOM] = n-1;}
        else {rect[BOTTOM] = i + (h/TWO);}

        for(int j=0; j < m; j++)
        {
            if(j - (w/TWO) < 1) {rect[LEFT] = -1;}
            else {rect[LEFT] = j - (w/TWO) - 1;}
  
            if(j + (w/TWO) >= m) {rect[RIGHT] = m-1;}
            else {rect[RIGHT] = j + (w/TWO);}
        
            sum = sum_rect(integral_image, rect);
            avg = (double)sum / (w * h);
            average[i][j] = round(avg); 
        }
    }
}



/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

