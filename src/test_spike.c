#include <stdio.h>


int main(int argc, char const *argv[]) {
	for(int i=0; i<1000; i++) {
		for(int j=0; j<100; j++) {
			if(i<50) printf("%f\n", (j==50 ? 1.0 : 0.0));
			else if(i<100) printf("%f\n", (j==50 || j==15 ? 1.0 : 0.0));
			else if(i<150) printf("%f\n", (j==15 ? 1.0 : 0.0));
			else printf("%f\n", 0.0);
		}
	}
	return 0;
}
