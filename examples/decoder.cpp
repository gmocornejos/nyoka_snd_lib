#include <iostream>
#include <stdlib.h>

#include <ogg_vorbis.hh>
#include <plot.hh>

using namespace std;


int main(int argc, char *argv[]){
	const char *fname = argv[1];

	int smpls_num = samples_number(fname);
	cout << "samples number " << smpls_num << "\n";
	double smpls_rate = samples_rate(fname);
	cout << "sample rate " << smpls_rate << "\n";

	double *buffer = (double*)malloc(smpls_num*sizeof(double));
	int smpls_read = decode(fname, buffer, smpls_num);
	cout << "smpls_read " << smpls_read << "\n";

	plot_decoder(buffer, smpls_read, smpls_rate);
	free(buffer);
	return 0;
}
