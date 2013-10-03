#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <complex>

#include <fftwest.hh>

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

void sinft (double *y, complex<double> *rbuffer, const int size){
	int j,n=size;
	double sum,y1,y2,theta,wi=0.0,wr=1.0,wpi,wpr,wtemp;
	theta=3.1415/double(n);
	
	wtemp=sin(0.5*theta);
	wpr= -2.0*wtemp*wtemp;
	wpi=sin(theta);
	y[0]=0.0;
	
	for (j=1;j<(n>>1)+1;j++) {
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
		y1=wi*(y[j]+y[n-j]);
		y2=0.5*(y[j]-y[n-j]);
		y[j]=y1+y2;
		y[n-j]=y1-y2;
	}
	//complex<double> *retbuffer = (complex<double>*) malloc((0.5*n+1)*sizeof(complex<double>));
	fft_west(size, y, rbuffer);
	
	rbuffer[0] = complex<double> (0.5*real(rbuffer[j]),0);

	for (j=0;j<(n-1)/2;j+=2) {
		sum += imag(rbuffer[j]);
		rbuffer[j] = complex<double> (imag(rbuffer[j]),sum);
	}
}
