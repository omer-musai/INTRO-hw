#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAXGRADES 50
#define SIGMA 10

//function declaration
double minMaxGrades(double grades[], int n, bool min_max);
double meanGrades(double grades[], int n);
double stdGrades(double grades[], double n, double average);
void printGrades(double grades[], int n);
void updateGrades(double grades[],int n,double exp_avg,double sigma_max);
void printGradesOpening();
void printOldGrades(double grades[], int num_of_grades);
void printOldGradesStatistics(double min, double max,
                                 double mean, double std);
void printNewGrades(double grades[], int num_of_grades);
void printNewGradesStatistics(double min, double max,
                                double mean, double std);
   


int main()
{
    //last element will be the expected average
    double grades[MAXGRADES+1], x=0;
     
    int n=0;
    printGradesOpening();

    while(scanf("%lf", &x) != EOF)
    {   
        grades[n] = x;
        n++;
    }
    //average inserted as the last element and should'nt be considered
    n--;

    
    printOldGrades(grades, n);
    printOldGradesStatistics(minMaxGrades(grades, n, true),
        minMaxGrades(grades, n, false),
        meanGrades(grades, n),stdGrades(grades,n,meanGrades(grades,n)));

    updateGrades(grades, n, grades[n], SIGMA);

    printNewGrades(grades, n);
    printNewGradesStatistics(minMaxGrades(grades, n, true),
        minMaxGrades(grades, n, false),
        meanGrades(grades, n), stdGrades(grades,n,meanGrades(grades,n)));

}


double minMaxGrades(double grades[], int n, bool min_max)
{
    double min = grades[0], max = grades[0];

    for (int i = 1; i < n; i++)
    {
        if(max < grades[i])
        {
            max = grades[i];
        }
        if (min > grades[i])
        {
            min = grades[i];
        }
    }

    return min_max ? min : max;
}

double meanGrades(double grades[], int n)
{
    double sum = 0;

    for (int i=0; i<n; i++)
    {
        sum += grades[i];
    }

    return (sum / n);
}

double stdGrades(double grades[], double n, double average)
{
    double sigma;
    double sum=0;

    for(int i=0; i<n; i++)
    {
        sum += ((grades[i] - average) * (grades[i] - average));
    }
    
    sigma = sqrt( (1/n) * sum);
    return sigma;
}

void printGrades(double grades[], int n)
{
    for (int i=0; i<n; i++)
    {
        printf("%.1lf ", grades[i]);
    }
    printf("\n");
}

void updateGrades(double grades[],int n,double exp_avg,double sigma_max)
{
    double curr_avg = meanGrades(grades, n);
    double sigma_curr = stdGrades(grades, n, curr_avg);

    if(sigma_curr > sigma_max)
    {
        double sigma_factor = (sigma_max / sigma_curr);
        for (int i=0; i<n; i++)
        {
            grades[i] = (sigma_factor * grades[i]);
        }

        curr_avg = meanGrades(grades, n);
    }

    double tmp = curr_avg - exp_avg;

    double avg_diff = (tmp > 0 ? tmp : -1*tmp);

    if(avg_diff > 1)
    {
        for(int i =0; i<n; i++)
        {
            grades[i] = grades[i] - curr_avg + exp_avg;
        }
    }
}

void printGradesOpening(){
    printf("Please enter the grades of the examinees");
    printf(" followed by the expected mean\n");
}

void printOldGrades(double grades[], int num_of_grades){
    printf("Old grades: ");
    printGrades(grades, num_of_grades);
}

void printOldGradesStatistics(double min, double max,
                              double mean, double std){
    printf("Old minimum grade: %.1f\n", min);
    printf("Old maximum grade: %.1f\n", max);
    printf("Old mean: %.1f\n", mean);
    printf("Old standard deviation: %.1f\n",std);

}

void printNewGrades(double grades[], int num_of_grades){
    printf("New grades: ");
    printGrades(grades, num_of_grades);
}

void printNewGradesStatistics(double min, double max,
                              double mean, double std){
    printf("New minimum grade: %.1f\n", min);
    printf("New maximum grade: %.1f\n", max);
    printf("New mean: %.1f\n", mean);
    printf("New standard deviation: %.1f\n", std);
}