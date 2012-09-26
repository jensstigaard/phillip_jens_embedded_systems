#include <stdio.h>
#include <stdlib.h>
#include "peak.h"

void findRPeaks();

static int datapoints[3] = {0,0,0};

static int peaks[200];

static int RPeaks[8] = {0,0,0,0,0,0,0,0};
static int peakCounter = 0;
static int threshold1 = 2000;
static int threshold2 = 1000;
static int NPKF = 1000;
static int SPKF = 4500;
static int timePast = 0;

void findAllPeaks(int datapoint){

	timePast++;

	datapoints[2] = datapoints[1];
	datapoints[1] = datapoints[0];
	datapoints[0] = datapoint;

	if(datapoints[1] > datapoints[2] && datapoints[1] > datapoints[0]){

		addPeakToPeaks();
		findRPeaks();

	}

}

void findRPeaks(){

	if(datapoints[1] > threshold1){


		int i = 7;
		while(i > 0){
			RPeaks[i] = RPeaks[i - 1];
			i--;
		}
		RPeaks[0] = datapoints[1];
		printf("RR: %i\n",timePast);
		printf("R-Peaks: %i\n",datapoints[1]);
		printf("Threshold: %i\n\n",threshold1);

		timePast = 0;

	}else{

		NPKF = 0.125*datapoints[1]+0.875*NPKF;
		threshold1 = NPKF + 0.25*(SPKF-NPKF);
		threshold2 = 0.5*threshold1;

	}

}


