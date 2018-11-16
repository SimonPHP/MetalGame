# MetalGame
2D C++ Spieleentwicklungs Projekt

## Spiel Idee

### Intro
Man sitzt im Bus und hört Musik.
Nun kann man ein lied auswählen.
Zu diesem Lied träumt der Charakter dann entsprechends.

Nun wird ein Level geladen was der Musik entspricht.

### Spiel
Man Spielt einen Charakter aus der entsprechenden Metal Band und muss ein entsprechendes gegen genre bekämpfen z.B. Disco Musik.
Der endboss ist dann immer ein Charakter aus einer Band des Genres.

### Charakter
Jeder Charakter hat 3 Moves, Meele, Range, Ulti.
Die Waffe eines Charakters ist sein Instrument.

## Umsetzung
Es wird ein 2D Sidescroller und Platformer.

Ich denke mal wir verwenden am besten den Wrapper (suck it Jan :P).

### Object
Es gibt eine Abtractes Object welches folgende Attribute beinhaltet

* SDL::Rect rect;
* Tileset tileset;
* std::vector<SDL::Point*> animation;
* std::vector<SDL::Point *>::iterator it;
* int animationMaxTime = 12; 
* int animationTimer = 1;

Man kann in animation einfach eine Reihe von Punkten geben und so eine Animation von diesem Object erstellen.
Wenn man nur eine Statische grafik hat dann gibt man nur einen Punkt mit (ist überladen muss kein vector mit nur einem punkt übergeben werden)

Die animationMaxTime bestimmt nach wie vielen frames die animation sich ändert.

Das tileset object wrappt nur die drawsprite methode damit die einfacher zu nutzen ist.

### Kollision
Es gibt eine Collidable Klasse welche von Object erbt und noch zusätzlich eine hitbox enthält

* SDL::Rect *hitbox;

Die Hitbox kann mit bindHitboxToObjectRect(true) ans rect von Object gebudnen werden(pointer magie)

mit bool checkCollision(Collidable &secCol) kann man eine Kollision zwischen zwei collidables ermittlen.

### Player
Hier fängt das undurchdachte Problem an denn wie können wir den Input richtig handlen von einem Spieler?
Wenn wir zwischen Tastatur und Controller unterscheiden in der Player Klasse ist das viel aufwand wenn man etwas z.B an Sprungverhalten ändern will
muss man das an zwei stellen machen.

* Inputhandler *ih;
* double speed = 2;

* bool JUMP = false;
* bool FALL = false;
* int maxJump = 125;
* int maxY = 0;

Das ganze zeug sind hilfsvariablen zum springen

### Inputhandling
Das ist auch noch echt Problematisch, denn wo mappen wir jetzt den Input und wer legt fest welche Inputstates es alle gibt?

Der Inputhandler hat ein input array in welchem die tasten die wir benötigen auf ein float gemappt werden.
So kann man das direkt mit dem speed multiplizieren.

Die Abgeleiteten klassen wie inputhandlerkeyboard geben an wie diese states gesetzt werden.

Wenn man im Player jetzt nen neuen Input haben will dann muss man das im inputhandler regeln und dann in jeder abgeleiteten klasse davon auch(das lässt sich allerdings nie verhindern denn das ist ja ne tastenzuweisung)
Ich denke mal wir verwenden am besten den Wrapper (suck it Jan(nicht der von Ubisoft) :P).
