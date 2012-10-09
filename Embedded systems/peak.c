#include <stdio.h>
#include <stdlib.h>
#include "switchArray.h"
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

static Peak peaks[50];
static Peak peak;

static Peak RPeaks[50];

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


		//switchArray(peaks,50);
		int i = 49;
		while(i > 0){
			peaks[i] = peaks[i - 1];
			i--;
		}

		peaks[0] = peak;
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

	currentRR = peaks[0].time - RPeaks[0].time;
	if(RR_Low < currentRR && currentRR < RR_High){

		storeRPeak();

		SPKF = ((125*peak.hight)/1000)+((875*SPKF)/1000);

		switchArray(RecentRR,8);

		RecentRR[0] = currentRR;

		switchArray(RecentRR_OK,8);

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

	while(peaks[0].hight <= threshold2){
		i++;
	}

	peak = peaks[i];

	storeRPeak();

	SPKF = ((125*peak.hight)/1000)+((875*SPKF)/1000);

	currentRR = RPeaks[0].time - RPeaks[1].time;



	switchArray(RecentRR,8);

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

		int i = 49;
		while(i > 0){
			RPeaks[i] = RPeaks[i - 1];
			i--;
		}

		//switchArray(RPeaks,50);
		RPeaks[0] = peak;

		printf("Latest R-Peak value:%i\n",peak.hight);
		printf("Latest R-Peak occurrence:%i\n",peak.time);
		printf("Pulse:%i\n\n",currentRR);

	}

}

