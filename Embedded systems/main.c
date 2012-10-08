#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include "peak.h"
#include <windows.h>
#include <time.h>

static const char filename[] = "ECG.txt";

int main() {

	clock_t start, end;
	double cpu_time_used;
	int currentPoint = 0;
	int i = 0;

	FILE *file = fopen(filename, "r");

	start = clock();

	while (getNextData(file, &currentPoint) != EOF) {

		//printf("RawPoint: %i\n",currentPoint);

		// Calculate the filtered data
	    runFilters(&currentPoint);

		//printf("%i\n", currentPoint);

	    findAllPeaks(currentPoint);

		i++;

	}

	end = clock();

	cpu_time_used =((double) (end - start)) / CLOCKS_PER_SEC;

	printf("%d",cpu_time_used);

	return 0;

}
