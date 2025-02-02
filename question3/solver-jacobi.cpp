#include <bits/stdc++.h>
#include <stdlib.h>
#include <math.h>
#include<omp.h>
using namespace std;
extern double eps;
extern double **New_Matrix(int m, int n);
extern void Delete_Matrix(double **matrix);
int solver(double **a, int n)
{
	int i,j;
	double h;
	double diff;
	int k = 0;
	double **b = New_Matrix(n,n);
	double time = omp_get_wtime();
	if (b == NULL) 
	{
		cerr << "Jacobi: Can’t allocate matrix\n";
		exit(1);
	}
	
			do 
			{
						diff = 0;
						#pragma omp parallel for shared(n,b,a) private(i,j) reduction(max:diff)
						for (i=1; i<n-1; i++) 
						{
							for (j=1; j<n-1; j++) 
							{
								b[i][j] = 0.25 * (a[i][j-1] + a[i-1][j]+ a[i+1][j] + a[i][j+1]);
								/* Determine the maximum change of the matrix elements */
								// h = fabs(a[i][j] - b[i][j]);
								// #pragma omp critical
								// if (h > diff) diff = h;
								diff=max(diff,fabs(a[i][j] - b[i][j]));
							}
						}
						/*
						** Copy intermediate result into matrix ’a’
						*/
						#pragma omp parallel for shared(n,b,a) private(i,j)
						for (i=1; i<n-1; i++) 
						{
							for (j=1; j<n-1; j++) 
							{
								a[i][j] = b[i][j];
							}
						}
						k++;
				
					
		} while (diff > eps && k<100);
		
	printf(" in %lf seconds\n",omp_get_wtime()-time);
	Delete_Matrix(b);
	return k;
}

