#include <iostream>
#include <stdlib.h>
#include <complex>

#include <ogg_vorbis.hh>
#include <plot.hh>
#include <fftwest.hh>

using namespace std;

int main(int argc, char *argv[]){
        const char *fname = argv[1];
//	const char *outfilename = argv[2];

        //decode
        int smpls_num = samples_number(fname);
        double smpls_rate = samples_rate(fname);
        double *buffer = (double*)malloc(smpls_num*sizeof(double));
        long smpls_read = decode(fname, buffer, smpls_num); 
        if(smpls_num != smpls_read){
                cout << "Error decoding \n";
                return 1;
        }
	 // Creates a complex array (fftbuffer) to receive the FFT result.
        complex<double> *fftbuffer = (complex<double>*) malloc(sizeof(complex<double>)*(0.5*smpls_read+1));
        fft_west(smpls_read, buffer, fftbuffer);
        free(buffer);

	//Creates a double array to store de inverse fft
	double *ibuffer = (double*) malloc(smpls_read*sizeof(double));
	ifft_west(smpls_read, fftbuffer, ibuffer);
	free(fftbuffer);

	// Inverse Fourier return an array with all entries multiplied. 
	// We take the maxvalue as reference. So -1 < ibuffer < 1.
	double maxvalue = 0;
	for(int i = 0; i < smpls_read; i++){
		if(ibuffer[i] > maxvalue) maxvalue = ibuffer[i];
	}
	for(int i = 0; i < smpls_num; i++) ibuffer[i] = ibuffer[i]/maxvalue;


//	encoder(outfilename, ibuffer, smpls_num, smpls_rate);
	plot_time(ibuffer, smpls_read, smpls_rate);
	free(ibuffer);
	return 0; 
}
