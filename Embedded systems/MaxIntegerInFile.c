/*
 * MaxIntegerInFile.c
 *
 *  Created on: 05/09/2012
 *      Author: Jens
 */

#include <stdio.h>

static const char filename[] = "ECG.txt";

int main() {
	int max;
	int i1;
	int success;

	FILE *file = fopen(filename, "r");

	fscanf(file, "%i", &i1);

	max = i1;

	do {
		success = fscanf(file, "%i", &i1);

		if (i1 > max) {
			max = i1;
		}

	} while (success != EOF);

	printf("Max found: %i", max);

	return 0;
}

