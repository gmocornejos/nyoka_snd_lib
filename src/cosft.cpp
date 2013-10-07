#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <complex>

#include <fftwest.hh>

using namespace std;	
/*! \fn  get_array_lenght (double *arr, const int size)
 * \brief The function found the number poewr of two, highest and closest to the size of the array.  
 * \param "size" is the size of the array 
 * \return number result: Is the number power of two closest and bigger than size  .
 */
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
/*! \fn  complete_arr (double *arr_in, double *arr_out, const int size)
 * \brief This function fill an array power of two with other smaller or equal array and with zeros in extra spaces  
 * \param : "*arr_in" is a pointer  towards the smallest array with which will fill the biggest array. 
 * \param : "*arr_out" is a pointer towards the biggest array where is goint to get out the smaller array one time that is complete with the zeros.
 * \param : "size" is the size of the smaller array .
 */
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
/*! \fn  cosft (double *y, complex<double> *rbuffer, const int size)
 * \brief  :Is the function in charge to realize the cosine transform the one that you can obtain with  equation  f_j = \sum_{k=0}^{n-1} x_k \cos \left[\frac{\pi}{n} j \left(k+\frac{1}{2}\right) \right] 
 * \param : "size" is the size of the array.
 * \param : "*y" is a pointer towards an array that has to be of a size power of two.
 * \param : "*rbuffer" is a pointer towards an array where is going to return the cosine transform into other array of complex numbers.
  */
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
	
	cout << "antes de aplicar fourier " << "\n";

	complex<double> *retbuffer = (complex<double>*) malloc((0.5*n+1)*sizeof(complex<double>));
	fft_west(size, yy, retbuffer);
	free(yy);
	cout << "despues de aplicar fourier " << "\n";
	
	for (j=0;j<(0.5*n+1);j++) rbuffer[j]=retbuffer[j];
	//y[n]=y[1];
	//y[1]=sum;
	
	for (j=3;j<((0.5*n+1)/2);j+=2){
		sum += imag(rbuffer[j]);
		rbuffer[j] = complex<double> (real(rbuffer[j]),sum);
	}

	free(retbuffer);
}	
