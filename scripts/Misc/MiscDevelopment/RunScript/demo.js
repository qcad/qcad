addLine(0,0,100,100);


// constants:
a=7; b=6;
// phase angle:
phi=0.2*Math.PI;
// iteration step:
step=Math.PI/256;
// width of plot (amplitude in X):
w=100;
// height of plot (amplitude in Y):
h=100;

// array of x,y coordinates on the curve:
v=[];

// loop:
for (t=0.0; t<Math.PI*2; t+=step) {
    qDebug("t:" + t);
    // compute next x,y coordinate:
    x = w * Math.sin(a*t + phi);
    y = h * Math.sin(b*t);

    // append coordinate to our array of coordinates:
    v.push([x,y]);
}

// add a spline to the drawing, using
// the computed coordinates as fit points:
addSpline(v, true);

// auto zoom:
autoZoom();
