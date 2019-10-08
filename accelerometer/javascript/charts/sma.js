'use strict';

// Display simple moving average chart
function showSMAChart(dataPoints, samples) {
	var smaPoints = calcSMA(dataPoints, samples);
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
   		theme: "light2", // "light1", "light2", "dark1", "dark2"
   		animationEnabled: false,
	    title: {
	         text: "Simple moving average",
	    },
    	axisY: {
			title: "Acceleration",
			suffix: "g"
		},
    	axisX: {
			title: "Time",
			suffix: "s"
		},
	    data: [{
	         type: "spline",
	         markerSize: 7,
	         dataPoints: smaPoints,
	      }]
    });
    chart.render();
}

function calcSMA(data, samples) {
	var tmp = [];
	var smaData = [];
	var smaPoints = [];
	var peak = 0;
	var perc = 0;
	var playSound = 0;
	var firstUp = null;
	var label = '';
	for (var i = 0; i < data.length; i++) {
		tmp[i] = data[i].y;
	}
	var smaData = sma(tmp, samples);
	for (i = 0; i < data.length; i++) {

		var curr = smaData[i];
		var markers = setMarkers(curr, 'circle', '', '');

		// Detect change.
		if (i > 0) {
			var prev = smaData[i-1];
			if (i < data.length) {
				var next = smaData[i+1];
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
            y: parseFloat(smaData[i]),
            indexLabel: markers.indexLabel,
            markerType: markers.markerType,
            markerColor: markers.markerColor,
            markerSize: markers.markerSize,
        });
	}
	return smaPoints;
}

// Set graph markers.
function setMarkers(val, markerType, markerColor, indexLabel) {
	// Set the markers only if the value is > threshold.
	if (val >= threshold) {
		return {
			markerType: markerType,
			markerColor: markerColor,
			indexLabel: indexLabel,
			markerSize: 10
		}
	}
	else {
		return {
			markerType: null,
			markerColor: null,
			indexLabel: null,
			markerSize: 5
		}
	}
}
