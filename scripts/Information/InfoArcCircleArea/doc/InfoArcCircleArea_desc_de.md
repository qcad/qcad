Autor: Robert S.

Dieser Befehl berechnet die Fläche von Bögen, Kreisen, Ellipsen und
elliptischen Bögen und fügt optional die Informationen zur aktuellen Ebene
einer Zeichnung hinzu. Wenn Sie einen anderen Objekttyp auswählen, wird eine
Warnung in der Befehlszeile angezeigt.

Für Bögen gibt es zwei Möglichkeiten der Flächenberechnung, nämlich Segment
oder Sektor. Die Fläche eines Segments ist der Bereich, der
durch den Bogen und zwei Linien vom Start- und Endpunkt des Bogens zum
Mittelpunkt des Bogens begrenzt wird. Die Fläche eines Sektors ist der
Bereich, der durch den Bogen und eine Linie vom Startpunkt des Bogens bis zum
Endpunkt begrenzt wird.

![Segment or Sector](ArcCircle01.png)  
Abbildung 1: ein Segment und ein Sektor.

**Optionen**

Dieser Befehl hat die Standardoptionen "*Bemaßung zur Zeichnung hinzufügen*" und *"Texthöhe*".

![Standard Optionen](ArcCircle02a.png)  
Abbildung 2: Standard Optionen

Ob dies nun ausgeschaltet ist oder nicht, wenn Sie auf einen Bogen, Kreis,
eine Ellipse oder einen elliptischen Bogen klicken, werden die Informationen im
der Befehlszeile angezeigt.

![Info wird in der Befehlszeile angezeigt](ArcCircle03.png)  
Abbildung 3: In der Kommandozeile angezeigte Informationen

(Hinweis: Bei jedem Start eines Info-Befehls ist das Kontrollkästchen
"*Resultat der Zeichnung hinzufügen*"
deaktiviert. Sie müssen daran denken, es einzuschalten, wenn Sie möchten,
dass die Informationen in die Zeichnung aufgenommen werden).

Außerdem werden die folgenden Optionen hinzugefügt.

![Optionenwerkzeugleiste](ArcCircle02.png)  
Abbildung 4: Zusätzliche Optionen

**Modus:**

Der Modus gilt nur für Bögen.

![Sektor](InfoSector.png)  
*Sektor:* Dieser Modus gibt die Fläche des Sektors zurück. Dies ist
sinnvoll in Verbindung mit dem Befehl *"Polygon Fläche*".

![Segment](InfoSlice.png) *Segment:* Dieser Modus gibt die Fläche des Segments zurück.

**Hinzufügen:**

*Objekt:* Hiermit legen Sie fest, ob Sie dem aktuellen Layer der
Zeichnung eine Kopie des gemessenen Objekts hinzufügen möchten.

*Sehne:* Hiermit wählen Sie aus, ob die Sehne oder die
Radiuslinien (Sektor) in die Zeichnung eingefügt werden sollen.

*Länge:* Standardmässig wird die Fläche immer auf die Zeichnung gedruckt.
Mit dieser Option können Sie auswählen, ob der Zeichnung zusätzliche
Informationen hinzugefügt werden sollen.

Bei Kreisen und vollen Ellipsen ist die zusätzliche Information der Umfang.
Dabei wird der Mittelpunkt als untere linke Ecke für den hinzugefügten Text
verwendet.

![Extra Info für Kreise und Ellipsen](ArcCircle04.png)

Bei Kreisbögen ist die zusätzliche Information die Länge des Bogens und die
Länge der Sehne (im Sektormodus) oder der Radius (im Segmentmodus).

Bei Ellipsen ist die zusätzliche Information die Länge des Bogens und die
Länge der Sehne (im Sektormodus), oder der Abstand vom Mittelpunkt zum
Startpunkt des Bogens, gefolgt vom Abstand vom Mittelpunkt zum Endpunkt des
Bogens (im Segmentmodus).

Die untere linke Ecke für den hinzugefügten Text ist der Endpunkt des
Bogens.

![Extra Info für Bögen](ArcCircle06.png)

![Extra Info für Bögen](ArcCircle05.png)

![Extra Info für Bögen](ArcCircle08.png)

![Extra Info für Bögen](ArcCircle07.png)
