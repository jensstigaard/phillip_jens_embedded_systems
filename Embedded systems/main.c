#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include <windows.h>

static const char filename[] = "ECG.txt";

void shiftArray(int data_points_raw[], int data_points_filtered[]) {

	int i;

	for (i = 31; i > 0; i--) {
		data_points_raw[i] = (int) data_points_raw[i - 1];
		data_points_filtered[i] = (int) data_points_filtered[i - 1];
	}
}

void insertNewDataPoint(int current_point_raw, int current_point_filtered,
		int * data_points_raw[], int * data_points_filtered[]) {

	// shift data in array 1 field to the right
	shiftArray(&data_points_raw, &data_points_filtered);

	data_points_raw[0] = current_point_raw;
	data_points_filtered[0] = current_point_filtered;
}

int main() {

	int currentPoint = 0;
	int currentPointFiltered = 0;
	int filteredDatapoints[32];
	int rawDatapoints[32];

	int i;
	for (i = 0; i < 32; i++) {
		filteredDatapoints[i] = 0;
		rawDatapoints[i] = 0;
	}

	FILE *file = fopen(filename, "r");

	i = 0;
	while (getNextData(file, &currentPoint) != EOF && i<10) {

		// Calculate the filtered data
		currentPointFiltered = runFilters(currentPoint, rawDatapoints,
				filteredDatapoints);

		printf("Current point raw: %i\n", currentPoint);
		printf("Current point filtered: %i\n", currentPointFiltered);

		// Inserts the new data point in the first field in both the arrays
		insertNewDataPoint(currentPoint, currentPointFiltered, &rawDatapoints,
				&filteredDatapoints);

		printf("\n");
			int ii;
			for (ii = 0; ii < 32; ii++) {
					printf("%i\t", rawDatapoints[ii]);
				}
			printf("\n");

		i++;

	}

	return 0;

}
