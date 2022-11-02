## Bolt - áruk bővítése:

**shop.txt** fájlt kell megnyitni, ahhoz új sorokat hozzáadni.

**name**: string => az árucikk neve

**price**: int => az árucikk ára

**type**: int =>

1 - HEALTH

2 - DAMAGE

3 - DODGE

4 - ARMOR

**value**: int => az érték, ami a megvásárláskor a játékos statjait változtatja.

**buff**: boolean (true/false) => ha true, a value hozzáad, ha false, a value elvesz a statokból.

**A sorrend fontos!**

  

## Kijárat - gyengítések bővítése:

**debuffs.txt** fájlt kell megnyitni, ahhoz új sorokat hozzáadni.

**name**: string => a gyengítés neve

**value**: int => a gyengítés értéke, a kiválasztáskor mennyivel csökken a játékos adott statja

**type**: int =>

1 - HEALTH

2 - DAMAGE

3 - DODGE

4 - ARMOR

5 - BOSS HEALTH

6 - BOSS DAMAGE

**A sorrend fontos!**

  

## Ellenfelek - szörnyek bővítése:

**Enemies** mappába elég bemásolni a szörny ASCII art-ját, és kész is, a program magától generál hozzá értékeket.