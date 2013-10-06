#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <complex>

#include <fftwest.hh>

using namespace std;	
/*! \fn  get_array_lenght (double *arr, const int size)
 * \brief The function found the highest closest number to the size of the array 
 * \param size is the size of the array 
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
 * \brief This function un arreglo mas grande con uno mas pequeño y ceros en los espacios sobrantes 
 * \param  arr_in el arreglo que entra mas pequeño 
 * arr_out el arreglo grande que sale de la funcion y size el tamaño del arreglo pequeño.
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
/*! \fn  cosft (double *y, complex<double> *rbuffer, const int size){
 * \brief This function es la encargada de realizar la transformada de cosenos la cual esta dada por la ecuacion f_j = \sum_{k=0}^{n-1} x_k \cos \left[\frac{\pi}{n} j \left(k+\frac{1}{2}\right) \right] 
 * \param "size" is the size of the array, "*y" es el puntero con el vector que ingresa el cual debe ser de un tamaño potencia de dos,rbuffer es el vector donde se va a debolver el arreglo solo se nesecita el espacio en memoria.
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
