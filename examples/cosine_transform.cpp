#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

#include <cosft.hh>
#include <plot.hh>
#include <ogg_vorbis.hh>

using namespace std;

int get_array_lenght (double *arr, const int size) {	
	int n,array_lenght=0;
	for (n=2; 3<4; n++) {
		if(pow(2, n) >= size){
			array_lenght = pow(2, n);
			break;
		}	
	}
	return array_lenght;
}

void complete_arr (double *arr_in, double *arr_out, const int size) {
	int array_lenght = get_array_lenght(arr_in, size);

	for (int c=0; c<array_lenght; c++) {
		if(c<size){
			arr_out[c]= arr_in[c];
		}	
		else{
			arr_out[c]= 0;
		}
	}	
} 	

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
	
	cosft(abuffer, 1, smpls_num);
	cout << "aqui no "  << "\n";
	
	plot_freq_real(buffer, smpls_num, smpls_rate);
	
	free(abuffer);
	
	return 0;
}
