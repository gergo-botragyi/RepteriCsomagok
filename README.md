A program egy reptér csomagszállító rendszerét szimulálja. 
A modellben vannak csomagok, amelyek bizonyos csomópontokra érkeznek be. Innen futószalagok továbbítják azokat az 
úticélukhoz, amely bármely más csomópont lehet. Egy központi vezérlőrendszer adja ki az 
utasításokat, hogy a csomópontok hova, mely futószalagon küldjék tovább a csomagokat.

A program képes fájlból beolvasni a reptér rendszerét, valamint a csomagokat. Itt bemenetként 

a következőket várja soronkénti, vesszővel tagolt felsorolásban az alábbi sorrendben:

• Csomópontok neve (angol abc 1db nagy betűje)

• Futószalag: kezdő csomópont neve, vége csomópont neve (egy sor egy db)

• Csomag azonosítója (pozitív egész szám), kiinduló csomópont neve, cél csomópont neve (egy sor egy db)

Ezeket az adatokat be lehet vinni manuálisan is a konzolról a megfelelő menüpont segítségével.

A programmal tetszőleges mennyiségű csomópont, futószalag és csomag létrehozható.

A program lefutásához az adatoknak helyesnek kell lenni. Ennek feltételei:

• Minden csomóponthoz kapcsolódjon legalább egy ott végződő és egy ott kezdődő futószalag, annak érdekében, hogy oda csomagok érkezhessenek és onnan indulhassanak.

• A csomópontok rendszerének összefüggőnek kell lennie (összefüggő gráf). Tehát bármelyik csomópontról bármelyik másik elérhető legyen.

• Egy futószalag nem végződhet ott, ahol indul. Ezeket a program automatikusan törli.

• Két csomópont között közvetlen csak egy oda/vissza futószalag lehet. Ha már létezik A-->B futószalag, akkor a program nem fogja létrehozni azt újra. (Egyszerű gráf)

Ezen kívül alapvető feltétel, hogy a platform ahol a program fut rendelkezzen C++ fordítóval.

Ha megfelelő bemenet érkezik, a program elkezdi szimulálni a modellt. Ezt a konzolon végig lehet követni, ahol a program írja, hogy éppen az adott pillanatban melyik csomóponton mely csomagok vannak (azonosító szerint). Így jól látható ahogy egy csomag a lehető legrövidebb úton eljut az úticéljához. Végezetül a program kiírja (konzolra és fájlba is) a végleges állapotot a csomópontokkal és a csomagokkal.
