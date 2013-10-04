#include <stdlib.h>
#include <iostream>

#include <plot.hh>
#include <noise.hh>
#include <ogg_vorbis.hh>

using namespace std;

int main(int argc, char *argv[]){\
	int smpls_num = atoi(argv[1]);
	//char *outfilename = argv[2];

	double *buffer = (double*) malloc(smpls_num*sizeof(double));
	whitenoise(smpls_num, buffer);
	//Assuming 44.1 KHz as sample rate.
	plot_time(buffer, smpls_num, 44100);
	//encoder(outfilename, buffer, smpls_num, 44100);
	free(buffer);
}
