'use strict';

// Read csv and populate data
function getDataPointsFromCSV(csv) {
	var time = 0;
	var prevTime = 0;
	var accTime = 0;
	var offsetTime = -1;
	var acceleration = 0;
    var dataPoints = [];
    var csvLines = [];
    var points = [];
    csvLines = csv.split(/[\r?\n|\r|\n]+/);         
        
    for (var i = 0; i < csvLines.length; i++) {
        if (csvLines[i].length > 0) {
            points = csvLines[i].split(",");

            switch (points.length) {
            	case 2:
            		time = points[0];
                	acceleration = points[1];
            		break

            	case 4:
                	time = points[0];
                	// Extract only y form CSV with xyz
                	acceleration = points[2];
            		break;
            }

    		// Convert dates to timestamp i.e. '2019/09/22 10:14:06.753'
    		var myDate = new Date(time);
			var timestamp = myDate.getTime();
			if (timestamp) {
				var ss = myDate.getSeconds();
				var ms = myDate.getMilliseconds();
				time = ss.toString().padStart(2, '0') + '.' + ms.toString().padStart(3, '0');
			}

    		time = parseFloat(time);
    		if (time >= 0) {
        		acceleration = parseFloat(acceleration*-1); // Invert Y data from iphone app

        		// Normalize time to make it start from 0
	        	if (offsetTime < 0) {
	        		offsetTime = time;
	        	}

                var x = time - offsetTime;
                if (x <= maxSamples) {
                    dataPoints.push({ 
                        x: x,
                        y: acceleration,
                        markerType: 'triangle'
                    });
                }
            }

        }
    }

    return dataPoints;
}