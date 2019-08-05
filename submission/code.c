#include <stdio.h>
#include <stdlib.h>
#include <archlab.h>


double go(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i++) {
    sum += A[i] * B[i];
  }
  return sum;
}

