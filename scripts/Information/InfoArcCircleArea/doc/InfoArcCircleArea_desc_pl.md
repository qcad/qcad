Autor: Robert S.

Polecenie to oblicza obszar łuków, okręgów, elips i łuków eliptycznych i
opcjonalnie dodaje informacje do bieżącej warstwy rysunku. Jeśli wybierzesz
inny typ jednostki, w wierszu poleceń pojawi się ostrzeżenie.

W przypadku łuków istnieją dwie opcje obliczania powierzchni, a mianowicie
Segment lub Sektor. Powierzchnia odcinka (lub plastra) to obszar ograniczony
łukiem oraz dwie linie wyznaczone od punktu początkowego i końcowego łuku do
jego środka. Obszar sektora jest to obszar ograniczony łukiem i pasem
narysowanym od punktu początkowego łuku do punktu końcowego.

![Segment or Sector](ArcCircle01.png)  
Rysunek 1: segment (plaster) i sektor.

**Opcje**

Polecenie to posiada standardowe opcje *"Dodaj pomiar do rysunku*" i *"Wysokość tekstu*".

![Standard options](ArcCircle02a.png)  
Rysunek 2: Standardowe opcje informacji

Niezależnie od tego, czy jest to wyłączone czy nie, po kliknięciu na łuk,
okrąg, elipsę lub eliptyczny łuk informacje są wyświetlane w widżecie wiersza
poleceń.

![Info is displayed in command line widget](ArcCircle03.png)  
Rysunek 3: Informacje wyświetlane w wierszu poleceń

(Uwaga: Przy każdym uruchomieniu polecenia informacyjnego pole wyboru *"Dodaj pomiar do rysunku*" jest zawsze odznaczone. Musisz pamiętać, aby
włączyć go, jeśli chcesz, aby informacje zostały dodane do rysunku).

Dodano również następujące opcje.

![Options toolbar](ArcCircle02.png)  
Rysunek 4: Opcje dodane

**Tryb:**

Tryb ten dotyczy tylko łuków.

![Sector](InfoSector.png)  
*Sektor:* Tryb ten zwraca obszar sektora. Jest to przydatne w połączeniu z
poleceniem *"Obszar wielokątny*".

![Segment](InfoSlice.png) *Segment:* Tryb ten zwraca obszar segmentu.

**Dodać:**

*Jednostka:* Zaznacza to, czy chcesz dodać kopię mierzonego elementu do
bieżącej warstwy rysunku.

*Akord:* Wybierz, czy chcesz dodać do rysunku cięciwę (sektor), czy też
linie promienia (segment).

*W kierunku wzdłużnym:* Domyślnie obszar jest zawsze drukowany na rysunku.
Opcja ta określa, czy do rysunku mają być dodane dodatkowe informacje.

Dla okręgów i pełnych elips dodatkową informacją jest obwód. Używa się w tym
celu punktu środkowego jako lewego dolnego rogu dodanego tekstu.

![Extra info for circles and ellipses](ArcCircle04.png)

W przypadku łuków okrągłych dodatkową informacją jest długość łuku i długość
pasa (w trybie sektorowym) lub promień (w trybie sektorowym).

W przypadku elipsy dodatkową informacją jest długość łuku i długość pasa (w
trybie sektorowym) lub odległość od punktu centralnego do punktu początkowego
łuku, a następnie odległość od punktu środkowego do punktu końcowego łuku (w
trybie odcinkowym).

Dolny lewy róg dodanego tekstu jest punktem końcowym łuku.

![Extra info for arcs](ArcCircle06.png)

![Extra info for arcs](ArcCircle05.png)

![Extra info for arcs](ArcCircle08.png)

![Extra info for arcs](ArcCircle07.png)
