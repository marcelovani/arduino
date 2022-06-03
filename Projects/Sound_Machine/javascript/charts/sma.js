'use strict';

// Display simple moving average chart
function showSMAChart(dataPoints, range) {
	var smaPoints = detectChange(dataPoints, range);
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

function getCalibrationX() {
	return 0;
}

function calcPerc(curr, offset) {
	return Math.abs((curr - getCalibrationX()) * 100 / offset);
}

function detectChange(data, range) {
	var tmp = [];
	var smaData = [];
	var smaPoints = [];
	var peak = 0;
	var perc = 0;
	var playSound = 0;
	var firstUp = null;
	var label = '';
	var offset = threshold;

	for (var i = 0; i < data.length; i++) {
		tmp[i] = data[i].y;
	}

	var smaData = sma(tmp, range);
	var samples = data.length;

	for (i = 0; i < samples; i++) {
		var prev = smaData[i - 2];
		var curr = smaData[i];
		var next = smaData[i + 1];

		var markers = setMarkers(0, 'circle', '', '');

		// Detect change.
		if (curr > prev) {
			// Going up
			if (firstUp == null) {
				firstUp = curr;
				peak = curr;
				playSound = 0;
			}

			label = '^';
			// // Perc is used to display LEDs and to calculate the volume.
			// if (curr >= offset) {
			// 	var diff = curr - offset;
			// 	perc = Math.floor(diff / offset * 100);
			// 	label = perc + '%';
			// }
			// markers = setMarkers(curr, 'circle', '#00AA00', label);

			// Detect peak
			if (curr > next) {
				peak = curr;
				// markers = setMarkers(curr, 'triangle', '#00FF00', perc + '%');
			}
		}
		else if (curr == prev) {
			// Cruising.
			// markers = setMarkers(curr, 'circle', '#00AA00', '>');
		}
		else if (peak > curr && curr > offset) {
			// Going down.
			if (playSound == 0) {
				perc = calcPerc(curr, offset);
				// markers = setMarkers(curr, 'triangle', '#0000FF', perc + '%');
				markers = setMarkers(curr, 'circle', '#00FF00', 'S ' + curr);
				peak = curr;

				// Play sound
				playSound = 1;

				firstUp = null;
			}
			else {
				// markers = setMarkers(curr, 'cross', '#FF0000', '-');
			}
		}
		perc = calcPerc(curr, offset);

    	smaPoints.push({ 
            x: data[i].x,
            y: parseFloat(smaData[i]),
            // indexLabel: markers.indexLabel,
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
			markerSize: 6
		}
	}
	else {
		return {
			markerType: null,
			markerColor: null,
			indexLabel: null,
			markerSize: 1
		}
	}
}
