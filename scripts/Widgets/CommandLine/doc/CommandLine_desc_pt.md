A linha de comando do QCAD permite iniciar comandos, introduzir
 coordenadas ou introduzir valores como distâncias ou raios.

### Introduzir coordenadas

As coordenadas absolutas são introduzidas no formato "x,y"

40,5

As coordenadas relativas são introduzidas no formato "@x,y"

@10,6

As coordenadas polares absolutas são introduzidas no formato
 "distância<ângulo"

10<30

As coordenadas polares relativas são introduzidas no formato
 "@distance<angle"

@10<45

Ao introduzir coordenadas ou valores, [as expressões matemáticas](#expr) podem ser utilizadas para
 calcular uma coordenada com base em valores conhecidos. Por exemplo, a
 coordenada 10,5 também pode ser introduzida como

5+5,30/6

### Calculadora

A linha de comando também pode ser usada como uma calculadora. Para isso,
 entrar uma [expressão matemática](#expr) com um sinal de igualdade

=3+4  
7

As variáveis podem ser usadas para armazenar valores

=a=5+6  
11  
=a/2  
5.5  

### Expressões Matemáticas

As constantes matemáticas disponíveis são:

PI, LN2, LN10, LOG2E, LOG10E, SQRT1_2, SQRT2

As funções matemáticas disponíveis são:

abs, ceil, floor, exp, log, max, min, pow, sqrt, random, round, rad2deg, deg2rad,
sin, cos, tan, asin, acos, atan, atan2, log10, log1p, log2, sign, cosh, sinh, tanh,
acosh, asinh, atanh, expm1, hypot, cbrt, trunc

A maioria dessas constantes e funções são funções padrão ECMAScript
 (JavaScript) e documentadas online. No ECMAScript padrão, estas funções fazem
 parte da classe Math, pelo que a função *abs* teria de ser escrita como *Math.abs.* Na linha de comando QCAD, você pode deixar de lado a parte *matemática* por conveniência *.* As funções trigonométricas (sin, cos, tan, asin, acos, atan, atan,
 atan2) aceitam ou retornam ângulos em graus. Se preferir as versões radianas
 destas funções, utilize as funções *matemáticas* originais *.*

As funções *rad2deg* e **deg2deg** podem ser usadas para converter ângulos entre radianos e graus.
