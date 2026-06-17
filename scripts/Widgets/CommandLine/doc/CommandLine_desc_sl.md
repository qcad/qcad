Ukazna vrstica programa QCAD omogoča zagon ukazov, vnos koordinat ali vnos
 vrednosti, kot so razdalje ali polmeri.

### Vnos koordinat

Absolutne koordinate se vnesejo v obliki "x,y"

40,5

Relativne koordinate se vnesejo v obliki "@x,y"

@10,6

Absolutne polarne koordinate se vnesejo v obliki "razdalja<kot"

10<30

Relativne polarne koordinate se vnesejo v obliki "@distance<angle"

@10<45

Pri vnosu koordinat ali vrednosti se lahko za izračun koordinate na
 podlagi znanih vrednosti uporabijo [matematični izrazi](#expr). Na primer koordinata 10,5 se lahko
 vnese tudi kot

5+5,30/6

### Kalkulator

Ukazno vrstico lahko uporabite tudi kot kalkulator. To storite tako, da
 vnesete [matematični izraz,](#expr) ki mu sledi znak enakosti

=3+4  
7

Spremenljivke se lahko uporabljajo za shranjevanje vrednosti

=a=5+6  
11  
=a/2  
5.5  

### Matematični izrazi

Na voljo so naslednje matematične konstante:

PI, LN2, LN10, LOG2E, LOG10E, SQRT1_2, SQRT2

Matematične funkcije, ki so na voljo, so:

abs, ceil, floor, exp, log, max, min, pow, sqrt, random, round, rad2deg, deg2rad,
sin, cos, tan, asin, acos, atan, atan2, log10, log1p, log2, sign, cosh, sinh, tanh,
acosh, asinh, atanh, expm1, hypot, cbrt, trunc

Večina teh konstant in funkcij so standardne funkcije ECMAScripta
 (JavaScript) in so dokumentirane na spletu. V standardnem jeziku ECMAScript
 so te funkcije del razreda Math, zato bi bilo treba funkcijo *abs* zapisati kot *Math.abs*. V ukazni vrstici QCAD lahko zaradi priročnosti izpustite del *Math.* Trigonometrične funkcije (sin, cos, tan, asin, acos, atan, atan2)
 sprejemajo ali vračajo kote v stopinjah. Če imate raje radianske različice
 teh funkcij, uporabite izvirne funkcije *Math.*

Funkciji *rad2deg* in *deg2rad* lahko uporabite za pretvorbo kotov med radianom in
 stopinjami.
