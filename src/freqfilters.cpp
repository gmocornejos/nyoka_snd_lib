#define PI 3.141592654
/*! \fn lowpass(int smpls_num, int smpls_rate, double *buffer, double *lowbuff, double freq)
 * \brief The function attenuates only the highest frequencies to a determinated frequency in a wave
 * \param  *buffer is  a pointer towards the array whit the decoded song .
 * \param  *lowbuff is a pointer towards an array where is going to send the attenuated frequencies.
 * \param  freq is the is the maximun unattenuated frequency.
 * \param  smpls_num is the number of total samples.
 * \param  smpls_rate is the number of samples per second.
 */
void lowpass(int smpls_num, int smpls_rate, double *buffer, double *lowbuff, double freq){
	double dt = (double)1/smpls_rate;
	double alpha = 2*PI*freq*dt;
	double factor = alpha/(1+alpha);
	for(int i = 1; i < smpls_num; i++){
		lowbuff[i] = factor*buffer[i] + (1-factor)*lowbuff[i-1];
	}
}
/*! \fn highpass(int smpls_num, int smpls_rate, double *buffer, double *highbuff, double freq)
 * \brief The function attenuates only the lowest frequencies to a determinated frequency in a wave
 * \param   *buffer is  a pointer towards the array whit the decoded song .
 * \param   *highbuff is a pointer towards an array where is going to send the attenuated frequencies.
 * \param   freq is the is the minimun unattenuated frequency.
 * \param   smpls_num es el tamaño del array buffer
 * \param   smpls_rate is the number of samples per second.
 */
void highpass(int smpls_num, int smpls_rate, double *buffer, double *highbuff, double freq){
	double dt = (double)1/smpls_rate;
	double alpha = 2*PI*freq*dt;
	double factor = 1/(1+alpha);
	for(int i = 1; i < smpls_num; i++){
		highbuff[i] = factor*highbuff[i-1] + factor*(buffer[i] - buffer[i-1]);
	}
}
/*! \fn bandpass(int smpls_num, int smpls_rate, double *buffer, double *bandbuff, double lowfreq, double highfreq)
 * \brief The function in charge of attenuated frequecies outside of a given rack in a wave.
 * \param smpls_num is the number of total samples.
 * \param smpls_rate is the number of samples per second.
 * \param *buffer is  a pointer towards the array whit the decoded song .
 * \param *bandbuff is a pointer towards an array where is going to send the attenuated frequencies.
 * \param lowfreq  is the is the minimun unattenuated frequency.
 * \param highfreq  is the is the maximun unattenuated frequency.
  */
 
void bandpass(int smpls_num, int smpls_rate, double *buffer, double *bandbuff, double lowfreq, double highfreq){
	lowpass(smpls_num, smpls_rate, buffer, bandbuff, lowfreq);
	highpass(smpls_num, smpls_rate, buffer, bandbuff, highfreq);
}

