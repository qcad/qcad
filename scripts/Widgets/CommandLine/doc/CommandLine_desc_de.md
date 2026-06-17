Über die Kommandozeile von QCAD können Befehle gestartet werden und
Koordinaten oder Werte wie Abstände oder Radien eingegeben werden.

### Koordinateneingabe

Absolute Koordinaten werden im Format "x,y" eingegeben:

40,5

Relative Koordinaten werden im Format "@x,y" eingegeben:

@10,6

Absolute polare Koordinaten werden im Format "Abstand<Winkel" eingegeben:

10<30

Relative polare Koordinaten werden im Format "@Abstand<Winkel" eingegeben:

@10<45

Bei jeder Eingabe von Koordinaten oder anderen Werten können [mathematische Ausdrücke](#expr) verwendet werden um Berechnungen durchzuführen. So kann zum Beispiel die Koordinate 10,5 eingegeben werden
als:

5+5,30/6

### Rechner

Die Kommandozeile kann außerdem als Rechner benutzt werden. Dazu wird der Eingabe
eines [mathematischen Ausdruckes](#expr) ein Gleichheitszeichen vorangestellt:

=3+4  
7

Werte können in Variablen abgelegt werden:

=a=5+6  
11  
=a/2  
5.5  

### Mathematische Ausdrücke

Mathematische Konstanten:

PI, LN2, LN10, LOG2E, LOG10E, SQRT1_2, SQRT2

Mathematische Funktionen:

abs, ceil, floor, exp, log, max, min, pow, sqrt, random, round, rad2deg, deg2rad,
sin, cos, tan, asin, acos, atan, atan2, log10, log1p, log2, sign, cosh, sinh, tanh,
acosh, asinh, atanh, expm1, hypot, cbrt, trunc

Die meisten dieser Konstanten und Funktionen sind Teil des ECMAScript (JavaScript) Standards
und Online dokumentiert. Im ECMAScript Standard sind diese Funktionen der Klasse *Math* angegliedert. Die Funktion abs müsste also als *Math.abs* ausgeschrieben werden. Die QCAD
Kommandozeile akzeptiert aber auch die kürzere Schreibweise *abs*.
Trigonometrische Funktionen (sin, cos, tan, asin, acos, atan, atan2) erwarten oder liefern
Winkel in Grad. Wenn stattdessen die Radiant basierten Funktionen verwendet werden sollen, können
die originalen Funktionen in der *Math* Klasse verwendet werden.

Die Funktionen *rad2deg* und *deg2rad* können zur Konvertierung von Winkeln
zwischen Radiant und Graden verwendet werden.
