#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
/*! \fn whitenoise(int smpls_num, double* buffer)
 * \brief The function fill a pointer with aleatoriis random numbers which when they join the song they can be seen like noisy.
 * \param  : *buffer is a pointer towards an array where is going to return the ramdon numbers.
 * \param  : smpls_num is the number of total samples and is equal to size of buffer.
 */
void whitenoise(int smpls_num, double* buffer){
	srand(time(NULL));
	double sign, ran, sum;
	double cons = (double) 1/sqrt(2*3.141592654);
	for(int i = 0; i < smpls_num; i++){
		sign = (double) (rand()%100)/100;
		ran = (double) (rand()%100)/100;
		if(sign <= 0.5){
			buffer[i] = ran*-1;
		}else{
			buffer[i] = ran;
		}
	}
}
