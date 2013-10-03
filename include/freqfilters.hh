void lowpass(int smpls_num, int smpls_rate, double *buffer, double *lowbuff, double freq);

void highpass(int smpls_num, int smpls_rate, double *buffer, double *highbuff, double freq);

void bandpass(int smpls_num, int smpls_rate, double *buffer, double *bandbuff, double lowfreq, double highfreq);
