#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

int lowPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int highPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int derivative(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int squaring(int datapoint, int filteredDatapoints[], int rawDatapoints[]);

int runFilters(int datapoint, int filteredDatapoints[], int rawDatapoints[]){



	lowPass(&datapoint, filteredDatapoints, rawDatapoints);
	highPass(&datapoint, filteredDatapoints, rawDatapoints);
	derivative(&datapoint, filteredDatapoints, rawDatapoints);
	squaring(&datapoint);

	return datapoint;

}

void lowPass(int* datapoint, int filteredDatapoints[], int rawDatapoints[]){

	datapoint = 2*filteredDatapoints[0] - filteredDatapoints[1] + (datapoint - 2*rawDatapoints[5]+rawDatapoints[11])/32;

}

void highPass(int* datapoint, int filteredDatapoints[], int rawDatapoints[]){

	datapoint = filteredDatapoints[0] - datapoint/32 + rawDatapoints[15] - rawDatapoints[16] + (rawDatapoints[31]/32);

}

void derivative(int* datapoint, int filteredDatapoints[], int rawDatapoints[]){



}

void squaring(int* datapoint){

	datapoint = datapoint * datapoint;

}
