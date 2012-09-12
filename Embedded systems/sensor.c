#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(FILE* file, int* currentPoint){

	return fscanf(file, "%i", currentPoint);
}

