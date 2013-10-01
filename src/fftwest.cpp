#include <stdlib.h>
#include <iostream>
#include <complex>

#include <fftw3.h>

using namespace std;

void fft_west(int smpls_num, double *buffer, complex<double> *retbuffer){

	double *inbuffer = (double*) malloc(sizeof(double)*smpls_num);
	fftw_complex *outbuffer = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(0.5*smpls_num+1));
	fftw_plan plan = fftw_plan_dft_r2c_1d(smpls_num, inbuffer, outbuffer, NULL);

        //initializing inbuffer
        for(int i = 0; i < smpls_num; i++) inbuffer[i] = buffer[i];
        fftw_execute(plan);
	fftw_free(inbuffer);
	fftw_destroy_plan(plan);
	for(int i = 0; i < (0.5*smpls_num+1); i++){
		retbuffer[i] = (complex<double>) (outbuffer[i][0], outbuffer[i][1]); 
	}
	
	fftw_free(outbuffer);

}

void ifft_west(int smpls_num, complex<double> *buffer, double *retbuffer){
	
	fftw_complex *inbuffer = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(0.5*smpls_num+1));
	fftw_plan plan = fftw_plan_dft_c2r_1d(smpls_num, inbuffer, retbuffer, NULL);
	for(int i = 0; i < (0.5*smpls_num+1); i++){
		inbuffer[i][0] = real(buffer[i]);
		inbuffer[i][1] = imag(buffer[i]);
	}

	fftw_execute(plan);
	fftw_free(inbuffer);
	fftw_destroy_plan(plan);

}
