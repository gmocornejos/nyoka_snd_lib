#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <complex>

#include <cosft.hh>
#include <plot.hh>
#include <ogg_vorbis.hh>

using namespace std;	

int main(int argc, char *argv[]){
	const char *fname = argv[1];
	
	int smpls_num = samples_number(fname);
	
	double smpls_rate = (double)smpls_num/total_time(fname);
	double *buffer = (double*)malloc(smpls_num*sizeof(double));

	long smpls_read = decode(fname, buffer, smpls_num);
	cout << "smpls_read " << smpls_read << "\n";
	
	int tam = get_array_lenght(buffer, smpls_num);
	cout << "new size " << tam << "\n";
	
	double *abuffer = (double*)malloc(tam*sizeof(double));
	
	complete_arr(buffer,abuffer,smpls_num);
	
	free(buffer);
	
	cosft(abuffer, tam);
	
	complex<double> *plot_buff = (complex<double>*) malloc(tam*sizeof(complex<double>));
	
	for(int c=0; c<(tam/2); c++){
		plot_buff[c]=complex<double> (abuffer[2*c], abuffer[2*c+1]);
	}
	free(abuffer);
	
	plot_freq_cmplx(plot_buff, tam, smpls_rate);

	free(plot_buff);
	return 0;
}
