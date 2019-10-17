/*
 * Calculates the simple moving average
 */
//#include <Statistic.h>

//Statistic smaStats;
int smaData[100] = {}; // Storage SMA calculations
int sma = 0;

// Return the current SMA.
int getSma()
{
  return sma;
}

// Return the full data set.
int * getSmaData()
{
  return smaData;
}

/**
 * Calculate the simple moving average of an array. A new array is returned with the average
 * of each range of elements. A range will only be calculated when it contains enough elements to fill the range.
 *
 * sma([1, 2, 3, 4, 5, 6, 7, 8, 9], 4);
 * //=> [ '2.50', '3.50', '4.50', '5.50', '6.50', '7.50' ]
 * //=>   │       │       │       │       │       └─(6+7+8+9)/4
 * //=>   │       │       │       │       └─(5+6+7+8)/4
 * //=>   │       │       │       └─(4+5+6+7)/4
 * //=>   │       │       └─(3+4+5+6)/4
 * //=>   │       └─(2+3+4+5)/4
 * //=>   └─(1+2+3+4)/4
 */
void calcSma() {
  int * data = getAccelerationData();
  int s = getSamples();
  int r = getRange();

  int sum = 0;
  int avg = 0;

  // Start from total of samples minus the range.
  // i.e. Samples=9, Range=3
  // 1, 2, 3, 4, 5, 6, 7, 8, 9
  //                   ^  ^  ^
  int i = s - r;
  while(i < s) {
    int val = data[i];
    sum += val;
    i++;
  }
  avg = sum / r;

//  char buff[6];
//  sprintf(buff, "%3d", avg);
//  Serial.print(String("AVG: ") + buff);

  // Push to the end of the array
  pushSmaData(avg);    
}

// Push to the end of the array
void pushSmaData(int value) {
    int s = getSamples();
    int i = 0;
    while (i < s) {
      // Move from bottom to top.
      smaData[i] = smaData[i+1];
      i++;
    }
    // Set bottom value.
    sma = value;
    smaData[s-1] = sma;
}

// Algorithm to detect changes and take actions
short int firstUp = -9999;
short int peak = 0;
float perc = 0;
short int diff = 0;
short int playSound = 0;

void detectChange() {
  short int s = getSamples();
	float threshold = getThreshold();

  short int prev = smaData[s-3];
  short int curr = smaData[s-2];
  short int next = smaData[s-1];

  String playLabel = "";

	if (curr > prev) {
    // Perc is used to display LEDs and to calculate the volume.
    perc = 0;
    diff = curr - threshold;
    if (diff > 0) {
      perc = diff / threshold * 100;
    }

		// Going up
		if (firstUp == -9999) {
			firstUp = curr;
			playSound = 0;
      ledOff();
		}

		// Detect peak
		if (curr > next) {
			if (curr >= threshold) {
				peak = curr;
			}
		}
	}
	else if (curr > threshold && peak > curr) {
		// Going down.
		if (playSound == 0 && isPlaying() == false) {
      //@todo check if DFP is not playing
      playLabel = "PLAY";
      
			// Play sound
      play();
			playSound = 1;
      ledOn();
			firstUp = -9999;
		}
		peak = next;
	}

  Serial.print(getSma());
  Serial.print(",");
  Serial.print(perc);
  Serial.print(",");

//  char buff[6];
//  sprintf(buff, "%3d", peak);
//  Serial.print(String("\tPeak: ") + buff);
//
//  sprintf(buff, "%3d", diff);
//  Serial.print(String("\tDiff: ") + buff);
//  
//  Serial.print("\tPerc: ");
//  Serial.print(perc);
  //Serial.print("%");
  
  ledBar();
//  Serial.print("\t" + playLabel);

}
