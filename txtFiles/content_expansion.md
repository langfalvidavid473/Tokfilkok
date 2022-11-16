## Bolt - áruk bővítése:

**shop.txt** fájlt kell megnyitni, ahhoz új sorokat hozzáadni.

**name**: string => az árucikk neve

**price**: int => az árucikk ára

**type**: int =>
(fix érték) => Az érték hozzáadódik az adott stathoz
(változó érték) => Az érték először osztódik 100-zal, majd a stat felszorzódik a kapott százalékkal

1 - HEALTH (fix érték)

2 - DAMAGE (fix érték)

3 - ARMOR (fix érték)

4 - HEALTH (változó érték)

5 - DAMAGE (változó érték)

6 - ARMOR (változó érték)

7 - DODGE (változó érték)

8 - BOSS HEALTH DEBUFF (változó érték)

9 - BOSS DAMAGE DEBUFF (változó érték)

**value**: int => az érték, ami a megvásárláskor a játékos statjait változtatja.

**buff**: boolean (true/false) => ha true, a value hozzáad, ha false, a value elvesz a statokból.

**Példa 1:** name:Az egyszeri feltámadás itala type:1 price:300 value:250 buff:true => Élet elixir, ami 250-nel növeli a játékos életét
**Példa 2:** name:Az örök élet bájitala type:4 price:500 value:105 buff:true => Élet elixir, ami 5%-kal növeli a játékos életét

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

<<<<<<< Updated upstream
**Példa:** name:trágya value:500 type:2 => Trágya, amely 500 ponttal csökkenti a játékos sebzését
=======
**Példa:** name:trágya value:500 type:6 => Trágya, amely 10%-kal növeli a szörny sebzését
>>>>>>> Stashed changes

**A sorrend fontos!**

  

## Ellenfelek - szörnyek bővítése:

**Enemies** mappába elég bemásolni a szörny ASCII art-ját, és kész is, a program magától generál hozzá értékeket.
