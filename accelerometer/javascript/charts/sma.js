'use strict';

// Display simple moving average chart
function showSMAChart(dataPoints, samples) {
	var smaPoints = calcSMA(dataPoints, samples);
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
   		theme: "light2", // "light1", "light2", "dark1", "dark2"
   		animationEnabled: true,
	    title: {
	         text: "Simple moving average",
	    },
	    data: [{
	         type: "line",
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
	for (var i = 0; i < data.length; i++) {
		tmp[i] = data[i].y;
	}
	var smaData = sma(tmp, samples);
	for (i = 0; i < data.length; i++) {

		var curr = smaData[i];

		// Detect change
		if (i > 0) {
			var prev = smaData[i-1];
			if (i < data.length) {
				var next = smaData[i+1];
			}

			if (curr > prev) {
				// Going up
				if (typeof firstUp == 'undefined') {
					var firstUp = curr;
				}
				var indexLabel = '^';
				var markerType = 'circle';
				var markerColor = '#6B8E23';

				// Detect peak
				if (curr > next) {
					peak = curr;
					var indexLabel = peak;
					var markerType = 'triangle';
					var markerColor = '#00ff00';
				}
			}
			else if (curr == prev) {
				// Dont do anything
			}
			else {
				// Going down
				var diff = peak - firstUp;
				var perc = diff * 100 / peak;
				//var indexLabel = Math.round(perc) + '%';

				// if perc > threshold {
				//	var indexLabel = 'Shhh';
				//}
				var indexLabel = '';
				var markerType = 'cross';
				var markerColor = '#ff0000';
				peak = next;
				//peak = 0;
			}
		}
		else {
			// Initialize peak
			peak = curr;
		}

    	smaPoints.push({ 
            x: data[i].x,
            y: parseFloat(smaData[i]),
            indexLabel: indexLabel,
            markerType: markerType,
            markerColor: markerColor
        });
	}
	return smaPoints;
}

function simple_moving_averager(period) {
    var nums = [];
    return function(num) {
        nums.push(num);
        if (nums.length > period)
            nums.splice(0,1);  // remove the first element of the array
        var sum = 0;
        for (var i in nums)
            sum += nums[i];
        var n = period;
        if (nums.length < period)
            n = nums.length;
        return(sum/n);
    }
}

function calcSMA2(data, samples) {
	var sma = simple_moving_averager(samples);
	var tmp = [];
	var smaData = [];
	var smaPoints = [];
	for (i = 0; i < data.length; i++) {
		tmp[i] = data[i].y;
	}
	for (var i in tmp) {
	    var n = tmp[i];
	  	smaPoints.push({ 
            x: data[i].x,
            y: parseFloat(sma[n])
        });
	}
	return smaPoints;
}
