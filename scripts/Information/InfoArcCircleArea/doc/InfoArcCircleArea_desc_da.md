Forfatter: Robert S.

Denne kommando beregner arealet af buer, cirkler, ellipser og elliptiske
buer og tilføjer valgfrit oplysningerne til det aktuelle lag i en tegning. Hvis
du vælger en anden type enhed, vises der en advarsel i kommandolinjen.

For buer er der to muligheder for at beregne arealer, nemlig Segment eller
Sektor. Arealet af et segment (eller en skive) er det område, der er afgrænset
af buen og to linjer, der er trukket fra buens startpunkt og slutpunkt til
buens centrum. Arealet af en sektor er det område, der er afgrænset af buen og
en kordel, der er trukket fra buens startpunkt til slutpunktet.

![Segment or Sector](ArcCircle01.png)  
Figur 1: Et segment (skive) og en sektor.

**Indstillinger**

Denne kommando har standardindstillingerne *"Add measurement to drawing*" og " *Text Height*" ( *teksthøjde*).

![Standard options](ArcCircle02a.png)  
Figur 2: Standardindstillinger for info

Uanset om dette er slået fra eller ej, vises oplysningerne i
kommandolinje-widgetten, når du klikker på en bue, cirkel, ellipse eller
elliptisk bue.

![Info is displayed in command line widget](ArcCircle03.png)  
Figur 3: Info vises i kommandolinjen

(Bemærk: Hver gang du starter en info-kommando, er afkrydsningsfeltet *"Add measurement to drawing*" ( *Tilføj måling til tegning*) altid frakrydset. Du skal huske at slå den
til, hvis du vil have informationen tilføjet til tegningen).

Den tilføjer også følgende indstillinger.

![Options toolbar](ArcCircle02.png)  
Figur 4: Tilføjede indstillinger

**Mode (Tilstand):**

Tilstanden gælder kun for buer.

![Sector](InfoSector.png)  
*Sektor*: Denne tilstand returnerer sektorens areal. Dette er nyttigt, når
den bruges sammen med kommandoen *"Polygonal Area*".

![Segment](InfoSlice.png) *Segment*: Denne tilstand returnerer arealet af segmentet.

**Tilføj:**

*Enhed:* Dette vælger, om du vil tilføje en kopi af den målte enhed til
det aktuelle lag i tegningen.

*Chord (Akkord):* Dette vælger, om du vil have akkorden (sektor) eller
radiuslinjerne (segment) tilføjet til tegningen.

*Længde:* Som standard udskrives arealet altid på tegningen. Denne
indstilling vælger, om du ønsker, at der skal tilføjes ekstra oplysninger til
tegningen.

For cirkler og helellipser er de ekstra oplysninger omkredsen. Dette bruger
midtpunktet som det nederste venstre hjørne til den tilføjede tekst.

![Extra info for circles and ellipses](ArcCircle04.png)

For cirkelbuer er de ekstra oplysninger buens længde og længden af korden (i
sektortilstand) eller radius (i segmenttilstand).

For ellipser er de ekstra oplysninger buens længde og længden af korden (i
sektortilstand) eller afstanden fra midtpunktet til buens startpunkt,
efterfulgt af afstanden fra midtpunktet til buens slutpunkt (i
segmenttilstand).

Det nederste venstre hjørne for den tilføjede tekst er buens endepunkt.

![Extra info for arcs](ArcCircle06.png)

![Extra info for arcs](ArcCircle05.png)

![Extra info for arcs](ArcCircle08.png)

![Extra info for arcs](ArcCircle07.png)
