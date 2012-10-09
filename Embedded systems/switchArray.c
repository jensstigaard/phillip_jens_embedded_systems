#include "switchArray.h"

void switchArray(int array[], int length){

	int i = length - 1;
	while(i > 0){
		array[i] = array[i - 1];
		i--;
	}

}
