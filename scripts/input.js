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


// polyfills for ECMAScript 2015 (ES6):
log10 = Math.log10 = function(x) { return Math.log(x) / Math.LN10; };
log1p = Math.log1p = function(x) { return Math.log(1 + x); };
log2 = Math.log2 = function(x) { return Math.log(x) / Math.LN2; };

sign = Math.sign = function(x) { x = +x; if (x === 0 || isNaN(x)) { return Number(x); } return x > 0 ? 1 : -1; };

cosh = Math.cosh = function(x) { return (Math.exp(x) + Math.exp(-x)) / 2; };
sinh = Math.sinh = function(x) { return (Math.exp(x) - Math.exp(-x)) / 2; };
tanh = Math.tanh = function(x) { if (x === Infinity) { return 1; } else if (x === -Infinity) { return -1; } else { return (Math.exp(x) - Math.exp(-x)) / (Math.exp(x) + Math.exp(-x)); } };

acosh = Math.acosh = function(x) { return Math.log(x + Math.sqrt(x * x - 1)); };
asinh = Math.asinh = function(x) { if (x === -Infinity) { return x; } else { return Math.log(x + Math.sqrt(x * x + 1)); } };
atanh = Math.atanh = function(x) { return Math.log((1+x)/(1-x)) / 2; };

expm1 = Math.expm1 = function(x) { return Math.exp(x) - 1; };
hypot = Math.hypot = function() { var y = 0; var length = arguments.length; for (var i = 0; i < length; i++) { if (arguments[i] === Infinity || arguments[i] === -Infinity) { return Infinity; } y += arguments[i] * arguments[i]; } return Math.sqrt(y); };

cbrt = Math.cbrt = function(x) { var y = Math.pow(Math.abs(x), 1/3); return x < 0 ? -y : y; };

trunc = Math.trunc = function(x) { return x < 0 ? Math.ceil(x) : Math.floor(x); };

