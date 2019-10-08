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
