Auteur : Robert S.

Cette commande calcule la surface des arcs, cercles, ellipses et arcs
elliptiques, et ajoute éventuellement l'information au calque courant d'un
dessin. Si vous sélectionnez un autre type d'entité, un avertissement est
affiché dans la ligne de commande.

Pour les arcs, il y a deux options pour calculer les surfaces, à savoir
Segment ou Secteur. La zone d'un segment (ou tranche) est la zone délimitée par
l'arc et deux lignes tracées depuis le point de départ et le point final de
l'arc jusqu'au centre de l'arc. La zone d'un secteur est la zone délimitée par
l'arc et une corde dessinée depuis le point de départ de l'arc jusqu'au point
final.

![Segment or Sector](ArcCircle01.png)  
Figure 1 : un segment (tranche) et un secteur.

**Options**

Cette commande possède les options standard *"Ajouter une mesure au dessin*" et " *Hauteur du texte*".

![Standard options](ArcCircle02a.png)  
Figure 2 : Options d'information standard

Que cette fonction soit désactivée ou non, lorsque vous cliquez sur un arc,
un cercle, une ellipse ou un arc elliptique, l'information est affichée dans le
widget de la ligne de commande.

![Info is displayed in command line widget](ArcCircle03.png)  
Figure 3 : Informations affichées en ligne de commande

(Note : chaque fois que vous lancez une commande info, la case à cocher *"Ajouter une mesure au dessin*" est toujours décochée. Vous devez vous
rappeler de l'activer si vous voulez que les informations soient ajoutées au
dessin).

Il ajoute également les options suivantes.

![Options toolbar](ArcCircle02.png)  
Figure 4 : Options ajoutées

**Mode :**

Le mode ne s'applique qu'aux arcs.

![Sector](InfoSector.png)  
*Secteur :* Ce mode retourne la surface du secteur. Ceci est utile
lorsqu'il est utilisé en conjonction avec la commande *"Polygonal Area*".

![Segment](InfoSlice.png) *Segment :* Ce mode retourne la zone du segment.

**Ajouter :**

*Entité :* Ceci sélectionne si vous voulez ajouter une copie de l'entité
mesurée au calque courant du dessin.

*Chord :* Ceci sélectionne si vous voulez que l'accord (secteur), ou les
lignes de rayon (segment), soient ajoutés au dessin.

*Longueur :* Par défaut, la zone est toujours imprimée sur le dessin.
Cette option sélectionne si vous voulez que des informations supplémentaires
soient ajoutées au dessin.

Pour les cercles et les ellipses complètes, l'information supplémentaire est
la circonférence. Ceci utilise le point central comme coin inférieur gauche
pour le texte ajouté.

![Extra info for circles and ellipses](ArcCircle04.png)

Pour les arcs circulaires, l'information supplémentaire est la longueur de
l'arc et la longueur de l'accord (en mode secteur), ou le rayon (en mode
segment).

Pour les ellipses, l'information supplémentaire est la longueur de l'arc et
la longueur de l'accord (en mode secteur), ou la distance entre le point
central et le point de départ de l'arc, suivie de la distance entre le point
central et le point final de l'arc (en mode segment).

Le coin inférieur gauche pour le texte ajouté est le point final de
l'arc.

![Extra info for arcs](ArcCircle06.png)

![Extra info for arcs](ArcCircle05.png)

![Extra info for arcs](ArcCircle08.png)

![Extra info for arcs](ArcCircle07.png)
