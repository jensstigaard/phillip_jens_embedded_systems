#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

void insertRawDatapoint(int datapoint);
void runLowPassFilter();
void runHighPassFilter();
void runDerivFilter();
void runSquared();
int runMWIFilter();

static int lowPassArray[13] = {0,0,0,0,0,0,0,0,0,0,
							   0,0,0};

static int highPassArray[33] = {0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,
								0,0,0};

static int derivativeArray[5] = {0,0,0,0,0};

static int toBeSquared = 0;

static int MWIArray[30] = {0,0,0,0,0,0,0,0,0,0,
						   0,0,0,0,0,0,0,0,0,0,
						   0,0,0,0,0,0,0,0,0,0};

void runFilters(int *datapoint) {

	//insert new datapoint into the array needed for low-Pass-filter

	insertRawDatapoint(*datapoint);

	//perform the low-pass-filter
	// and insert the new datapoint into the array needed for high-Pass-filter

	runLowPassFilter();

	//perform the high-pass-filter
	// and insert the new datapoint into the array needed for derivative-filter

	runHighPassFilter();

	//perform the derivative filter
	// and find the number to be squared

	runDerivFilter();

	//Square the number and insert it into the MWI Array

	runSquared();

	//Run The final filter:

	*datapoint = runMWIFilter();

}

void insertRawDatapoint(int datapoint){

	int i = 12;
	while(i > 0){
		lowPassArray[i] = lowPassArray[i - 1];
		i--;
	}
	lowPassArray[0] = datapoint;

}

void runLowPassFilter(){

	int i = 32;
	while(i > 0){
		highPassArray[i] = highPassArray[i - 1];
		i--;
	}
	highPassArray[0] = 2 * highPassArray[1] - highPassArray[2] + ((lowPassArray[0] - 2 * lowPassArray[6] + lowPassArray[12])/32);

}

void runHighPassFilter(){

	int i = 4;
	while(i > 0){
		derivativeArray[i] = derivativeArray[i - 1];
		i--;
	}
	derivativeArray[0] = derivativeArray[1] - (highPassArray[0]/32) + highPassArray[16] - highPassArray[17] + (highPassArray[32]/32);

}

void runDerivFilter(){

	toBeSquared = (2 * derivativeArray[0] + derivativeArray[1] - derivativeArray[3] - 2 * derivativeArray[4])/8;

}

void runSquared(){

	int i = 30;
	while(i > 0){
		MWIArray[i] = MWIArray[i - 1];
		i--;
	}
	MWIArray[0] = toBeSquared * toBeSquared;

}

int runMWIFilter(){

	int temp = 0;

	int i = 0;

	while(i < 30){

		temp = temp + MWIArray[i];

		i++;
	}

	return temp/30;

}



/* To Print Arrays Copy Pasta:
    printf("\n\n");
	i = 0;
	while(i < 13){
		printf("%i,",lowPassArray[i]);
		i++;
	}
*/

