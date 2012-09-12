#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

int lowPass(int datapoint, int fixedDatapoints[]);
int highPass(int datapoint, int fixedDatapoints[]);
int derivative(int datapoint, int fixedDatapoints[]);
int squaring(int datapoint, int fixedDatapoints[]);

int runFilters(int datapoint, int fixedDatapoints[]){

	int tempDatapoint = 0;

	tempDatapoint = lowPass( datapoint, fixedDatapoints[]);
	tempDatapoint = highPass( tempdatapoint, fixedDatapoints[]);
	tempDatapoint = derivative( datapoint, fixedDatapoints[]);
	tempDatapoint = squaring( datapoint);

	return tempDatapoint;

}

int lowPass(int datapoint, int fixedDatapoints[]){


}

int highPass(int datapoint, int fixedDatapoints[]){



}

int derivative(int datapoint, int fixedDatapoints[]){



}

int squaring(int datapoint){
	return datapoint*datapoint;
}
