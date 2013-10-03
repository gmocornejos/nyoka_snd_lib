#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>	

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

void four1(double *data, const int n, const int isign) {
	int nn,mmax,m,j,istep,i;
	double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
	if (n<2 || n&(n-1)) throw("n must be power of 2 in four1");
	nn = n << 1;
	j = 1;
	for (i=1;i<nn;i+=2) {
		if (j > i) {
			std::swap(data[j-1],data[i-1]);
			std::swap(data[j],data[i]);
		}
		m=n;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;	
	}
	mmax=2;
	while (nn > mmax) {
		istep=mmax << 1;
		theta=isign*(6.2830/mmax);
		wtemp=sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi=sin(theta);
		wr=1.0;
		wi=0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=nn;i+=istep) {
				j=i+mmax;
				tempr=wr*data[j-1]-wi*data[j];
				tempi=wr*data[j]+wi*data[j-1];
				data[j-1]=data[i-1]-tempr;
				data[j]=data[i]-tempi;
				data[i-1] += tempr;
				data[i] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
	mmax=istep;
	}
}

void realft(double *data, const int size) {
	int i,i1,i2,i3,i4,n=size;
	double c1=0.5,c2=0.5,h1r,h1i,h2r,h2i,wr,wi,wpr,wpi,wtemp;
	double theta=-3.1415/double(n>>1); 

	wtemp=sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi=sin(theta);
	wr=1.0+wpr;
	wi=wpi;
	
	std::cout << "antes del for de realft "  << "\n";
	for (i=1;i<(n>>2);i++) {
		i2=1+(i1=i+i);
		i4=1+(i3=n-i1);
		h1r=c1*(data[i1]+data[i3]);
		h1i=c1*(data[i2]-data[i4]);
		h2r= -c2*(data[i2]+data[i4]);
		h2i=c2*(data[i1]-data[i3]);
		data[i1]=h1r+wr*h2r-wi*h2i;
		data[i2]=h1i+wr*h2i+wi*h2r;
		data[i3]=h1r-wr*h2r+wi*h2i;
		data[i4]= -h1i+wr*h2i+wi*h2r;
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
	}
	data[0] = (h1r=data[0])+data[1];
	data[1] = h1r-data[1];
}

void cosft (double *y, const int size){
	std::cout << "entro a cosft "  << "\n";
	const double PI=3.1415;
	int j,n=size-1;
	double sum,y1,y2,theta,wi=0.0,wpi,wpr,wr=1.0,wtemp;
	std::cout << "aqui? "  << "\n";
	double *yy = (double*)malloc(n*sizeof(double));
	//double yy[n];
	theta=PI/n;
	wtemp=sin(0.5*theta);
	wpr	= -2.0*wtemp*wtemp;
	wpi=sin(theta);
	sum=0.5*(y[0]-y[n]);
	yy[0]=0.5*(y[0]+y[n]);
	
	std::cout << "antes del for "  << "\n";
	for (j=1;j<n/2;j++) {
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
		y1=0.5*(y[j]+y[n-j]);
		y2=(y[j]-y[n-j]);
		yy[j]=y1-wi*y2;
		yy[n-j]=y1+wi*y2;
		sum += wr*y2;
	}
	std::cout << "antes de fourier "  << "\n";
	yy[n/2]=y[n/2];
	std::cout << "fijo "  << "\n";
	realft(yy,size);
	
	for (j=0;j<n;j++) y[j]=yy[j];
	y[n]=y[1];
	y[1]=sum;
	
	for (j=3;j<n;j+=2) {
		sum += y[j];
		y[j]=sum;
	}
	free(yy);
}	
