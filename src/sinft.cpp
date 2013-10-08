#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <complex>

#include <fftwest.hh>

using namespace std;	

/*! \fn  get_array_lenght (double *arr, const int size)
 * \brief The function found the highest closest number to the size of the array 
 * \param size : is the size of the array 
 * \return number result: Is the number power of two closest and bigger than size  .
 */

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
 /*! \fn  complete_arr (double *arr_in, double *arr_out, const int size)
 * \brief This function fill an array power of two with other smaller or equal array and with zeros in extra spaces
 * \details It is equivalent to the imaginary parts of a DFT of roughly twice the length, is a linear and invertible function  
 * \param  *arr_in: is a pointer  towards the smallest array with which will fill the biggest array. 
 * \param  *arr_out: is a pointer towards the biggest array where is goint to get out the smaller array one time that is complete with the zeros.
 * \param  size: is the size of the smaller array .
 */
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

/*! \fn  sinft (double *y, complex<double> *rbuffer, const int size)
 * \brief    Is the function in charge to realize the sine transform the one that you can obtain with  equatio F_k = \sum_{j=1}^{N-1}f_j sin(\pi  j k/N)  
 * \param  size: is the size of the array.
 * \param  *y: is a pointer towards an array that has to be of a size power of two.
 * \param  *rbuffer: is a pointer towards an array where is going to return the cosine transform into other array of complex numbers.
 */
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
	fft_west(size, y, rbuffer);//do the fast fourier transform
	
	rbuffer[0] = complex<double> (0.5*real(rbuffer[j]),0);

	for (j=0;j<(n-1)/2;j+=2) {
		sum += imag(rbuffer[j]);
		rbuffer[j] = complex<double> (imag(rbuffer[j]),sum);
	}
}
