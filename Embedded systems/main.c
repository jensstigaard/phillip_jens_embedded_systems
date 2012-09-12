#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include <windows.h>

static const char filename[] = "ECG.txt";

int main() {

	int currentPoint = 0;
	int filteredDatapoints [32];
	int rawDatapoints [32];

	for(int i = 0; i <32; i++){
		filteredDatapoints[i] = 0;
		rawDatapoints[i] = 0;
	}

	FILE *file = fopen(filename, "r");

	while(getNextData(file, &currentPoint) != EOF){

		printf("%i\n", currentPoint);



	}

	return 0;

}
