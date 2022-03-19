#include <stdio.h>
#include <stdbool.h>

#define N 5

int possible_assignments(int matrix[][N]);
int possible_assignments_aux(int matrix[][N], int task_taken[], int worker);


int main()
{
    int matrix[N][N];
    
    printf("Enter the matrix:\n");
    for(int i=0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    int result = possible_assignments(matrix);
    printf("The result is %d\n", result);
    return 0;
}

int possible_assignments(int matrix[][N])
{
    int task_taken[N] = {0};
    return possible_assignments_aux(matrix, task_taken, 0);
}


int possible_assignments_aux(int matrix[][N], int task_taken[], int worker)
{
    //all assigned
    if(worker == N)
    {
        return 1;
    }

    int result = 0;
    //check each possible task and add the solution
    for (int i = 0; i < N; i++)
    {
        if(matrix[worker][i] && !task_taken[i])
        {
            task_taken[i] = 1;
            result += possible_assignments_aux(matrix, task_taken, worker + 1);
            task_taken[i] = 0;
        }
    }
    return result;
}