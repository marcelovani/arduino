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
*/
int smaData[20] = {}; // Storage SMA calculations
int sma = 0;

bool isMoving = false;

bool SMAMoving() {
  Serial.print(isMoving);
  Serial.print("\t");
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

/*
   Calculates the simple moving average
*/
void calcSma() {
  if (knobsMoving()) {
    // Divert logic to display knobs
    return;
  }

  int * data = getAccelerationData();
  short int s = getSamples();
  short int r = getRange();
  short int sum = 0;
  short int avg = 0;

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
  int diff = data[i] - data[i - 1]; //@todo we need to map all values from accelerometer data and knobs to the screen height, this way we normalize the data and it will be easier to compare diff
  int threshold;
  threshold = map(getThreshold(), 0, 1023, 0, 30);
  Serial.print(threshold);
  Serial.print("% \t diff ");
  Serial.print(diff);
  Serial.print("\t");
  if (diff < (threshold * -1) || diff > threshold) {
    // Push to the end of the array
    isMoving = true;
    pushSmaData(avg);
  }
  else {
    isMoving = false;
  }
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

void detectChange() {
  short int s = getSamples();
  int threshold = getThreshold();
  short int prev = smaData[s - 3] + getCalibrationX();
  short int curr = smaData[s - 2] + getCalibrationX();
  short int next = smaData[s - 1] + getCalibrationX();

  if (curr > prev) {
    // Perc is used to display LEDs and to calculate the volume.
    perc = 0;
    diff = curr - threshold;
    if (diff > 0) {
      perc = diff / threshold * 100;
    }

    // Going up
    if (firstUp == -1) {
      firstUp = curr;
      // @todo only reset playSound after few seconds since last play.
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
      // Play sound
      setVolume(perc);
      play();
      ledOn();
      firstUp = -1;
      playSound = 1;
    }
    peak = next;
  }

  Serial.print(getSma());
  Serial.print(",");
  Serial.print(perc);
  Serial.print(",");

  ledBar(perc);
}
