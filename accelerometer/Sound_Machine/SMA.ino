/*
 * Calculates the simple moving average
 */
#include <Statistic.h>

Statistic smaStats;
int smaData[100] = {}; // Storage SMA calculations

int * getSma()
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
  int t = getRange(); // Total rename to samples
  int r = 4; // Range @todo make configurable
  
  float sum = 0;
  //float avg = 0;

  // Update stats.
  int i = 0;
  while(i < t) {
    //if (data[i] != 0) {

      // Calcumlate SMA for the range
      sum = 0;
      int s = 0;
      while(s < r) {
        int pos = i + r - s - 1;
        //Serial.print(pos);
        //Serial.print(", ");
        sum += data[pos];
        s++;
      }
      smaData[i] = sum / r;

      //sum = data[i + r - 1] + data[i + r - 2] + data[i + r - 3] + data[i + r - 4];
//      avg = sum / r;
//      Serial.print(data[i]);
//      Serial.print(", ");
//      Serial.print(smaData[i]);
//      Serial.println(", ");
//      Serial.println(avg);
    //}
    i++; 
  }
//  Serial.print(smaData[r-1]);
//  Serial.print(", ");
}

// Algorithm to detect changes and take actions
void detectChange() {
//calcSma();//temp

  int r = 10;//getRange(); //temp
	int threshold = getThreshold();
 
 //threshold = 8;//temp

  String label = "";
	short int peak = 0;
	short int perc = 0;
	short int curr = 0;
	short int prev = 0;
	short int next = 0;
	short int diff = 0;
	short int playSound = 0;
	short int firstUp = -9999;
  short int i=0;
//  Serial.println(" ");
//  Serial.println("Detect change");
  while(i <= r) {
    //delay(10);
    curr = smaData[i];

//    Serial.print("Curr: ");
    Serial.print(curr);
    Serial.print(",");

		// Detect change.
		if (i > 0) {
			prev = smaData[i-1];
			if (i < r) {
				next = smaData[i+1];
			}

			if (curr > prev) {
				// Going up
				if (firstUp == -9999) {
					firstUp = curr;
					playSound = 0;
          ledOff();
				}

				// Perc is used to display LEDs and to calculate the volume.
				if (curr >= threshold) {
					diff = curr - threshold;
					perc = diff / threshold * 100;
					label = perc + '%';
          //Serial.print("Perc: ");
          //Serial.println(perc);
          //Serial.print(",");
          //Serial.println('%');
				}
        else {
          //Serial.println('^');
        }

				// Detect peak
				if (curr > next) {
					if (curr >= threshold) {
						peak = curr;
            //Serial.print("Peak: ");
						//Serial.println(peak);
					}
				}
			}
			else if (curr == prev) {
				// Sliding.
        //Serial.println(">");
			}
			else {
				// Going down.
				if (playSound == 0) {
          //Serial.println("PLAY");

					// Play sound
					playSound = 1;
          ledOn();

					firstUp = -9999;;
				}
				else {
          //Serial.println("-");
				}
				peak = next;
			}
		}
		else {
			// Initialize peak
			peak = curr;
		}

    i++; 
    ledBar();
  }
}
