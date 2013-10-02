#include <iostream>
#include <stdlib.h>
#include <complex>

#include <ogg_vorbis.hh>
#include <plot.hh>
#include <fftwest.hh>

using namespace std;

int main(int argc, char *argv[]){
	const char *fname = argv[1];

	//decode
	int smpls_num = samples_number(fname);
	double smpls_rate = samples_rate(fname);
	double *buffer = (double*)malloc(smpls_num*sizeof(double));
	long smpls_read = decode(fname, buffer, smpls_num); 
	if(smpls_num != smpls_read){
		cout << "Error decoding \n";
		return 1;
	}
	// Creates a complex array (retbuffer) to receive the FFT result.
	complex<double> *retbuffer = (complex<double>*) malloc((0.5*smpls_read+1)*sizeof(complex<double>));
	fft_west(smpls_read, buffer, retbuffer);
	free(buffer);
	plot_freq_cmplx(retbuffer, (0.5*smpls_read+1), smpls_rate);
	free(retbuffer);
	return 0;
}
