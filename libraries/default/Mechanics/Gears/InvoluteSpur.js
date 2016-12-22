/**
 * Copyright (c) 2016 Iain Hibbert.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 *
 * InvoluteSpur.js - Gear generator for QCAD
 *
 *
 * Metric gears are defined by the module system, as follows:
 *
 * The diameter of the pitch circle, in mm
 * 	PCD = MOD * N
 *
 * The number of teeth
 *	N = PCD / MOD
 *
 * The module, is the length in mm of the pitch circle diameter, per tooth
 *	MOD = PCD / N
 *
 * The addendum is the height the tooth rises above the pitch circle
 *	A = MOD
 *
 * The outside diameter of the gear, is the PCD plus the addendum each way
 *	OD = PCD + (A * 2)
 *
 * The whole depth of the teeth, including clearance
 *	H = MOD * 2.25
 *
 * The root diameter is the OD minus the tooth height each side
 *	RD = OD - (H * 2)
 */

include("scripts/library.js");

function InvoluteSpur() {
}

/*
 * Fixed (for now) parameters
 */
InvoluteSpur.spokeRatio = 1.0;	// times axleDiameter
InvoluteSpur.hubRatio = 1.5;	// times axleDiameter
InvoluteSpur.rimRatio = 0.8;	// times rootRadius

/* defaults */
InvoluteSpur.pitchCircleDiameter = 100;
InvoluteSpur.drawPitchCircle = false;
InvoluteSpur.numberOfTeeth = 12;
InvoluteSpur.pressureAngle = 20;
InvoluteSpur.numberOfSpokes = 0;
InvoluteSpur.axleDiameter = 6;

/*
 * The function init() is called whenever the preview icon is generated or when the script
 * item is being inserted into a drawing.
 * - formWidget is the widget that displays the script item's parameters (if applicable).
 */

InvoluteSpur.init = function(formWidget) {
	if (!isNull(formWidget)) {
		InvoluteSpur.widgets = getWidgets(formWidget);

		var dv = new QDoubleValidator();
		dv.notation = "StandardNotation";

		var PCD = InvoluteSpur.widgets["PitchCircleDiameter"];	/* QLineEdit */
		PCD.setValidator(dv);
		PCD.text = InvoluteSpur.pitchCircleDiameter;

		var N = InvoluteSpur.widgets["NumberOfTeeth"];		/* QSpinBox */
		N.value = InvoluteSpur.numberOfTeeth;

		var MOD = InvoluteSpur.widgets["Module"];		/* QLabel */
		MOD.text = InvoluteSpur.pitchCircleDiameter / InvoluteSpur.numberOfTeeth;

		PCD.textChanged.connect(function(value) {
			MOD.text = value / InvoluteSpur.numberOfTeeth;
		});

		N['valueChanged(int)'].connect(function(value) {
			MOD.text = InvoluteSpur.pitchCircleDiameter / value;
		});

		var PA = InvoluteSpur.widgets["PressureAngle"];		/* QLineEdit */
		PA.setValidator(dv);
		PA.text = InvoluteSpur.pressureAngle;

		var AD = InvoluteSpur.widgets["AxleDiameter"];		/* QLineEdit */
		AD.setValidator(dv);
		AD.text = InvoluteSpur.axleDiameter;
	}
};

/*
 * The function generate() is called when the user is about to insert the script item.
 * - documentInterface is a valid document interface (RDocumentInterface) that is used
 *   to create the library item. This is not the document the user is editing.
 * - file is the name of the current script file (String).
 * 
 * This function is expected to return an object of type RAddObjectsOperation.
 */

InvoluteSpur.generate = function(documentInterface, file) {
	/* QLineEdit */
	var v = parseFloat(InvoluteSpur.widgets["PitchCircleDiameter"].text);
	if (!isNaN(v)) {
		InvoluteSpur.pitchCircleDiameter = v;
	}

	/* QLineEdit */
	var v = parseFloat(InvoluteSpur.widgets["PressureAngle"].text);
	if (!isNaN(v)) {
		InvoluteSpur.pressureAngle = v;
	}

	/* QLineEdit */
	var v = parseFloat(InvoluteSpur.widgets["AxleDiameter"].text);
	if (!isNaN(v)) {
		InvoluteSpur.axleDiameter = v;
	}

	/* QCheckBox */
	InvoluteSpur.drawPitchCircle = InvoluteSpur.widgets["DrawPitchCircle"].checked;

	/* QSpinBox */
	InvoluteSpur.numberOfTeeth = InvoluteSpur.widgets["NumberOfTeeth"].value;

	/* QSpinBox */
	InvoluteSpur.numberOfSpokes = InvoluteSpur.widgets["NumberOfSpokes"].value;

	return InvoluteSpur.createGear(documentInterface.getDocument());
};

/*
 * The function generatePreview() is called to create an icon for the library browser
 * preview. Note that at the moment the preview icon is generated, no user input is
 * available. Usually an icon with default parameters is generated.
 *  - documentInterface is a valid document interface (RDocumentInterface).
 *  - iconSize is the user configurable size of the icon (integer).
 *
 * This function is expected to return an object of type RAddObjectsOperation.
 */

InvoluteSpur.generatePreview = function(documentInterface, iconSize) {
	InvoluteSpur.pitchCircleDiameter = iconSize / 2;
	InvoluteSpur.drawPitchCircle = false;
	InvoluteSpur.pressureAngle = 20;
	InvoluteSpur.numberOfTeeth = 12;
	InvoluteSpur.numberOfSpokes = 0;
	InvoluteSpur.axleDiameter = iconSize / 15

	return InvoluteSpur.createGear(documentInterface.getDocument());
};

