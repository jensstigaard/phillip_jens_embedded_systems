#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

int lowPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int highPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int derivative(int datapoint, int filteredDatapoints[], int rawDatapoints[]);
int squaring(int datapoint);

int runFilters(int datapoint, int rawDatapoints[], int filteredDatapoints[]) {

	int tempPoint = 0;

	tempPoint = lowPass(datapoint, filteredDatapoints, rawDatapoints);
	printf("\n\nLow:%i\n", tempPoint);
	tempPoint = highPass(tempPoint, filteredDatapoints, rawDatapoints);
	printf("High:%i\n", tempPoint);
	tempPoint = derivative(tempPoint, filteredDatapoints, rawDatapoints);
	printf("Deriv:%i\n", tempPoint);
	tempPoint = squaring(tempPoint);
	printf("Square:%i\n", tempPoint);

	return tempPoint;

}

int lowPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]) {

	return 2 * filteredDatapoints[0] - filteredDatapoints[1]
			+ (datapoint - 2 * rawDatapoints[5] + rawDatapoints[11]) / 32;

}

int highPass(int datapoint, int filteredDatapoints[], int rawDatapoints[]) {

	return filteredDatapoints[0] - datapoint / 32 + rawDatapoints[15]
			- rawDatapoints[16] + (rawDatapoints[31] / 32);
}

int derivative(int datapoint, int filteredDatapoints[], int rawDatapoints[]) {

	return (2 * datapoint + rawDatapoints[0] - rawDatapoints[2]
			- 2 * rawDatapoints[3]) / 8;

}

int squaring(int datapoint) {

	return datapoint * datapoint;

}
