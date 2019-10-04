'use strict';

// Display acceleration chart
function showAccelerationChart(dataPoints) {
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
   		theme: "light2", // "light1", "light2", "dark1", "dark2"
   		animationEnabled: false,
	    title: {
	         text: "Acceleration",
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
	         dataPoints: dataPoints
	      }]
    });
    chart.render();
}
