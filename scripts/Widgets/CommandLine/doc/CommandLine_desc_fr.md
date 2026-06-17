La ligne de commande de QCAD vous permet de lancer des commandes, d'entrer
 des coordonnées ou des valeurs telles que des distances ou des rayons.

### Saisie des coordonnées

Les coordonnées absolues sont saisies au format "x,y"

40,5

Les coordonnées relatives sont saisies au format "@x,y"

@10,6

Les coordonnées polaires absolues sont saisies au format
 "distance<angle"

10<30

Les coordonnées polaires relatives sont saisies au format
 "@distance<angle"

@10<45

Lors de la saisie de coordonnées ou de valeurs, des [expressions mathématiques](#expr) peuvent être utilisées pour
 calculer une coordonnée à partir de valeurs connues. Par exemple, la
 coordonnée 10,5 peut également être saisie sous la forme

5+5,30/6

### Calculatrice

La ligne de commande peut également être utilisée comme calculatrice. Pour
 ce faire, saisissez une [expression mathématique](#expr) précédée d'un signe égal

=3+4  
7

Des variables peuvent être utilisées pour stocker les valeurs

=a=5+6  
11  
=a/2  
5.5  

### Expressions mathématiques

Les constantes mathématiques disponibles sont :

PI, LN2, LN10, LOG2E, LOG10E, LOG10E, SQRT1_2, SQRT2

Les fonctions mathématiques disponibles sont :

abs, ceil, floor, exp, log, max, min, pow, sqrt, random, round, rad2deg, deg2rad,
sin, cos, tan, asin, acos, atan, atan2, log10, log1p, log2, sign, cosh, sinh, tanh,
acosh, asinh, atanh, expm1, hypot, cbrt, trunc

La plupart de ces constantes et fonctions sont des fonctions ECMAScript
 (JavaScript) standard et documentées en ligne. Dans ECMAScript standard, ces
 fonctions font partie de la classe Math, donc la fonction *abs* devrait être écrite comme *Math.abs.* Dans la ligne de commande QCAD, vous pouvez laisser la partie *Math.* de côté pour plus de commodité. Fonctions trigonométriques (sin,
 cos, tan, asin, acos, atan, atan, atan2) accepter ou retourner les angles en
 degrés. Si vous préférez les versions radian de ces fonctions, utilisez
 plutôt les fonctions *mathématiques* originales.

Les fonctions *rad2deg* et *deg2rad* permettent de convertir les angles entre radian et degrés.
