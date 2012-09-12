#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

void lowPass(int * datapoint, int filteredDatapoints[], int rawDatapoints[]);
void highPass(int * datapoint, int filteredDatapoints[], int rawDatapoints[]);
void derivative(int * datapoint, int filteredDatapoints[], int rawDatapoints[]);
void squaring(int * datapoint);

int runFilters(int datapoint, int filteredDatapoints[], int rawDatapoints[]){

	lowPass(&datapoint, filteredDatapoints, rawDatapoints);
	highPass(&datapoint, filteredDatapoints, rawDatapoints);
	derivative(&datapoint, filteredDatapoints, rawDatapoints);
	squaring(&datapoint);

	return datapoint;

}

void lowPass(int* datapoint, int filteredDatapoints[], int rawDatapoints[]){

	datapoint = 2 * filteredDatapoints[0] - filteredDatapoints[1] + ((int) datapoint - 2*rawDatapoints[5]+rawDatapoints[11])/32;

}

void highPass(int* datapoint, int filteredDatapoints[], int rawDatapoints[]){

	datapoint = filteredDatapoints[0] - (int)datapoint/32 + rawDatapoints[15] - rawDatapoints[16] + (rawDatapoints[31]/32);

}

void derivative(int* datapoint, int filteredDatapoints[], int rawDatapoints[]){



}

void squaring(int* datapoint){

	datapoint = (int)datapoint * (int)datapoint;

}
