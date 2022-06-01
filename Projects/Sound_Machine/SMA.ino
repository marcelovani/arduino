/**
   Calculate the simple moving average of an array. A new array is returned with the average
   of each range of elements. A range will only be calculated when it contains enough elements to fill the range.

   sma([1, 2, 3, 4, 5, 6, 7, 8, 9], 4);
   //=> [ '2.50', '3.50', '4.50', '5.50', '6.50', '7.50' ]
   //=>   │       │       │       │       │       └─(6+7+8+9)/4
   //=>   │       │       │       │       └─(5+6+7+8)/4
   //=>   │       │       │       └─(4+5+6+7)/4
   //=>   │       │       └─(3+4+5+6)/4
   //=>   │       └─(2+3+4+5)/4
   //=>   └─(1+2+3+4)/4

   * Range parameter cannot be greater than number of samples.
*/
int smaData[20] = {}; // Storage SMA calculations
int sma = 0;

bool isMoving = false;

bool SMAMoving() {
  return isMoving;
}

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

short int avg = 0;
short int prevAvg = 0;
  
/*
   Calculates the simple moving average
*/
void calcSma() {
  if (knobsMoving()) {
    // Divert logic to display knobs
    //return;
  }

  int * data = getAccelerationData();
  short int s = getSamples();
  short int r = getRange();
  // Make sure range is not bigger than number of samples.
  if (r > s) {
    r = s;
  }
  short int sum = 0;


  // Start from total of samples minus the range.
  // i.e. Samples=9, Range=3
  // 1, 2, 3, 4, 5, 6, 7, 8, 9
  //                   ^  ^  ^
  short int i = s - r;
  while (i < s) {
    sum += data[i];
    i++;
  }
  avg = sum / r;

  // Clear noise
  int diff = abs(prevAvg - avg); //@todo we need to map all values from accelerometer data and knobs to the screen height, this way we normalize the data and it will be easier to compare diff
  prevAvg = avg;

  int threshold = map(getThreshold(), 0, 1023, 0, r);
  if (diff > threshold) {
    // Push to the end of the array
    isMoving = true;
    pushSmaData(avg);
  }
  else {
    isMoving = false;
  }
  
//  Serial.print("isMoving:"); Serial.print(isMoving); Serial.print(" ");
//  Serial.print("Thre:");     Serial.print(threshold); Serial.print(" ");
//  Serial.print("Diff:");     Serial.print(diff); Serial.print(" ");
//  Serial.print("Avg:");     Serial.print(avg + getCalibrationX()); Serial.print("\t");
}

// Push to the end of the array
void pushSmaData(int value) {
  short int s = getSamples();
  short int i = 0;
  while (i < s) {
    // Move from bottom to top.
    smaData[i] = smaData[i + 1];
    i++;
  }
  // Set bottom value.
  sma = value;
  smaData[s - 1] = sma;
}

// Algorithm to detect changes and take actions
short int firstUp = -1;
short int peak = 0;
short int diff = 0;
short int playSound = 0;
short int perc = 0;

short int getPerc() {
  return perc;
}

void calcPerc(short int curr, int offset) {
  perc = abs((curr - getCalibrationX()) * 100 / offset);
}

void detectChange() {
  short int s = getSamples();
  int offset = getThreshold() + getCalibrationX();
  //int offset = map(getThreshold(), 0, 1023, 0, 100);
  // Get samples from begining, middle and end of data.
  short int prev = smaData[0] + getCalibrationX();
  short int curr = smaData[s / 2] + getCalibrationX();
  short int next = smaData[s - 1] + getCalibrationX();

  if (curr > prev) {
    // Perc is used to display LEDs and to calculate the volume.
    //perc = 0; // @todo broken. Calculate percentage based on peak value.
    //diff = abs(curr - offset);
    //perc = diff / offset * 100;

    // Going up
    if (firstUp == -1) {
      firstUp = curr;
      peak = curr;
      // @todo only reset playSound after few seconds since last play.
      playSound = 0;
      ledOff();
    }

    // Detect peak
    if (curr > next) {
      //if (curr >= offset) {
        peak = curr;
      //}
    }
  }
  else if (peak > curr && curr > offset) {
    // Going down.
    if (playSound == 0 && isPlaying() == false) {
      calcPerc(curr, offset);
      ledOn();
      peak = curr;
      // Play sound
      setVolume(perc);
      play();
      firstUp = -1;
      playSound = 1;
    }
//    else {
//      peak = next;
//    }
  }
  calcPerc(curr, offset);

  Serial.print("Offset:");     Serial.print(offset); Serial.print(" ");
//  Serial.print("SMA:");  Serial.print(getSma());  Serial.print(" ");
  //Serial.print("Diff:"); Serial.print(diff);      Serial.print(" ");
  //Serial.print("Offset:"); Serial.print(offset); Serial.print(" ");
//  Serial.print("S / 2:");  Serial.print(s / 2);  Serial.print(" ");
//  Serial.print("Prev:");  Serial.print(prev);  Serial.print(" ");
  Serial.print("Curr:");  Serial.print(curr);  Serial.print(" ");
//  Serial.print("Next:");  Serial.print(next);  Serial.print(" ");
  Serial.print("Peak:");  Serial.print(peak);  Serial.print(" ");
  //Serial.print("Perc:"); Serial.print(perc);      Serial.print("\t");

  ledBar(perc);
}
