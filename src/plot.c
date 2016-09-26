#include "utils.h"
#include "jpg.h"


int n = 100;
float* A = 0;
float* out = 0;

int main(int argc, char const *argv[]) {
	system("rm -rf plot_out");
	system("mkdir -p plot_out");

	float min = argc>=2 ? atof(argv[1]) : 0;
	float max = argc>=3 ? atof(argv[2]) : 1;

	A = falloc(n);
	out = falloc(n*100);

	char file[256];
	for(int t=0; ; t++) {
		for(int i=0; i<n; i++) {
			scanf("%f", &A[i]);
		}

		for(int i=0; i<n; i++) {
			int val = (int) ((A[i]-min)/(max-min));
			for(int j=0; j<100; j++) {
				out[j*n+i] = (100-j)<val ? 255 : 0;
			}
		}
		sprintf(file, "plot_out/%08d.jpg", t);
		save_jpg(out, n, 100, file);
	}
}
