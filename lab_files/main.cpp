#include "archlab.hpp"
#include <stdlib.h>
#include <getopt.h>
#include "lab.h"
#include <stdio.h>
#include<string.h>
#include<unistd.h>


extern "C" {
	double go(double * A, double *B, int len);
}

double reference(double * A, double *B, int len) {
  
	double sum = 0.0; 
	for(int i = 0; i < len; i++) {
		sum += A[i] * B[i];
	}

	return sum;
}

int main(int argc, char *argv[]) {
  
	uint64_t vec_size_small;
	uint64_t vec_size_large;
	uint32_t iterations;
  
	archlab_add_si_option<uint64_t>("vec-small",  vec_size_small, 4096 ,  "Small memory region size (bytes).");
	archlab_add_si_option<uint64_t>("vec-large",  vec_size_large, 1*MB,  "Large region size (bytes).");
	archlab_add_si_option<uint32_t>("iterations", iterations , 1,  "Repetitions");
		     
	archlab_parse_cmd_line(&argc, argv);


	double * A = (double *)malloc(vec_size_large*sizeof(double)); // allocate two big vectors
	double * B = (double *)malloc(vec_size_large*sizeof(double));
  
	for(uint32_t i = 0; i < vec_size_large; i++) {
		A[i] = rand_double(); // fill them with random data
		B[i] = rand_double();
	}

	for(uint64_t size = vec_size_small; size <= vec_size_large; size *= 2) { // and for different vector sizes
		
		double correct = reference(A, B, size); // compute correct answer
		fprintf(stderr, "correct value is %f\n", correct);
		pristine_machine(); // clear caches, disable turbo boost, reset clock speed
		{
			ArchLabTimer timer; 
			timer. attr("vector_size", size).
				attr("iterations", iterations).
				go(); // Start measuring
			for(uint32_t k = 0; k < iterations; k++) {
				double r = go(A, B, size);  // Call submitted code
				if (r != correct) {
      				        fprintf(stderr, "Incorrect result: %f.\n", r);
					exit(1);
				}
			}
		}
	}
 
	archlab_write_stats();
  
	return 0;
}	

