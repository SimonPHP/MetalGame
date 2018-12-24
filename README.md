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

### Entity

Eine Entity enthält verschiedene Komponenten.
- Position Float(x, y)
- Size Int/Float?(x, y) //eventuell auch in EntityState?
- vector<EntityStates> //enthält alle States die die Entity haben kann
- accState EntityState

???collisionState??? mit anderen Entitys unwichtig für Umgebungs Kollision

- levelCollisionPoints std::vector<SDL::Points> //hitboxen Position relativ von der Position geteilt durch die TileSize

+ render()

### EntityState
- hitboxes[] SDL::Rect
- Size Int/Float?(x, y) //eventuell auch in EntityState?
- vector<Animation> //Aniamtion hällt Tileset/Animationstime/Animationen

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
