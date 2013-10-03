#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <complex>

using namespace std;

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
