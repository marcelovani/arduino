'use strict';

// Clean charts
function clearCharts() {
	for (var i = 1; i <= clonedElements; i++) {
		var id = 'chartContainer-' + i;
		var div = document.getElementById(id);
		if (div !== null) {
			document.getElementById(id).remove();
		}
	}
	clonedElements = 0;
}
