//if file is not in the same directory of the executable then fname
// should include PATH

 /*************** DECODER FUNCTIONS *****************/

//Returns the total number of samples. Equals to array size.
int samples_number(const char *fname);

//Total time of sound. In seconds
double total_time(const char *fname);

//Returns the sample rate of the sound. Commonly 44.1 Khz
double samples_rate(const char *fname);

//Decode the sound into an array.
long decode(const char *fname, double *buffer, int smpls_num);


  /*************** ENCODER FUNCTIONS ******************/

// Creates a sound file from a float *inbuffer array
void encoder(const char *outfilename, double *inbuffer, int smpls_num, double smpls_rate);
