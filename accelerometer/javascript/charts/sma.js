'use strict';

// Display simple moving average chart
function showSMAChart(dataPoints, samples) {
	var smaPoints = calcSMA(dataPoints, samples);
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
	    title: {
	         text: "Simple moving average",
	    },
	    data: [{
	         type: "line",
	         dataPoints: smaPoints
	      }]
    });
    chart.render();
}

function calcSMA(data, samples) {
	var tmp = [];
	var smaData = [];
	var smaPoints = [];
	for (var i = 0; i < data.length; i++) {
		tmp[i] = data[i].y;
	}
	var smaData = sma(tmp, samples);
	for (i = 0; i < data.length; i++) {
    	smaPoints.push({ 
            x: data[i].x,
            y: parseFloat(smaData[i])
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
