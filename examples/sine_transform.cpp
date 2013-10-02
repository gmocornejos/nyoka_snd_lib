#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

#include <sinft.hh>
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
	
	cout << "aqui llega "  << "\n";
	
	complete_arr(buffer,abuffer,smpls_num);
	
	free(buffer);
	
	cout << "aqui llega2 "  << "\n";
	
	sinft(abuffer, smpls_num);
	cout << "aqui no "  << "\n";
	
	plot_decoder(abuffer, tam, smpls_rate);
	
/*	complex<double> *plotbuff = (complex<double>*) malloc(tam*sizeof(complex<double>));
	
	for(int c=0; c<tam; c++){
		plotbuff[c]= complex<double>(abuffer[c],0);
	}
	free(abuffer);
	
	plot_fft(plotbuff, tam, smpls_rate);
	*/
	return 0;
}
