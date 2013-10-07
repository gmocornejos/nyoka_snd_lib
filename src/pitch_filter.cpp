#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

#define PI 3.141592654
#define PITCH 1
#define UNPITCH 0

using namespace std;

// Recommended values: percent ~0.1 increment ~.45
void pitch_filter(int smpls_num, int smpls_rate, double *inbuffer, double percent, double increment){

	// Creates a new array to work with.
	// The wave must be over de axis.
	double *buffer = (double*) malloc(smpls_num*sizeof(double));
	for(int i = 0; i < smpls_num; i++) buffer[i] = abs(inbuffer[i]);

	double *result = (double*) malloc(smpls_num*sizeof(double));
	int *classification = (int*) malloc(smpls_num*sizeof(int));

	for(int i = 0; i < smpls_num; i++){
		cout << "Progress: " << (i*100)/smpls_num << "%" << "\r";
		fflush(stdout);
		double maxdistance = 0;
	        double c0, c1;
		int witeration = 1;
		for(int wsize = percent*smpls_rate; wsize < smpls_num; wsize = wsize*pow((1 + increment), witeration)){
			// initial centroids
			double max=0, min=0;
			double value;
			for(int j = 0; j < smpls_num; j++){
				if(j > i-wsize && j < i + wsize){
					value = buffer[j]*(1 + cos((PI*(j-i))/(2*wsize +1)));
					if(value > max){
						max = value;
					}else if(value < min){
						min = value;
					}
				}
			}

			c1 = max;
			c0 = min;

			// Allocating each sample in buffer into a class (cluster).
			for(int j = 0; j < smpls_num; j++){
                                if(j > i-wsize && j < i + wsize){
					value = buffer[j]*(1 + cos((PI*(j-i))/(2*wsize +1)));
					if(abs(c1 - value) <= abs(c0 - value)){
						classification[j] = PITCH;
					}else{
						classification[j] = UNPITCH;
					}
				}else {
					classification[j] = 0;
				}
			}
			// k-means algorithm
			double tmpc1, tmpc0;
			double num1 = 0, num0 = 0, den1 = 0, den0 = 0;
			int k = 0;
			// Stops when k >= 100 or when the centroids stop moving. 
			while((k < 100) && !((c1 == tmpc1) && (c0 == tmpc0))){
				tmpc1 = c1;
				tmpc0 = c0;
				// Calc new centroids
				for(int j = 0; j < smpls_num; j++){
					num1 = num1 + classification[j]*buffer[j]*(1 + cos((PI*(j-i))/(2*wsize +1)));
					den1 = den1 + classification[j]*(1 + cos((PI*(j-i))/(2*wsize +1)));
					num0 = num0 + (1-classification[j])*buffer[j]*(1 + cos((PI*(j-i))/(2*wsize +1)));
					den0 = den0 + (1-classification[j])*(1 + cos((PI*(j-i))/(2*wsize +1)));
				}
				c1 = num1/den1;
				c0 = num0/den0;

				//reallocating samples to a cluster
				for(int j = 0; j < smpls_num; j++){
                         	       if(j > i-wsize && j < i + wsize){
						value = buffer[j]*(1 + cos((PI*(j-i))/(2*wsize +1)));
						if(abs(c1 - value) <= abs(c0 - value)){
							classification[j] = PITCH;
						}else{
							classification[j] = UNPITCH;
						}
					}
				}
				k++;
			}

			if((c1 - c0) > maxdistance){
				maxdistance = c1 - c0;
				double frac = (buffer[i] - c0)/(maxdistance);
				if(frac > 0.5){
					result[i] = PITCH;
				}else{
					result[i] = UNPITCH;
				}
			}
			witeration++;
		}
	}

	free(classification);

	// turns to zero all the unpitched samples.
	for(int i = 0; i < smpls_num; i++){
		if(result[i] == 0) inbuffer[i] = 0;
	}

	free(result);
}

