#include <stdlib.h>
#include <iostream>

#include <plot.hh>
#include <ogg_vorbis.hh>
#include <freqfilters.hh>
#include <fftwest.hh>

using namespace std;

int main(int argc, char *argv[]){
	const char *fname = argv[1];
	int lowfreq = atoi(argv[2]);
	int highfreq = atoi(argv[3]);
//	const char *outfilename = argv[4];

        int smpls_num = samples_number(fname);
        double smpls_rate = samples_rate(fname);

        double *buffer = (double*)malloc(smpls_num*sizeof(double));
        int smpls_read = decode(fname, buffer, smpls_num);
	if(smpls_num != smpls_read){
		cout << "Error decoding";
	}

	double *bandbuff = (double*) malloc(smpls_num*sizeof(double));
	bandpass(smpls_num, smpls_rate, buffer, bandbuff, lowfreq, highfreq);//calculate the band pass of buffer and sent this in bandbuff 
	free(buffer);

	complex<double> *fftbuff = (complex<double>*) malloc((0.5*smpls_num +1)*sizeof(complex<double>));
	fft_west(smpls_num, bandbuff, fftbuff);
	free(bandbuff);

	plot_freq(fftbuff, smpls_num, smpls_read);
//	plot_time(bandbuff, smpls_num, smpls_rate);
//	encoder(outfilename, lowbuff, smpls_num, smpls_rate);
	free(fftbuff);
	return 0;
}
