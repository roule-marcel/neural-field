#include <stdio.h>


int main(int argc, char const *argv[]) {
	for(int i=0; i<1000; i++) {
		for(int j=0; j<100; j++) {
			printf("%f\n", (i<50 && j==50 ? 1.0 : 0.0));
		}
	}
	return 0;
}
