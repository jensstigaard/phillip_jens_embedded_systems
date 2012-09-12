#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include <windows.h>

static const char filename[] = "ECG.txt";

int main() {

	int currentPoint = 0;

	FILE *file = fopen(filename, "r");

	while(getNextData(file, &currentPoint) != EOF){

		printf("%i\n", currentPoint);

	}

	return 0;

}
