#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <complex>

#define PI 3.141592654
#define FORWARD 1
#define BACKWARD -1;

using namespace std;

 /*!
  *  \fn bits_length(int n)
 * \brief Calculates the necessary bits to store the array indexes
 * \param n: is number tells how many bits (binary digits) are required to store that number in decimal
  *  
  *  **/
int bits_length(int n){
        int i;
        for(i = 0; n > 1; i++){
                n = n/2;
        }
        return (i+1);
}

  /*! 
 * \fn bitrev(int num, int bitslength).
 * \brief The function attenuates only the highest frequencies to a determinated frequency in a wave.
 * \param  bitslength: the number of bits.
 * \param  num:is the number you are looking for the bit reverse.

**/
int bitrev(int num, int bitslength){
        int i, nrev, N;
        N = 1 << bitslength;
        nrev = num;

        for(i = 1; i < bitslength; i++){
                num >>= 1;
                nrev <<= 1;
                nrev |= num & 1;
        }
        nrev &= N-1;
        return nrev;
}

  /*!
 * \fn  next_pow_2(int size)
 *\brief calculates the next power of two .
 *\param size : is the large of the array .
 **/
int next_pow_2(int size){
	int i = 2;
	while(i < size){
		i = i*2;
	}
	return i;
}

 /*!
 * \fn fft(int smpls_read, double *buffer, complex<double> *transformed).
 * \brief The function calculated the fast fourier transform
 * \details FFT requires the array length to be a power of two. The input array contains N complex samples, with real and imaginary part alternating, so the number of samples must be 	multiplied by two
 * \param  *buffer: is  a pointer towards the array whit the decoded song .
 * \param  smpls_num: is the number of total samples read.
 * \param  *transformed: is  a pointer towards the array complex where send the result of the transform.
  **/
 
	
void fft(int smpls_read, double *buffer, complex<double> *transformed){


	int fft_buff_len = next_pow_2(smpls_read*2);
	// Creates a buffer to store the data
	double *fft_buff = (double*) malloc(fft_buff_len*sizeof(double));
	//initializes the array
	for(int i = 0; i < fft_buff_len/2; i++){
		fft_buff[2*i] = 0;
		fft_buff[2*i +1] = 0;
		if(i < smpls_read){
			fft_buff[2*i] = buffer[i];
		}
	}
	free(buffer);

	/*** FFT first step. Bit-reversal section ***/
	// We are interested in necessary bits to describe the last entry index
	int bits_len = bits_length(fft_buff_len-1);
	for(int i = 0; i < fft_buff_len/2; i++){
		int j = bitrev(i, bits_len);
		if(j > i){
			swap(fft_buff[2*i], fft_buff[j]);
			swap(fft_buff[2*i+1], fft_buff[j+1]);
		}
	}

	/*** FFT second step. Danielson lanczos.  ***/
	int sign = FORWARD;
	for(int stage = 1; stage <= log2(fft_buff_len); stage++){
		int boxlength = pow(2,stage);
		int num_of_boxes = fft_buff_len/boxlength;
		for(int j = 0; j < num_of_boxes; j++){
			int boxpos = 0;
			for(int i = boxlength*j; boxpos < boxlength/2; i += 2){
				int ipair = i + boxlength/2;

				// complex sinoids
				double c = cos(PI*boxpos/fft_buff_len);
				double s = sin(PI*boxpos/fft_buff_len)*sign;

				// this is W^k times the second number
				double tmpreal = fft_buff[ipair]*c - fft_buff[ipair+1]*s;
				double tmpimag = fft_buff[ipair]*s + fft_buff[ipair +1]*c;

				//Here comes the butterfly!
				fft_buff[ipair] = fft_buff[i] - tmpreal;
				fft_buff[ipair +1] = fft_buff[i+1] - tmpimag;
				fft_buff[i] = fft_buff[i] + tmpreal;
				fft_buff[i+1] = fft_buff[i+1] - tmpimag;

				boxpos += 2;
			}
		}
	} // FFT ends here!

	// Distributes fft_buffer in a complex array.
	// the rest of the library works this way
	for(int i = 0; i < smpls_read; i++){
		transformed[i] = (complex<double>) (fft_buff[2*i], fft_buff[2*i +1]);
	}
	free(fft_buff);

}
