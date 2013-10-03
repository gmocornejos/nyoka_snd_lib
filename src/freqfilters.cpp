#define PI 3.141592654

void lowpass(int smpls_num, int smpls_rate, double *buffer, double *lowbuff, double freq){
	double dt = (double)1/smpls_rate;
	double alpha = 2*PI*freq*dt;
	double factor = alpha/(1+alpha);
	for(int i = 1; i < smpls_num; i++){
		lowbuff[i] = factor*buffer[i] + (1-factor)*lowbuff[i-1];
	}
}

void highpass(int smpls_num, int smpls_rate, double *buffer, double *highbuff, double freq){
	double dt = (double)1/smpls_rate;
	double alpha = 2*PI*freq*dt;
	double factor = 1/(1+alpha);
	for(int i = 1; i < smpls_num; i++){
		highbuff[i] = factor*highbuff[i-1] + factor*(buffer[i] - buffer[i-1]);
	}
}

void bandpass(int smpls_num, int smpls_rate, double *buffer, double *bandbuff, double lowfreq, double highfreq){
	lowpass(smpls_num, smpls_rate, buffer, bandbuff, lowfreq);
	highpass(smpls_num, smpls_rate, buffer, bandbuff, highfreq);
}

