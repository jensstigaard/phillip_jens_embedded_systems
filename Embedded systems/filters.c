#include <stdio.h>
#include <stdlib.h>
#include "filters.h"
#include "switchArray.h"

void insertRawDatapoint(int datapoint);
void runLowPassFilter();
void runHighPassFilter();
void runDerivFilter();
void runSquared();
int runMWIFilter();

static int lowPassArray[13] = {0,0,0,0,0,0,0,0,0,0,
							   0,0,0};
static int lowPassIndex = 0;

static int highPassArray[33] = {0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,
								0,0,0};

static int highPassIndex = 0;

static int derivativeArray[5] = {0,0,0,0,0};

static int derivativeIndex = 0;

static int toBeSquared = 0;

static int MWIArrayIndex = 0;

static int MWIArray[30] = {0,0,0,0,0,0,0,0,0,0,
						   0,0,0,0,0,0,0,0,0,0,
						   0,0,0,0,0,0,0,0,0,0};
static int MWISum = 0;
static int MWIMinus = 0;


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

	lowPassIndex++;
	highPassIndex++;
	derivativeIndex++;
	MWIArrayIndex++;
}

void insertRawDatapoint(int datapoint){

	if(lowPassIndex >= 13){
		lowPassIndex = 0;
	}
	//switchArray(lowPassArray,13);
	lowPassArray[lowPassIndex] = datapoint;

}

void runLowPassFilter(){

	if(highPassIndex >= 33){
			highPassIndex = 0;
		}

	int y_1 = highPassIndex - 1, y_2 = highPassIndex - 2, x = lowPassIndex, x_6 = lowPassIndex - 6, x_12 = lowPassIndex - 12;

	if(y_1 < 0){
		y_1 = y_1 + 33;
	}
	if(y_2 < 0){
		y_2 = y_2 + 33;
	}

	if(x_6 < 0){
		x_6 = x_6 + 13;
	}
	if(x_12 < 0){
		x_12 = x_12 + 13;
	}

	//switchArray(highPassArray,33);
	highPassArray[highPassIndex] = 2 * highPassArray[y_1] - highPassArray[y_2] + ((lowPassArray[x] - 2 * lowPassArray[x_6] + lowPassArray[x_12])/32);
	//printf("%i\n",highPassArray[highPassIndex]);
}

void runHighPassFilter(){
	if(derivativeIndex >= 5){
		derivativeIndex = 0;
	}

	int y_1 = derivativeIndex - 1, x = highPassIndex, x_16 = highPassIndex - 16, x_17 = highPassIndex - 17, x_32 = highPassIndex - 32;

	if(y_1 < 0){
		y_1 = y_1 + 5;
	}
	if(x_16 < 0){
		x_16 = x_16 + 33;
	}

	if(x_17 < 0){
		x_17 = x_17 + 33;
	}

	if(x_32 < 0){
		x_32 = x_32 + 33;
	}

	//switchArray(derivativeArray,5);
	derivativeArray[derivativeIndex] = derivativeArray[y_1] - (highPassArray[x]/32) + highPassArray[x_16] - highPassArray[x_17] + (highPassArray[x_32]/32);
	//printf("%i\n",derivativeArray[derivativeIndex]);
}

void runDerivFilter(){

	int x = derivativeIndex, x_1 = derivativeIndex - 1, x_3 = derivativeIndex - 3, x_4 = derivativeIndex - 4;

	if(x_1 < 0){
		x_1 = x_1 + 5;
	}
	if(x_3 < 0){
		x_3 = x_3 + 5;
	}

	if(x_4 < 0){
		x_4 = x_4 + 5;
	}

	toBeSquared = ((2 * derivativeArray[x]) + derivativeArray[x_1] - derivativeArray[x_3] - (2 * derivativeArray[x_4]))/8;
	//printf("%i\n",toBeSquared);
}

void runSquared(){

	if(MWIArrayIndex >= 30){
		MWIArrayIndex = 0;
	}

	//switchArray(MWIArray,30);
	MWIMinus = MWIArray[MWIArrayIndex];
	MWIArray[MWIArrayIndex] = toBeSquared * toBeSquared;

}

int runMWIFilter(){

	MWISum = MWISum - MWIMinus + MWIArray[MWIArrayIndex];

	return MWISum/30;

}


