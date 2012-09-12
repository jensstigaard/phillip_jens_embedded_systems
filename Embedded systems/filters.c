#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

int lowPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int highPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int derivative(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int squaring(int datapoint);

int runFilters(int datapoint, int filteredDatapoints[], int rawDatapoints[]){


	int tempPoint = 0;

	tempPoint = lowPass(datapoint, filteredDatapoints, rawDatapoints);
	tempPoint= highPass(tempPoint, filteredDatapoints, rawDatapoints);
	tempPoint = derivative(tempPoint, filteredDatapoints, rawDatapoints);
	tempPoint = squaring(tempPoint);

	return tempPoint;

}

int lowPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]){

	return 2 * filteredDatapoints[0] - filteredDatapoints[1] + (datapoint - 2*rawDatapoints[5]+rawDatapoints[11])/32;

}

int highPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]){

	return filteredDatapoints[0] - datapoint/32 + rawDatapoints[15] - rawDatapoints[16] + (rawDatapoints[31]/32);
}

int derivative(int datapoint, int filteredDatapoints[], int rawDatapoints[]){

	return (2 * datapoint+rawDatapoints[1]-rawDatapoints[3]- 2 * rawDatapoints[4])/8;

}

int squaring(int datapoint){

	return datapoint * datapoint;

}
