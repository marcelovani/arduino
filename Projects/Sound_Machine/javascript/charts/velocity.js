'use strict';

// Display velocity chart
function showVelocityChart(velocityPoints) {
	var divId = cloneElement('chartContainer');
   	var chart = new CanvasJS.Chart(divId, {
   		theme: "light2", // "light1", "light2", "dark1", "dark2"
   		animationEnabled: false,
	    title: {
	         text: "Velocity",
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
	         dataPoints: velocityPoints
	      }]
    });
    chart.render();
}

// Calculate velocity
function calcVelocity(data) {
	var velocityPoints = [];
	var velocity = 0;
	for (var i = 2; i < data.length -1; i++)
	{
		var prevAcc = data[i-1].y;
		var curAcc = data[i].y;
		var time = data[i].x;
		var prevTime = data[i-1].x;
		velocity += (prevAcc + curAcc) / 2 * (time - prevTime);
    	velocityPoints.push({ 
            x: time,
            y: velocity
        });
	}

    return velocityPoints;
}
