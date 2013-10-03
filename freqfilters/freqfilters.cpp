#include <stdlib.h>
#include <iostream>

#include <ogg_vorbis.hh>
#include <plot.hh>

#define PI 3.141592654

void lowpass(int smpls_num, int smpls_rate, double *buffer, double *lowbuff, double freq){
	double dt = 1/smpls_rate;
	double alpha = (2*PI)
}


int main(int argc, char argv[]){
	 const char *fname = argv[1];

        int smpls_num = samples_number(fname);
        double smpls_rate = samples_rate(fname);

        double *buffer = (double*)malloc(smpls_num*sizeof(double));
        int smpls_read = decode(fname, buffer, smpls_num);
	if(smpls_num != smpls_read){
		cout << "Error decoding";
	}
	return 0;
}
