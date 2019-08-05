#include<stdio.h>
#include <stdlib.h>
#include <archlab.h>

#define N (128*4*4096)
#define ITERS 100

typedef double v4d __attribute__((vector_size(32)));

double go(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i++) {
    sum += A[i] * B[i];
  }
  return sum;
}

double unroll4_temps(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i+=4) {
    double t1 = A[i] * B[i];
    double t2 = A[i+1] * B[i+1];
    double t3 = A[i+2] * B[i+2];
    double t4 = A[i+3] * B[i+3];
    sum+= t1 + t2 + t3 + t4;
  }
  return sum;
}

double unroll4(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i+=4) {
    sum += A[i] * B[i];
    sum += A[i+1] * B[i+1];
    sum += A[i+2] * B[i+2];
    sum += A[i+3] * B[i+3];
  }
  return sum;
}

double unroll8(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i+=2) {
    sum += A[i] * B[i];
    sum += A[i+1] * B[i+1];
    sum += A[i+2] * B[i+2];
    sum += A[i+3] * B[i+3];
    sum += A[i+4] * B[i+4];
    sum += A[i+5] * B[i+5];
    sum += A[i+6] * B[i+6];
    sum += A[i+7] * B[i+7];
  }
  return sum;
}

double unroll2(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i+=8) {
    sum += A[i] * B[i];
    sum += A[i+1] * B[i+1];
  }
  return sum;
}

double unroll2_temps(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i+=8) {
    double t1 = A[i] * B[i];
    double t2 = A[i+1] * B[i+1];
    sum += t1 + t2;
  }
  return sum;
}

double unroll8_temps(double * A, double *B, int len) {
  double sum = 0.0; 
  for(int i = 0; i < len; i+=2) {
    double t0 =A[i] * B[i];
    double t1 =A[i+1] * B[i+1];
    double t2 =A[i+2] * B[i+2];
    double t3 =A[i+3] * B[i+3];
    double t4 =A[i+4] * B[i+4];
    double t5 =A[i+5] * B[i+5];
    double t6 =A[i+6] * B[i+6];
    double t7 =A[i+7] * B[i+7];
    sum += t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7;
  }
  return sum;
}

double vector(double * A, double *B, int len) {
  v4d vSum = {0.0, 0.0, 0.0, 0.0};
  for(int i = 0; i < len/4; i++) {
    vSum += A[i] * B[i];
  }
  return vSum[0] + vSum[1] + vSum[2] + vSum[3];
}



