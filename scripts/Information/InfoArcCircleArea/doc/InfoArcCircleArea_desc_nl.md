Auteur Robert S.

Dit commando berekent de oppervlakte van bogen, cirkels, ellipsen en
elliptische bogen en voegt de informatie optioneel toe aan de huidige laag van
een tekening. Als u een ander type object selecteert, wordt in de opdrachtregel
een waarschuwing weergegeven.

Voor bogen zijn er twee opties voor het berekenen van oppervlakten, namelijk
Segment of Sector. Het gebied van een lijnstuk (of plak) is het gebied dat
wordt begrensd door de boog en twee lijnen die worden getrokken vanaf het
begin- en eindpunt van de boog tot het middelpunt van de boog. Het gebied van
een sector is het gebied dat wordt begrensd door de boog en een akkoord dat
wordt getekend van het beginpunt van de boog tot het eindpunt.

![Segment or Sector](ArcCircle01.png)  
Figuur 1: een segment (plak) en sector.

**Opties**

Dit commando heeft de standaardopties *"Meting toevoegen aan tekening*" en *"Teksthoogte*" *.*

![Standard options](ArcCircle02a.png)  
Figuur 2: Standaard Info opties

Of dit nu uit is of niet, wanneer u op een boog, cirkel, ellips of
elliptische boog klikt, wordt de informatie in de commandoblok-widget
weergegeven.

![Info is displayed in command line widget](ArcCircle03.png)  
Figuur 3: In de commandoblok weergegeven informatie

(Opmerking: Telkens als u een info-opdracht start, wordt het selectievakje *"Meting aan tekening toevoegen*" altijd uitgeschakeld. U moet er rekening
mee houden dat u deze moet inschakelen als u de info aan de tekening wilt
toevoegen).

Het voegt ook de volgende opties toe.

![Options toolbar](ArcCircle02.png)  
Figuur 4: Opties toevoegen

**Modus:**

De modus is alleen van toepassing op bogen.

![Sector](InfoSector.png)  
*Sector:* Deze modus geeft het gebied van de sector weer. Dit is nuttig in
combinatie met de opdracht
"*Polygoonoppervlakte*".

![Segment](InfoSlice.png) *Segment:* Deze modus geeft het gebied van het segment weer.

**Toevoegen:**

*Object:* Hiermee selecteert u of u een kopie van het meeteenheid aan de
huidige laag van de tekening wilt toevoegen.

*Koorde:* Hiermee selecteert u of u het akkoord (sector) of radiuslijnen
(segment) aan de tekening wilt toevoegen.

*Lengte:* Standaard wordt het gebied altijd op de tekening afgedrukt. Met
deze optie selecteert u of u extra informatie aan de tekening wilt
toevoegen.

Voor cirkels en volle ellipsen is de extra informatie de omtrek. Dit
gebruikt het middelpunt als de linkerbenedenhoek voor de toegevoegde tekst.

![Extra info voor cirkels en ellipsen](ArcCircle04.png)

Voor cirkelbogen is de extra informatie de lengte van de boog en de lengte
van het akkoord (in sector modus), of de straal (in segment modus).

Voor ellipsen is de extra informatie de lengte van de boog en de lengte van
het akkoord (in sector modus), of de afstand van het middelpunt tot het
beginpunt van de boog, gevolgd door de afstand van het middelpunt tot het
eindpunt van de boog (in segment modus).

De linkerbenedenhoek voor de toegevoegde tekst is het eindpunt van de
boog.

![Extra info voor bogen](ArcCircle06.png)

![Extra info voor bogen](ArcCircle05.png)

![Extra info voor bogen](ArcCircle08.png)

![Extra info voor bogen](ArcCircle07.png)
