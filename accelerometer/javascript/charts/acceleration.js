'use strict';

// Display acceleration chart
function showAccelerationChart(dataPoints) {
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
   		theme: "light2", // "light1", "light2", "dark1", "dark2"
   		animationEnabled: true,
	    title: {
	         text: "Acceleration",
	    },
    	axisX: {
			interval: 1,
			intervalType: "s"
		},
		axisY:{
			title: "Acceleration"
		},
	    data: [{
	         type: "line",
	         dataPoints: dataPoints
	      }]
    });
    chart.render();
}
