#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* a, int na, int* b, int nb, int* c);
void mergeSort(int* arr, int n);
void mergeSort_aux(int* arr, int n, int* tmp_arr);

//time complexity: mergeSort in O(nlogn), 2 iterations over n elements in O(n) overall: O(nlogn)
//space complexity: create arrray of n elements + mergesort creates tmp_arr, overall: O(n)
int main()
{
    int n = 0;

    printf("Enter the length of the array:\n");
    scanf("%d", &n);
    

    int* arr = (int*)malloc(sizeof(int) * n);
    if(!arr)
    {
        return 0;
    }

    printf("Enter the array:\n");

    for(int i=0; i < n; i++)
    {
        scanf("%d", arr+i);
    }
    
    mergeSort(arr, n);
   
   //two side cases
    if(arr[n-1] < 0)
    {
        printf("The array is recommended and x = 0");
        free(arr);
        return 0;
    }
    if(arr[0] >= n)
    {
        printf("The array is recommended and x = %d", n);
        free(arr);
        return 0;
    }
    
    //checks if the array is recommended
    for(int x = 1; x < n; x++)
    {
        if(arr[n-x-1] < x && arr[n-x] >= x)
        {
            printf("The array is recommended and x = %d", x);
            free(arr);
            return 0;
        }
    }
    
    printf("The array is not recommended\n");
    free(arr);
    return 0;
}


void mergeSort(int* arr, int n)
{
    int* tmp_arr = malloc(sizeof(int) * n);
    
    mergeSort_aux(arr, n ,tmp_arr);
   
    free(tmp_arr);
}

void merge(int* a, int na, int* b, int nb, int* c)
 {
    int ia = 0, ib = 0, ic =0 ;
    
    //compare between element in a and element in b and put the lower one in c, then update the iterator of the used array.
    while((ia < na) && (ib < nb))
    {
        if(a[ia] < b[ib])
        {
            c[ic] = a[ia];
            ia++;
        }
        else
        {
            c[ic] = b[ib];
            ib++;
        }
        ic++;
    }

    //add the leftovers to c
    for(;ia < na; ia++, ic++)
    {
         c[ic] = a[ia];
    }
    for(;ib < nb; ib++, ic++)
    {
         c[ic] = b[ib];
    }
}

void mergeSort_aux(int* arr, int n, int* tmp_arr)
{
    int left = n/2;
    int right = n - left;
    
    if(n < 2)
    {
        return;
    }
    //sort each half of the array
    mergeSort_aux(arr, left, tmp_arr);
    mergeSort_aux(arr + left, right, tmp_arr);

    //merge both sorted halves
    merge(arr, left, arr+left, right, tmp_arr);
    
    //save result in the original array
    memcpy(arr, tmp_arr, n*sizeof(int));
}