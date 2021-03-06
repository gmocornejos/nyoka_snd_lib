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
	
	int tam = get_array_lenght(smpls_num);//tam is the number power of two, highest and closest to smpls_num 
	cout << "new size " << tam << "\n";
	
	double *abuffer = (double*)malloc(tam*sizeof(double));
	
	complete_arr(buffer,abuffer,smpls_num);
	
	free(buffer);
	
	complex<double> *plot_buff = (complex<double>*) malloc(tam*sizeof(complex<double>));
	
	sinft(abuffer,plot_buff,tam);//calculated the sine tranform 

	free(abuffer);
	
	plot_freq(plot_buff, tam, smpls_rate);//generates a graphyc

	free(plot_buff);
	return 0;
}
