#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <complex>

using namespace std;
/*! \fn pitch_filter(int smpls_num, int smpls_rate, double *inbuffer, double percent, double increment)
 * \brief The function receives a pointer to real array   and with their generates a graphyc respect to time.
 * \param   *buffer: is  a pointer towards the array whit the decoded song .
 * \param   smpls_read: is the number of  samples read .   
 * \param   smpls_rate: is the number of samples per second.
 */

void plot_time(double *buffer, int smpls_read, double smpls_rate){
        ofstream textfile;
        textfile.open("outputdata.txt");
        for(int i = 0; i < smpls_read; i++){
                textfile << ((double)i/smpls_rate) << " " << buffer[i] << "\n";
        }
        textfile.close();

        cout << "Press ENTER to close the program \n";
        system("gnuplot ../plotscripts/plot_time.sh");
}

/*! \fn pitch_filter(int smpls_num, int smpls_rate, double *inbuffer, double percent, double increment)
 * \brief The function  receives a pointer towards an array of complex numbers and with their generates a graphhyc respect to the frequency.
 * \param *buffer: is  a pointer towards the array whit the decoded song .
 * \param  smpls_read: is the number of  samples read .   
 * \param  smpls_rate: is the number of samples per second.
 */
void plot_freq(complex<double> *buffer, int smpls_read, double smpls_rate){
        ofstream textfile;
        textfile.open("outputdata.txt");
        double max = 0; int pos;
        for(int i = 0; i < smpls_read/2; i++){
                textfile << ((double) i*smpls_rate/smpls_read) << " " << abs(buffer[i]) << "\n";
                if(abs(buffer[i]) > max){
                        max = abs(buffer[i]);
                        pos = i;
                }
        }
        textfile.close();
        cout << "fundamental frequency " << (double) pos*smpls_rate/smpls_read << "\n";
        cout << "Press ENTER to close the program \n";
        system("gnuplot ../plotscripts/plot_freq.sh");
}
