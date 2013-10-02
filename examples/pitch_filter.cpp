#include <stdlib.h>
#include <iostream>

#include <ogg_vorbis.hh>
#include <pitch_filter.hh>
#include <plot.hh>

using namespace std;

int main(int argc, char *argv[]){
	const char *fname = argv[1];
	const char *outfilename = argv[2];

	/*** decoding ***/
	int smpls_num = samples_number(fname);

	double smpls_rate = samples_rate(fname);
	double *buffer = (double*) malloc(smpls_num*sizeof(double));
	int smpls_read = decode(fname, buffer, smpls_num);
	if(smpls_read != smpls_num){
		cout << "Error decoding \n";
		return 1;
	}

	/*** filter ***/
	double percent = 0.1;
	double increment = 0.45;
	pitch_filter(smpls_num, smpls_rate, buffer, percent, increment);
//	plot_decoder(buffer, smpls_num, smpls_rate);
	encoder(outfilename, buffer, smpls_num, smpls_rate);
	free(buffer);

	return 0;
}

