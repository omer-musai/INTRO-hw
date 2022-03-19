#include <stdio.h>
#define N 4

int is_strong(int mat[N][N], int row ,int column);
int space_rank(int mat[N][N], int row ,int column);


int main()
{
    int rank =0, x=0, strong_elements =0;
    int mat[N][N];

    printf("Please enter a matrix:\n");
    
    for (int i=0; i< N; i++)
    {
        for (int j=0; j<N; j++)
        {   
            scanf("%d" , &x);
            mat[i][j] = x;
        }
    }

    for (int i=0; i< N; i++)
    {
        for (int j=0; j<N; j++)
        {   
            if(is_strong(mat, i, j))
            {
                strong_elements++;
            }
            rank += space_rank(mat, i ,j);
        }
    }

    printf("Strong elements: %d\nSpace rank: %d\n",strong_elements,rank);
}


int is_strong(int mat[N][N], int row ,int column)
{
    int result = 0;
    result = ((row+1 < N ? (mat[row][column] > mat[row+1][column]) : 1)&&
        (column+1 < N ? (mat[row][column] > mat[row][column+1]) : 1)&&
        (row-1 >= 0 ? (mat[row][column] > mat[row-1][column]) : 1 )&&
        (column-1 >= 0 ? (mat[row][column] > mat[row][column-1]) : 1));

    return result;
}

int space_rank(int mat[N][N], int row ,int column)
{
    int rank = column + 1 < N ? mat[row][column]-mat[row][column+1] : 0;

    return rank > 0 ? rank : -1 * rank;
}