/**
 * License: Public domain
 * 
 * This file is evaluated by ECMAScript engines before evaluating expressions 
 * entered in input fields or the command line.
 */

// add common functions of Math to global scope for use in math input fields:
PI = Math.PI;
LN2 = Math.LN2;
LN10 = Math.LN10;
LOG2E = Math.LOG2E;
LOG10E = Math.LOG10E;
SQRT1_2 = Math.SQRT1_2;
SQRT2 = Math.SQRT2;
abs = Math.abs;
ceil = Math.ceil;
floor = Math.floor;
exp = Math.exp;
log = Math.log;
max = Math.max;
min = Math.min;
pow = Math.pow;
sqrt = Math.sqrt;
random = Math.random;
round = Math.round;

// converting rad to deg:
rad2deg = function(a) { return a / (2.0 * Math.PI) * 360.0; };
// converting deg to rad:
deg2rad = function(a) { return (a / 360.0) * (2.0 * Math.PI); };

// trigonometry (for convenience in degrees!):
sin = function(v) { return Math.sin(deg2rad(v)); };
cos = function(v) { return Math.cos(deg2rad(v)); };
tan = function(v) { return Math.tan(deg2rad(v)); };
asin = function(v) { return rad2deg(Math.asin(v)); };
acos = function(v) { return rad2deg(Math.acos(v)); };
atan = function(v) { return rad2deg(Math.atan(v)); };
atan2 = function(y,x) { return rad2deg(Math.atan2(y,x)); };

// polyfills:
log10 = Math.log10 = function(x) { return Math.log(x) / Math.LN10; };
