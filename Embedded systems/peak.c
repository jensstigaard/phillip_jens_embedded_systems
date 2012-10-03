#include <stdio.h>
#include <stdlib.h>
#include "peak.h"

void findRPeaks();
void RRCalcultaions();
void searchBack();
void storeRPeak();

typedef struct{
	int time;
	int hight;
} Peak;

static int datapoints[3] = {0,0,0};

static Peak peaks[200];
static int peaksIndex = 0;
static Peak peak;

static int peakCounter = 0;

static Peak RPeaks[200];
static int RPeaksIndex = 0;

static int RecentRR[8] = {150,150,150,150,150,150,150,150};
static int RecentRR_OK[8] = {150,150,150,150,150,150,150,150};
static int RR_Average1 = 0;
static int RR_Average2 = 0;

static int RR_Low = 100;
static int RR_High = 200;
static int RR_Miss = 250;

static int threshold1 = 2000;
static int threshold2 = 1000;
static int NPKF = 1000;
static int SPKF = 2000;
static int currentRR = 0;
static int timePast = 0;

void findAllPeaks(int datapoint){

	timePast++;

	datapoints[2] = datapoints[1];
	datapoints[1] = datapoints[0];
	datapoints[0] = datapoint;

	if(datapoints[1] > datapoints[2] && datapoints[1] > datapoints[0]){

		peak.hight = datapoints[1];
		peak.time = timePast;

		peaks[peaksIndex] = peak;
		peaksIndex++;
		findRPeaks();

	}

}

void findRPeaks(){

	if(peak.hight > threshold1){
		RRCalcultaions();
	}else{
		NPKF = ((125*peak.hight)/1000)+((875*NPKF)/1000);
		threshold1 = NPKF + (SPKF-NPKF)/4;
		threshold2 = threshold1/2;
	}

}

void RRCalcultaions(){

	if(RPeaksIndex > 1){
		currentRR = peaks[peaksIndex-1].time - RPeaks[RPeaksIndex-1].time;
	}else{
		currentRR = 150;
	}


	if(RR_Low < currentRR && currentRR < RR_High){

		storeRPeak();

		SPKF = ((125*peak.hight)/1000)+((875*SPKF)/1000);

		int i = 8;
		while(i > 0){
			RecentRR[i] = RecentRR[i - 1];
			i--;
		}
		RecentRR[0] = currentRR;

		i = 8;
		while(i > 0){
			RecentRR_OK[i] = RecentRR_OK[i - 1];
			i--;
		}
		RecentRR_OK[0] = currentRR;

		RR_Average1 = (RecentRR[0] + RecentRR[1] + RecentRR[2] + RecentRR[3] + RecentRR[4] + RecentRR[5] + RecentRR[6] + RecentRR[7])/8;
		RR_Average2 = (RecentRR_OK[0] + RecentRR_OK[1] + RecentRR_OK[2] + RecentRR_OK[3] + RecentRR_OK[4] + RecentRR_OK[5] + RecentRR_OK[6] + RecentRR_OK[7])/8;

		RR_Low = (920*RR_Average2)/1000;
		RR_High = (1160*RR_Average2)/1000;
		RR_Miss = (1660*RR_Average2)/1000;

		threshold1 = NPKF + (SPKF-NPKF)/4;
		threshold2 = threshold1/2;

	} else {

		if(currentRR > RR_Miss){
			searchBack();
		}

	}
}

void searchBack(){

	int i = 1;

	while(peaks[peaksIndex-i].hight <= threshold2){
		i++;
	}

	peak = peaks[peaksIndex-i];

	storeRPeak();

	SPKF = ((125*peak.hight)/1000)+((875*SPKF)/1000);

	if(RPeaksIndex > 1){
			currentRR = RPeaks[peaksIndex-1].time - RPeaks[RPeaksIndex-2].time;
		}else{
			currentRR = 150;
		}


	int j = 8;
	while(j > 0){
	RecentRR[j] = RecentRR[j - 1];
			j--;
		}
	RecentRR[0] = currentRR;
	RR_Average1 = (RecentRR[0] + RecentRR[1] + RecentRR[2] + RecentRR[3] + RecentRR[4] + RecentRR[5] + RecentRR[6] + RecentRR[7])/8;
	RR_Low = (920*RR_Average1)/1000;
	RR_High = (1160*RR_Average1)/1000;
	RR_Miss = (1660*RR_Average1)/1000;
	threshold1 = NPKF + (SPKF-NPKF)/4;
	threshold2 = threshold1/2;



}

void storeRPeak(){

	if(currentRR > 100){
		RPeaks[RPeaksIndex] = peak;
		RPeaksIndex++;

		printf("Latest R-Peak value:%i\n",peak.hight);
		printf("Latest R-Peak occurrence:%i\n",peak.time);
		printf("Pulse:%i\n\n",currentRR);

	}

}

void printRPeaks(){

	int i = 0;
	while(i < RPeaksIndex){

		printf("RPeak-High:%i\nRPeak-Time:%i\nRR:%i\n\n",RPeaks[i].hight,RPeaks[i].time,RPeaks[i].time-RPeaks[i-1].time);

		i++;
	}
	printf("%i",i);

}
