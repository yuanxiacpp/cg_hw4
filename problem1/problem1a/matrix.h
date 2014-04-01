#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void printMatrix(double *a, int n);
void transpose(double *a, int n);

double* multiply(double *a, double *b, int p, int q, int r);

void normalizeCol(double *a, double *g, int n, int col);


double dotProductForCols(double *a, int n, int col1, int col2);


void updateFromPrevCols(double *u, double *g, int n, int col);

void updateFollowingCols(double *u, double *g, int n, int col);


void assignIdentity(double *a, int n);

void inv_double_gs(double *a, int n, double *u, double *b);
