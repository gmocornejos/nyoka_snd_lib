#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

int get_array_lenght (float *arr, const int size) {	
	int n,array_lenght=0;
	for (n=2; 3<4; n++) {
		if(pow(2, n) >= size){
			array_lenght = pow(2, n);
			break;
		}	
	}
	return array_lenght;
}

void complete_arr (float *arr_in, float *arr_out, const int size) {
	int array_lenght = get_array_lenght(arr_in, size);
	
	for (int c=0; c<array_lenght; c++) {
		if(c<size){
			arr_out[c]= arr_in[c];
		}	
		else{
			arr_out[c]= 0;
		}
	}	
} 

/*int main(int argc, char *argv[]){
	float arr[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7, 8};
	
	int size= (sizeof(arr)/sizeof(arr[0]));
	std::cout << "size of array: " << size <<std::endl;
	
	int array_lenght = get_array_lenght(arr, size);
	std::cout << "size of completed array: " << array_lenght <<std::endl;
	
	float* completed_array = (float*)malloc(array_lenght*sizeof(float));
	
	complete_arr(arr, completed_array, size);
	
	for (int i=0; i<array_lenght; i++){
		std::cout << completed_array[i] <<std::endl;
	}
	
	return 0;
	free(completed_array);
}*/
