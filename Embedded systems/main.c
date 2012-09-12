#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include <windows.h>

static const char filename[] = "ECG.txt";


void shiftArray(int * data_points_raw[], int * data_points_filtered){

	for(int i=30; i>=0; i--){
		data_points_raw[i+1] 		= data_points_raw[i];
		data_points_filtered[i+1]	= data_points_filtered[i];
	}
}

void insertNewDataPoint(int current_point_raw, int current_point_filtered, int * data_points_raw[], int * data_points_filtered){
	data_points_raw[0] = current_point_raw;
	data_points_filtered[0] = current_point_filtered;
}

int main() {

	int currentPoint = 0;
	int currentPointFiltered = 0;
	int filteredDatapoints [32];
	int rawDatapoints [32];

	for(int i = 0; i <32; i++){
		filteredDatapoints[i] = 0;
		rawDatapoints[i] = 0;
	}

	FILE *file = fopen(filename, "r");

	while(getNextData(file, &currentPoint) != EOF){

		// Calculate the filtered data
		currentPointFiltered = filterPoint(currentPoint, rawDatapoints, filteredDatapoints);

		// shift data in array 1 field to the right
		shiftArray(&rawDatapoints, &filteredDatapoints);

		// Inserts the new data point in the first field in both the arrays
		insertNewDataPoint(currentPoint, currentPointFiltered, &rawDatapoints, &filteredDatapoints);

		printf("%i\n", currentPoint);
	}

	return 0;

}
