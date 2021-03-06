#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include "peak.h"
#include <windows.h>
#include <time.h>

static const char filename[] = "ECG.txt";

int main() {

	int currentPoint = 0;
	int i = 0;



	FILE *file = fopen(filename, "r");

	while (getNextData(file, &currentPoint) != EOF) {


		// Calculate the filtered data
	    runFilters(&currentPoint);

		//printf("%i\n", currentPoint);

	    findAllPeaks(currentPoint);

		i++;

	}

	return 0;

}