/*
 * Internal function, the polar angle for the involute curve at the given
 * radius. The angle is calculated as per formula derived from Wikipedia.
 */
function involuteAngle(radius, base) {
	const t = Math.sqrt(Math.pow(radius / base, 2) - 1);
	return t - Math.atan(t);
}

/*
 * Internal function to create a gear
 */
InvoluteSpur.createGear = function(document) {
	var addOperation = new RAddObjectsOperation(false);

	const centre = new RVector();
	const module = InvoluteSpur.pitchCircleDiameter / InvoluteSpur.numberOfTeeth;
	const pitchRadius = InvoluteSpur.pitchCircleDiameter / 2;
	const baseRadius = pitchRadius * Math.cos(deg2rad(InvoluteSpur.pressureAngle));
	const outsideRadius = pitchRadius + module;
	const rootRadius = outsideRadius - module * 2.25;

	/* draw pitch circle */
	if (InvoluteSpur.drawPitchCircle) {
		var cd = new RCircleData(centre, pitchRadius);
		addOperation.addObject(new RCircleEntity(document, cd));
	}

	/*
	 * Create an array of points and bulges for the tooth.
	 *
	 */
	var td = new Array();

	/*
	 * The root section, If the root is lower than the base circle, we start
	 * the tooth with a radial line between the two
	 */
	var radius = rootRadius;
	if (radius < baseRadius) {
		const angle = involuteAngle(baseRadius, baseRadius);
		td.push([radius, angle, 0]);
		radius = baseRadius;
	}

	/*
	 * The Involute Curve part to outsideRadius, ensuring that we place a
	 * vertex on the pitch circle.
	 */
	const step = (pitchRadius - radius) / 4;
	for (var n = 0; n < 4; n++) {
		const angle = involuteAngle(radius, baseRadius);
		td.push([radius, angle, 0]);
		radius += step;
	}

	const step = (outsideRadius - radius) / 5;
	for (var n = 0; n < 5; n++) {
		const angle = involuteAngle(radius, baseRadius);
		td.push([radius, angle, 0]);
		radius += step;
	}

	/*
	 * the pitchAngle is the angle at which the involute curve crosses the
	 * pitch circle
	 */
	const pitchAngle = involuteAngle(pitchRadius, baseRadius);
	const toothAngle = 2 * Math.PI / InvoluteSpur.numberOfTeeth;

	/*
	 * the vertex at outsideRadius is separate as we need to set the bulge
	 */
	const outsideAngle = involuteAngle(outsideRadius, baseRadius);
	const outsideBulge = Math.tan(((pitchAngle * 2) + (toothAngle / 2) - (outsideAngle * 2)) / 4);
	td.push([outsideRadius, outsideAngle, outsideBulge]);

	/*
	 * reflect the edge of the tooth onto the end of the array, without bulges
	 */
	for (var n = td.length - 1; n > 0; n--) {
		td.push([td[n][0], (pitchAngle * 2) + (toothAngle / 2) - td[n][1], 0]);
	}

	/*
	 * and finish off with a bulge at the root vertex this time
	 */
	const rootBulge = Math.tan(((toothAngle / 2) - (pitchAngle * 2) - td[0][1]) / 4);
	td.push([td[0][0], (pitchAngle * 2) + (toothAngle / 2) - td[0][1], rootBulge]);
	
	/*
	 * construct the gear
	 */
	gear = new RPolyline();
	gear.setClosed(true);
	for (var i = 0; i < InvoluteSpur.numberOfTeeth; i++) {
		for (var n = 0; n < td.length; n++) {
			gear.appendVertex(RVector.createPolar(td[n][0], (i * toothAngle) + td[n][1]), td[n][2]);
		}
	}

	addOperation.addObject(new RPolylineEntity(document, new RPolylineData(gear)));

	/* make axle hole, if required */
	if (InvoluteSpur.axleDiameter > 0) {
		var radius = Math.min(InvoluteSpur.axleDiameter / 2, pitchRadius - 2 * module);
		addOperation.addObject(new RCircleEntity(document, new RCircleData(centre, radius)));
	}

	/* make spokes, if required and is possible */
	if (InvoluteSpur.numberOfSpokes > 0 && InvoluteSpur.axleDiameter > 0) {
		const spokeAngle = 2 * Math.PI / InvoluteSpur.numberOfSpokes;

		var r0 = InvoluteSpur.hubRatio * InvoluteSpur.axleDiameter;
		var a0 = Math.asin((InvoluteSpur.spokeRatio * InvoluteSpur.axleDiameter) / (r0 * 2));

		var r1 = InvoluteSpur.rimRatio * rootRadius;
		var a1 = Math.asin((InvoluteSpur.spokeRatio * InvoluteSpur.axleDiameter) / (r1 * 2));

		var hole = new RPolyline();
		hole.setClosed(true);

		if (a0 > spokeAngle / 2) {
			a0 = spokeAngle / 2;
			r0 = (InvoluteSpur.spokeRatio * InvoluteSpur.axleDiameter) / (Math.sin(a0) * 2);
		} else {
			hole.appendVertex(RVector.createPolar(r0, spokeAngle - a0), Math.tan((2 * a0 - spokeAngle) / 4));
		}

		hole.appendVertex(RVector.createPolar(r0, a0));
		hole.appendVertex(RVector.createPolar(r1, a1), Math.tan((spokeAngle - 2 * a1) / 4));
		hole.appendVertex(RVector.createPolar(r1, spokeAngle - a1));

		if (r0 < r1) {
			for (var n = 0; n < InvoluteSpur.numberOfSpokes; n++) {
				addOperation.addObject(new RPolylineEntity(document, new RPolylineData(hole)));
				hole.rotate(spokeAngle, centre);
			}
		}
	}

	return addOperation;
}
