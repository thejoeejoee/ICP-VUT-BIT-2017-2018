# Blokový editor
Aplikace slouží jako editor blokových schémat, kde každý blok obsahuje **vstupní porty s definovaným typem a výstupní port s typem**.
Vstupní porty jdou následně **připojit** do výstupních portů jiných bloků, samozřejmě dle shodujícího se typu.
Do každého vstupního portu lze buď připojit jiný port, nebo přímo zapsat **vstupní hodnotu**. 

![Screenshot](./screenshot.png)

## Instalace na merlin.fit.vutbr.cz
Po rozbalení archivu stačí zavolat `make` pro sestavení, respektive `make run` poté pro spuštění.
Vzhledem ke specifickému prostředí na serveru Merlin jsou absolutní cesty zadány v souboru `Makefile`.
_Pro lokální spouštění je nutné upravit cesty ke Qt ve zmíněném souboru - včetně souboru `qt.conf`._

## Instalace lokálně
V souboru `Makefile` je nutno změnit cesty k nástroji `qmake` a ke knihovně `Qt`. Dále v `src/qt.conf` nutno zkontrolovat cestu pro Qt pluginy - poté již jen `make && make run`.

## Autoři:
- Josef Kolář xkolar71
- Son Hai Nguyen xnguye16
