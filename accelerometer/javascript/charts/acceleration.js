'use strict';

// Display acceleration chart
function showAccelerationChart(dataPoints) {
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
	    title: {
	         text: "Acceleration",
	    },
	    data: [{
	         type: "line",
	         dataPoints: dataPoints
	      }]
    });
    chart.render();
}
