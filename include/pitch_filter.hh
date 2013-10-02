/*** This function turns to zero all the unpitched samples
This overwrites the buffer ***/

// Recommended values: percent ~0.1 increment ~.45
void pitch_filter(int smpls_num, int smpls_rate, double *buffer, double percent, double increment);
