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

float sigma1 = 1;
float sigma2 = 10;
float lambda = 0.0001;
float gain = 1;
float gain1 = 1;
float gain2 = -0.2;
int maskSize = 0;


int circ(int i) { return (i+n)%n; }

int main(int argc, char const *argv[]) {
	maskSize = ceil(sigma2)*2+1;
	mask = falloc(maskSize);
	input = falloc(n); fzero(input, n);
	A = falloc(n); fzero(A,n);
	_A = falloc(n); fzero(_A,n);

	for(t=0; ;t+=0.01) {
		for(int i=0; i<n; i++) {
			scanf("%f", &input[i]);
		}

		for(int i=0; i<n; i++) {
			A[i] += gain*input[i] - lambda*A[i];
			for(int j=0; j<maskSize; j++) {
				A[circ(i+j-maskSize/2)] += _A[i]*mask[j];
			}
		}

		for(int i=0; i<n; i++) _A[i] = A[i];

		printf("%f", A[0]);
		for(int i=1; i<n; i++) printf(" %f", A[i]);
	 	printf("\n");
	}

	return 0;
}
