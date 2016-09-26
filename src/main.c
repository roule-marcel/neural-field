#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int n = 100;

float* input = 0;
float* A = 0;
float* _A = 0;
float* mask = 0;
float t = 0;

float sigma1 = 10;
float sigma2 = 40;
float lambda = 0.8;
float gain = 0.3;
float gain1 = 0.7;
float gain2 = -0.6;


int circ(int i) { return (i+n)%n; }

int main(int argc, char const *argv[]) {
	int maskSize = ceil(sigma2)*4+1;
	mask = falloc(maskSize);
	input = falloc(n); fzero(input, n);
	A = falloc(n); fzero(A,n);
	_A = falloc(n); fzero(_A,n);

	fprintf(stderr, "MASK=%u\n", maskSize);

	for(int i=0; i<maskSize; i++) {
		float d = i-maskSize/2;
		mask[i] = gain1*exp(-(d*d)/(2*sigma1*sigma1))
				+ gain2*exp(-(d*d)/(2*sigma2*sigma2));
	}

	for(t=0; ;t+=0.01) {
		for(int i=0; i<n; i++) {
			scanf("%f", &input[i]);
		}

		for(int i=0; i<n; i++) {
			A[i] += gain*input[i] - (lambda*A[i]);
			for(int j=0; j<maskSize; j++) {
				A[circ(i+j-maskSize/2)] += _A[i]*mask[j];
			}
		}

		for(int i=0; i<n; i++) {
			if(A[i]<0) A[i] = 0;
			_A[i] = A[i];
		}

		printf("%f", A[0]);
		for(int i=1; i<n; i++) printf(" %f", A[i]);
	 	printf("\n");
	}

	return 0;
}
