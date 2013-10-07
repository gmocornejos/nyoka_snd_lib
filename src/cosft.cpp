#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <complex>

#include <fftwest.hh>

using namespace std;	

int get_array_lenght (const int size) {	
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
	int array_lenght = get_array_lenght(size);
	
	for (int c=0; c<array_lenght; c++) {
		if(c<size){
			arr_out[c]= arr_in[c];
		}	
		else{
			arr_out[c]= 0;
		}
	}	
} 

void cosft (double *y, complex<double> *rbuffer, const int size){
	const double PI=3.1415;
	int j,n=size-1;
	double sum,y1,y2,theta,wi=0.0,wpi,wpr,wr=1.0,wtemp;
	
	double *yy = (double*)malloc(n*sizeof(double));

	theta=PI/n;
	wtemp=sin(0.5*theta);
	wpr	= -2.0*wtemp*wtemp;
	wpi=sin(theta);
	sum=0.5*(y[0]-y[n]);
	yy[0]=0.5*(y[0]+y[n]);
	
	for (j=1;j<n/2;j++) {
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
		y1=0.5*(y[j]+y[n-j]);
		y2=(y[j]-y[n-j]);
		yy[j]=y1-wi*y2;
		yy[n-j]=y1+wi*y2;
		sum += wr*y2;
	}

	yy[n/2]=y[n/2];

	complex<double> *retbuffer = (complex<double>*) malloc((0.5*n+1)*sizeof(complex<double>));
	fft_west(size, yy, retbuffer);
	free(yy);
	
	for (j=0;j<(0.5*n+1);j++) rbuffer[j]=retbuffer[j];
	//y[n]=y[1];
	//y[1]=sum;
	
	for (j=3;j<((0.5*n+1)/2);j+=2){
		sum += imag(rbuffer[j]);
		rbuffer[j] = complex<double> (real(rbuffer[j]),sum);
	}

	free(retbuffer);
}	
