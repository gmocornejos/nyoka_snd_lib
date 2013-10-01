#include <complex>

void fft_west(int smpls_num, double *buffer, std::complex<double> *retbuffer);

void ifft_west(int smpls_num, std::complex<double> *buffer, double *retbuffer);
