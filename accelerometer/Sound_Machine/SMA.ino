/*
 * Calculates the simple moving average
 */
#include <Statistic.h>

Statistic smaStats;
int smaData[100]; // Storage SMA calculations

int getSma()
{
  return smaData[0];
}

// Calculate the simple moving accelaration
int calcSma() {
  int * data = getAccelerationData();
  int r = getRange();
  smaStats.clear();

  // Update stats.
  int i=0;
  while(i < r) {
    smaStats.add(data[i]);
    i++; 
  }

  return smaStats.average();
}

// Algorithm to detect changes and take actions
void detectChange() {
  int r = getRange();
  smaData[0] = calcSma();
/*
	var data = [];
	var smaPoints = [];
	var peak = 0;
	var perc = 0;
	var playSound = 0;
	var firstUp = null;
	var label = '';

	var data = calcSma();
	for (i = 0; i < data.length; i++) {

		var curr = data[i];
		var markers = setMarkers(curr, 'circle', '', '');

		// Detect change.
		if (i > 0) {
			var prev = data[i-1];
			if (i < data.length) {
				var next = data[i+1];
			}

			if (curr > prev) {
				// Going up
				if (firstUp == null) {
					var firstUp = curr;
					playSound = 0;
				}

				label = '^';
				// Perc is used to display LEDs and to calculate the volume.
				if (curr >= threshold) {
					var diff = curr - threshold;
					perc = Math.floor(diff / threshold * 100);
					label = perc + '%';
				}
				markers = setMarkers(curr, 'circle', '#00AA00', label);

				// Detect peak
				if (curr > next) {
					if (curr >= threshold) {
						peak = curr;
						markers = setMarkers(curr, 'triangle', '#00FF00', perc + '%');
					}
				}
			}
			else if (curr == prev) {
				// Sliding.
				markers = setMarkers(curr, 'circle', '#00AA00', '>');
			}
			else {
				// Going down.
				if (playSound == 0) {
					markers = setMarkers(curr, 'circle', '#0000FF', 'S ' + curr);

					// Play sound
					playSound = 1;

					firstUp = null;
				}
				else {
					markers = setMarkers(curr, 'cross', '#FF0000', '-');
				}
				peak = next;
			}
		}
		else {
			// Initialize peak
			peak = curr;
		}

    	smaPoints.push({ 
            x: data[i].x,
            y: parseFloat(data[i]),
            indexLabel: markers.indexLabel,
            markerType: markers.markerType,
            markerColor: markers.markerColor,
            markerSize: markers.markerSize,
        });
	}
	return smaPoints;
 */
}
