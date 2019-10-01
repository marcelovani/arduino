'use strict';

// Count cloned elements.
var clonedElements = 0;

// Creates clones of elements
function cloneElement(id) {
	var div = document.getElementById(id),
    clone = div.cloneNode(true);
    clonedElements++;
	clone.id = id + '-' + clonedElements;
	clone.style.display = "block";
	document.body.appendChild(clone);

	return clone.id;
}

// Detect a drop after it reached the peak
function detectChange(data) {
	var prevAcc = 0;
	var prevTime = 0;
	var velocity = 0;
	var peak = 0;
	var prevPeak = 0;
	var peakLess5Perc = 0;
	var perc = 0;
	var threshold = 5; // % this will be a potenciometer
	console.log('Threshold ' + threshold + '%');
	for (var i = 0; i < data.length; i++)
	{
		var curAcc = data[i].y; // Read Acc X
		var time = data[i].x; // millis()
		velocity += (prevAcc + curAcc) / 2 * (time - prevTime);

		// Going up
		if (velocity > peak) {
			peak = velocity;
			var peakLess5Perc = peak - peak * threshold / 100;
		}

		// Going down
		var vp =  peak -  velocity;
		if (peak > 0 && vp > peakLess5Perc) {
			var boom = 1;
		}

		// Detect drop
		var speedVariation = (velocity - peak) * perc;
		if (peak > speedVariation) {
			if (perc > threshold) {
				// Trigger sound
				console.log('Time ' + time);
				console.log('Peak ' + peak);
				console.log('Velocity ' + velocity);
				console.log('Calc perc ' + perc + '%');
				console.log(' ');



				// Reset peak;
				//peak = velocity;
			}
		}
		// Store highest peak;
		prevPeak = peak;

		prevTime = time;
		prevAcc = curAcc;
	}
}