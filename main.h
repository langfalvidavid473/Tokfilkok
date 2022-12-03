#include "utilities.h"

#ifndef TOKFILKOK_MAIN_H
#define TOKFILKOK_MAIN_H

int shopDisplay(HANDLE h, vector<ShopItems> shopGoods, vector<Bosses> allBosses, Player player, int shopASCII, int i, float dodgePercent, string bossName, int shopASCIIRows){
    SetConsoleTextAttribute(h, 7);	// Parancssor betűszín változtatás (fehér)
    cout << "\t\t\t" << "━━━━━━━━" << endl;
    cout << "\t\t\t" << "┃ ÁRUK ┃" << endl;
    cout << "\t\t\t" << "━━━━━━━━" << endl;
    setCursorPosition(0,2);
    SetConsoleTextAttribute(h, shopGoods[0].color);	// Parancssor betűszín változtatás
    shopASCII = readFile("../txtFiles/shopASCII.txt", 7, "\t\t\t", shopASCII);	// Bolt menü beolvasása
    SetConsoleTextAttribute(h, shopGoods[1].color);	// Parancssor betűszín változtatás
    readFile("../txtFiles/shopASCII.txt", 7, "\t\t\t");
    SetConsoleTextAttribute(h, shopGoods[2].color);	// Parancssor betűszín változtatás
    readFile("../txtFiles/shopASCII.txt", 7, "\t\t\t");
    SetConsoleTextAttribute(h, shopGoods[0].color);	// Parancssor betűszín változtatás
    setCursorPosition(shopASCIIRows + 13, (shopASCII / 2) + 4);	// leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
    cout << "\t\t\t\t" << shopGoods[0].name << " (" << shopGoods[0].price << " arany) " << '[' << shopGoods[0].attribute << ']' << endl;
    SetConsoleTextAttribute(h, shopGoods[1].color);	// Parancssor betűszín változtatás
    setCursorPosition(shopASCIIRows + 13, (shopASCII / 2) + 6 + shopASCII);
    cout << "\t\t\t\t" << shopGoods[1].name << " (" << shopGoods[1].price << " arany) " << '[' << shopGoods[1].attribute << ']' << endl;
    SetConsoleTextAttribute(h, shopGoods[2].color);	// Parancssor betűszín változtatás
    setCursorPosition(shopASCIIRows + 13, (shopASCII / 2) + 8 + shopASCII*2);
    cout << "\t\t\t\t" << shopGoods[2].name << " (" << shopGoods[2].price << " arany) " << '[' << shopGoods[2].attribute << ']' << endl;
    SetConsoleTextAttribute(h, 7);	// Parancssor betűszín változtatás (fehér)
    setCursorPosition(0,(shopASCII*3) + 9);
    cout << "\t\t\t" << "━━━━━━━━━━━━━━━" << endl;
    cout << "\t\t\t" << "┃ INTERAKCIÓK ┃" << endl;
    cout << "\t\t\t" << "━━━━━━━━━━━━━━━" << endl;
    setCursorPosition(0,(shopASCII*3) + 13);
    SetConsoleTextAttribute(h, shopGoods[0].color);	// Parancssor betűszín változtatás
    cout << "\t\t\tVásárlás: " <<  shopGoods[0].name <<"(Balra nyíl)";
    setCursorPosition(0,(shopASCII*3) + 15);
    SetConsoleTextAttribute(h, shopGoods[1].color);	// Parancssor betűszín változtatás
    cout << "\t\t\tVásárlás: " << shopGoods[1].name << "(Előre nyíl)";
    setCursorPosition(0,(shopASCII*3) + 17);
    SetConsoleTextAttribute(h, shopGoods[2].color);	// Parancssor betűszín változtatás
    cout << "\t\t\tVásárlás: " << shopGoods[2].name << "(Jobbra nyíl)";
    setCursorPosition(0,(shopASCII*3) + 19);
    SetConsoleTextAttribute(h, 6);	// Parancssor betűszín változtatás (sárga)
    cout << "\t\t\tFrissítés [300 arany] (Hátra nyíl)";
    setCursorPosition(0,(shopASCII*3) + 21);
    SetConsoleTextAttribute(h, 8);	// Parancssor betűszín változtatás (szürke)
    cout << "\t\t\tKilépés [ESC]"; // Instrukciók
    setCursorPosition(0,(shopASCII*3) + 23);
    SetConsoleTextAttribute(h, 7);	// Parancssor betűszín változtatás (fehér)
    setCursorPosition(0,(shopASCII*3) + 23);
    cout << "\t\t\t" << "━━━━━━━━━━━━━━━━━━";
    setCursorPosition(0,(shopASCII*3) + 24);
    cout << "\t\t\t" << "┃ JÁTÉKOS STATOK ┃";
    setCursorPosition(0,(shopASCII*3) + 25);
    cout << "\t\t\t" << "━━━━━━━━━━━━━━━━━━";
    SetConsoleTextAttribute(h, 6);	// Parancssor betűszín változtatás (sárga)
    setCursorPosition(30,(shopASCII*3) + 26);
    cout << "\t\t\tArany: " << player.gold;
    SetConsoleTextAttribute(h, 2);	// Parancssor betűszín változtatás (zöld)
    setCursorPosition(30,(shopASCII*3) + 28);
    cout << "\t\t\tÉlet: " << player.health;
    SetConsoleTextAttribute(h, 3);	// Parancssor betűszín változtatás (aqua)
    setCursorPosition(30,(shopASCII*3) + 30);
    cout << "\t\t\tSebzés: " << player.damage;
    SetConsoleTextAttribute(h, 5);	// Parancssor betűszín változtatás (lila)
    setCursorPosition(30,(shopASCII*3) + 32);
    cout << "\t\t\tPáncél: " << player.armor;
    SetConsoleTextAttribute(h, 9);	// Parancssor betűszín változtatás (világoskék)
    setCursorPosition(30,(shopASCII*3) + 34);
    cout << "\t\t\tKitérés: " << dodgePercent;
    SetConsoleTextAttribute(h, 7);	// Parancssor betűszín változtatás (fehér)
    setCursorPosition(50,(shopASCII*3) + 23);
    cout << "\t\t\t" << "━━━━━━━━━━━━━━━━━";
    setCursorPosition(50,(shopASCII*3) + 24);
    cout << "\t\t\t" << "┃ SZÖRNY STATOK ┃";
    setCursorPosition(50,(shopASCII*3) + 25);
    cout << "\t\t\t" << "━━━━━━━━━━━━━━━━━";
    SetConsoleTextAttribute(h, 2);	// Parancssor betűszín változtatás (zöld)
    setCursorPosition(75,(shopASCII*3) + 26);
    cout << "\t\t\t" << bossName << " élete: " << allBosses[i].health;
    SetConsoleTextAttribute(h, 3);	// Parancssor betűszín változtatás (aqua)
    setCursorPosition(75,(shopASCII*3) + 28);
    cout << "\t\t\t" << bossName << " sebzése: " << allBosses[i].damage;
    return shopASCII;
}

void buyItems(HANDLE h, Player player, vector<ShopItems> shopGoods, vector<Bosses> allBosses, int shopASCII, int i, float dodgePercent, float dodgeChance, string bossName, bool itemPicked, int nthGood){
        switch (shopGoods[nthGood].type){			// A vásárolt áru típusának ellenőrzése
            case 1: player.health += shopGoods[nthGood].value; break;	// Ha a vásárolt áru buff, az adott típusú stat hozzáadódik, ha nem akkor kivonódik az eddigi értékből (ÉLET)
            case 2: player.damage += shopGoods[nthGood].value; break;	// Ha a vásárolt áru buff, az adott típusú stat hozzáadódik, ha nem akkor kivonódik az eddigi értékből (SEBZÉS)
            case 3: player.armor += shopGoods[nthGood].value; break;		// Ha a vásárolt áru buff, az adott típusú stat hozzáadódik, ha nem akkor kivonódik az eddigi értékből (PÁNCÉL)
            case 4: player.health = (player.health * shopGoods[nthGood].value / 100); break;		// (ÉLET BUFF %)
            case 5: player.damage = (player.damage * shopGoods[nthGood].value / 100); break;		// (SEBZÉS BUFF %)
            case 6: player.armor = (player.armor * shopGoods[nthGood].value / 100); break; 		// (PÁNCÉL BUFF %)
            case 7: dodgeChance = (dodgeChance * shopGoods[nthGood].value / 100); break;			// (KITÉRÉS BUFF %)
            case 8: allBosses[i].health = (allBosses[i].health * shopGoods[nthGood].value / 100) ; break; // (SZÖRNY ÉLET DEBUFF %)
            case 9: allBosses[i].damage = (allBosses[i].damage * shopGoods[nthGood].value / 100) ; break;	// (SZÖRNY SEBZÉS DEBUFF %)
        }
        setCursorPosition(0,(shopASCII*3) + 26);
        cout << "\x1b[2K";
        setCursorPosition(0,(shopASCII*3) + 28);
        cout << "\x1b[2K";
        setCursorPosition(0,(shopASCII*3) + 30);
        cout << "\x1b[2K";
        setCursorPosition(0,(shopASCII*3) + 32);
        cout << "\x1b[2K";
        setCursorPosition(0,(shopASCII*3) + 34);
        SetConsoleTextAttribute(h, 6);	// Parancssor betűszín változtatás (sárga)
        setCursorPosition(30,(shopASCII*3) + 26);
        cout << "\t\t\tArany: " << player.gold;
        SetConsoleTextAttribute(h, 2);	// Parancssor betűszín változtatás (zöld)
        setCursorPosition(30,(shopASCII*3) + 28);
        cout << "\t\t\tÉlet: " << player.health;
        SetConsoleTextAttribute(h, 3);	// Parancssor betűszín változtatás (aqua)
        setCursorPosition(30,(shopASCII*3) + 30);
        cout << "\t\t\tSebzés: " << player.damage;
        SetConsoleTextAttribute(h, 5);	// Parancssor betűszín változtatás (lila)
        setCursorPosition(30,(shopASCII*3) + 32);
        cout << "\t\t\tPáncél: " << player.armor;
        SetConsoleTextAttribute(h, 9);	// Parancssor betűszín változtatás (világoskék)
        setCursorPosition(30,(shopASCII*3) + 34);
        cout << "\t\t\tKitérés: " << dodgePercent;
        SetConsoleTextAttribute(h, 2);	// Parancssor betűszín változtatás (zöld)
        setCursorPosition(75,(shopASCII*3) + 26);
        cout << "\t\t\t" << bossName << " élete: " << allBosses[i].health;
        SetConsoleTextAttribute(h, 3);	// Parancssor betűszín változtatás (aqua)
        setCursorPosition(75,(shopASCII*3) + 28);
        cout << "\t\t\t" << bossName << " sebzése: " << allBosses[i].damage;
        shopGoods.erase(shopGoods.begin() + nthGood);
        Sleep(4000);
    }

    void notEnoughGold(HANDLE h, int shopASCII, vector<ShopItems> shopGoods, Player player, int nthGood){
        setCursorPosition(120,shopASCII + 15);
        cout << "                                                                                                                                    ";
        SetConsoleTextAttribute(h, 4);
        setCursorPosition(120,shopASCII + 15);
        cout << "\t\t\t" << "További " << shopGoods[nthGood].price - player.gold << " arany szükséges a tárgy megvásárlásához!" << endl;
}


void refreshShop(HANDLE h, Player player, vector<ShopItems> shopGoods, vector<Bosses> allBosses, int shopRefresh, int shopASCIIRows, int shopASCII, int i, float dodgePercent, string bossName ) {

        SetConsoleTextAttribute(h, shopGoods[0].color);    // Parancssor betűszín változtatás
        setCursorPosition(shopASCIIRows + 25, (shopASCII / 2) + 4);    // leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        cout << "                                                                                                ";
        setCursorPosition(shopASCIIRows + 25, (shopASCII / 2) + 4);    // leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        cout << "\t\t\t" << shopGoods[0].name << " (" << shopGoods[0].price << " arany) " << '[' << shopGoods[0].attribute << ']' << endl;
        setCursorPosition(shopASCIIRows + 25, (shopASCII / 2) + 6 + shopASCII);    // leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        cout << "                                                                                                ";
        SetConsoleTextAttribute(h, shopGoods[1].color);    // Parancssor betűszín változtatás
        setCursorPosition(shopASCIIRows + 22, (shopASCII / 2) + 6 + shopASCII);    // leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        cout << "\t\t\t" << shopGoods[1].name << " (" << shopGoods[1].price << " arany) " << '[' << shopGoods[1].attribute << ']' << endl;
        setCursorPosition(shopASCIIRows + 25, (shopASCII / 2) + 8 + shopASCII * 2);    // leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        SetConsoleTextAttribute(h, shopGoods[2].color);    // Parancssor betűszín változtatás
        cout << "                                                                                                ";
        setCursorPosition(shopASCIIRows + 25, (shopASCII / 2) + 8 + shopASCII * 2);    // leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        cout << "\t\t\t" << shopGoods[2].name << " (" << shopGoods[2].price << " arany) " << '[' << shopGoods[2].attribute << ']' << endl;
        setCursorPosition(0, (shopASCII * 3) + 13);
        cout << "                                                                                                                                    ";
        setCursorPosition(0, (shopASCII * 3) + 15);
        cout << "                                                                                                                                    ";
        setCursorPosition(0, (shopASCII * 3) + 17);
        cout << "                                                                                                                                    ";
        SetConsoleTextAttribute(h, shopGoods[0].color);    // Parancssor betűszín változtatás
        setCursorPosition(0, (shopASCII * 3) + 13);
        cout << "\t\t\t" << "Vásárlás: " << shopGoods[0].name << "(Balra nyíl) 🠰";
        SetConsoleTextAttribute(h, shopGoods[1].color);    // Parancssor betűszín változtatás
        setCursorPosition(0, (shopASCII * 3) + 15);
        cout << "\t\t\t" << "Vásárlás: " << shopGoods[1].name << "(Előre nyíl) 🠱";
        SetConsoleTextAttribute(h, shopGoods[2].color);    // Parancssor betűszín változtatás
        setCursorPosition(0, (shopASCII * 3) + 17);
        cout << "\t\t\t" << "Vásárlás: " << shopGoods[2].name << "(Jobbra nyíl) 🠲";
        setCursorPosition(0, (shopASCII * 3) + 27);
        cout << "                                                                                                                                    ";
        SetConsoleTextAttribute(h, 6);    // Parancssor betűszín változtatás (sárga)
        setCursorPosition(30, (shopASCII * 3) + 26);
        cout << "\t\t\tArany: " << player.gold;
        SetConsoleTextAttribute(h, 2);    // Parancssor betűszín változtatás (zöld)
        setCursorPosition(30, (shopASCII * 3) + 28);
        cout << "\t\t\tÉlet: " << player.health;
        SetConsoleTextAttribute(h, 3);    // Parancssor betűszín változtatás (aqua)
        setCursorPosition(30, (shopASCII * 3) + 30);
        cout << "\t\t\tSebzés: " << player.damage;
        SetConsoleTextAttribute(h, 5);    // Parancssor betűszín változtatás (lila)
        setCursorPosition(30, (shopASCII * 3) + 32);
        cout << "\t\t\tPáncél: " << player.armor;
        SetConsoleTextAttribute(h, 9);    // Parancssor betűszín változtatás (világoskék)
        setCursorPosition(30, (shopASCII * 3) + 34);
        cout << "\t\t\tKitérés: " << dodgePercent;
        SetConsoleTextAttribute(h, 2);    // Parancssor betűszín változtatás (zöld)
        setCursorPosition(75, (shopASCII * 3) + 26);
        cout << "\t\t\t" << bossName << " élete: " << allBosses[i].health;
        SetConsoleTextAttribute(h, 3);    // Parancssor betűszín változtatás (aqua)
        setCursorPosition(75, (shopASCII * 3) + 28);
        cout << "\t\t\t" << bossName << " sebzése: " << allBosses[i].damage;
    }

    int exitDisplay(HANDLE h, Player player, vector<Debuffs> debuffs, vector<Bosses> allBosses, int debuffsASCII, int debuffsASCIIRows, int i, float dodgePercent, string bossName ){
        cout << "\t\t\t" << "━━━━━━━━━━━━━━━" << endl;
        cout << "\t\t\t" << "┃ GYENGÍTÉSEK ┃" << endl;
        cout << "\t\t\t" << "━━━━━━━━━━━━━━━" << endl;
        setCursorPosition(0,2);
        debuffsASCII = readFile("../txtFiles/debuffsASCII.txt", 4, "\t\t\t", debuffsASCII);					// Gyengítésekhez tartozó ASCII-k beolvasása
        readFile("../txtFiles/debuffsASCII.txt", 4, "\t\t\t");
        readFile("../txtFiles/debuffsASCII.txt", 4, "\t\t\t");
        setCursorPosition(debuffsASCIIRows + 13, (debuffsASCII / 2) + 4);	// leghosszabb sor hossza + 4 + tabok száma (3*3 karakter), sorok száma / 2
        cout << "\t\t\t\t" << debuffs[0].name << '[' << debuffs[0].attribute << ']' << endl;
        setCursorPosition(debuffsASCIIRows + 13, (debuffsASCII / 2) + 6 + debuffsASCII);
        cout << "\t\t\t\t" << debuffs[1].name << '[' << debuffs[1].attribute << ']' << endl;
        setCursorPosition(debuffsASCIIRows + 13, (debuffsASCII / 2) + 8 + debuffsASCII*2);
        cout << "\t\t\t\t" << debuffs[2].name << '[' << debuffs[2].attribute << ']' << endl;
        setCursorPosition(0,(debuffsASCII*3) + 9);
        cout << "\t\t\t" << "━━━━━━━━━━━━━━━" << endl;
        cout << "\t\t\t" << "┃ INTERAKCIÓK ┃" << endl;
        cout << "\t\t\t" << "━━━━━━━━━━━━━━━" << endl;
        setCursorPosition(0,(debuffsASCII*3) + 13);
        cout << "\t\t\t" << "Kiválasztás: " <<  debuffs[0].name <<"(Balra nyíl) 🠰\n\n\t\t\tKiválasztás: " << debuffs[1].name
        << "(Előre nyíl) 🠱\n\n\t\t\tKiválasztás: " << debuffs[2].name << "(Jobbra nyíl) 🠲\n\n\t\t\tKilépés [ESC]"; // Instrukciók
        setCursorPosition(0,(debuffsASCII*3) + 22);
        cout << "\t\t\t" << "━━━━━━━━━━" << endl;
        cout << "\t\t\t" << "┃ STATOK ┃" << endl;
        cout << "\t\t\t" << "━━━━━━━━━━\n" << endl;
        cout << "\t\t\t" << "Arany: " << player.gold << "\tÉlet: " << player.health << "\tSebzés: " << player.damage << "\tPáncél: " << player.armor << "\tKitérés: " << dodgePercent << "%\n" << endl;
        cout << "\t\t\t" << bossName << " élete: " << allBosses[i].health << "\t" << bossName << " sebzése: " << allBosses[i].damage << endl;
        return debuffsASCII;
}

void pickDebuff(Player player, vector<Debuffs> debuffs, vector<Bosses> allBosses, float dodgeChance, int i, int nthDebuff){
    switch(debuffs[0].type) {    // Gyengítés típusának ellenőrzése (debuffs.txt)
        case 1: player.health = (player.health * debuffs[nthDebuff].value / 100);               // JÁTÉKOS ÉLET CSÖKKENTÉS
        case 2: player.damage = (player.damage * debuffs[nthDebuff].value / 100);               // JÁTÉKOS SEBZÉS CSÖKKENTÉS
        case 3: dodgeChance = (dodgeChance * debuffs[nthDebuff].value / 100);                   // JÁTÉKOS KITÉRÉS CSÖKKENTÉS
        case 4: player.armor = (player.armor * debuffs[nthDebuff].value / 100);                 // JÁTÉKOS PÁNCÉL CSÖKKENTÉS
        case 5: allBosses[i].health = (allBosses[i].health * debuffs[nthDebuff].value / 100);   // SZÖRNY ÉLET NÖVELÉS
        case 6: allBosses[i].damage = (allBosses[i].damage * debuffs[nthDebuff].value / 100);   // SZÖRNY SEBZÉS NÖVELÉS
        }
}

void bossDies(Player *player, vector<Bosses> allBosses, int i, int longestRow, int bossHeight){
    allBosses[i].health = 0;
    newLine();
    int goldWon = generateNum(500,750);
    player->gold += goldWon;									// Játékos kap 500-750 aranyat a győzelemért
    int keyChance = generateNum(1,100);						// Szám generálás 1 és 100 között
    bool giveKey;
    keyChance % 2 == 0 ? giveKey = true : giveKey = false;	// A generált szám ellenőrzése
    giveKey ? player->keys += 1 : player->keys += 0;			// Ha a generált szám páros, a játékos kap kulcsot (50% esély)
    setCursorPosition(longestRow + 40, (bossHeight / 2) + 28);
    cout << "\tGratulálok! Legyőzted a szörnyet!" << endl;
    newLine();
    if(giveKey){
        setCursorPosition(longestRow + 40, (bossHeight / 2) + 30);
        cout << "\t" << goldWon << " aranyat és 1 kulcsot nyertél!" << endl;
    }
    else{
        setCursorPosition(longestRow + 40, (bossHeight / 2) + 30);
        cout << "\t" << goldWon << " aranyat nyertél!" << endl;
    }
}

size_t combatInteractions(Player *player, vector<Bosses> allBosses, int *i, int combatOption, int longestRow, int bossHeight, float dodgePercent, float *dodgeChance, string bossName, string playerName, bool gameOver){
    do
    {
        BlockInput(false);							// User input engedélyezése, hogy ismét lehessen választani
        combatOption = _getch();					// Változó a harc közben lenyomható billentyűkre
        BlockInput(true);							/* User input megszűntetése (azért, hogy tudjon automatikusan működni a harc,
														   		   ne lépjen fel semmi furcsa jelenség, ha a felhasználó nyomkodja a gombokat) */
        if (combatOption == 0 || combatOption == 0xE0) combatOption = _getch();
        if (combatOption == RIGHT && *i < allBosses.size()){ 		// Jobb nyíl lenyomása (támadás)
            setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
            cout << "\tTámadás!!!" << endl;
            Sleep(1000);
            if((allBosses[*i].health - player->damage) > 0){
                allBosses[*i].health -= player->damage;				// Támadás után a szörny életet veszít
            }
            else{
                bossDies(player, allBosses, *i, longestRow, bossHeight);
                Sleep(4000);
                break;
            }
            displayStats(allBosses, *player, *i, dodgePercent, longestRow + 20, (bossHeight / 2) - 6);
            setCursorPosition(longestRow + 40, (bossHeight / 2) + 26);
            cout << "\t" << player->damage << " sebzést okoztál!" << endl;
            Sleep(1000);
            if (allBosses[*i].health > 0) {											// Ha a szörnynek maradt élete, támadjon vissza, ha nincs, akkor a játékos győzőtt
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 28);
                cout << "\t" << bossName << " támad!" << endl;
                Sleep(1000);
                if(player->health - (allBosses[*i].damage - player->armor) > 0) {
                    player->health -= (allBosses[*i].damage - player->armor); 			// Játékos életet veszít (szörny sebzése - játékos páncélja)
                }
                else {
                    player->health = 0;
                    Sleep(2000);
                    system("cls");
                    readFile("../txtFiles/lose.txt", 7);
                    _getch();
                    gameOver = true;
                    exit(0);
                }
                displayStats(allBosses, *player, *i, dodgePercent, longestRow + 20, (bossHeight / 2) - 6);
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 30);
                cout << "\t" << allBosses[*i].damage - player->armor << " sebzést szenvedtél!" << endl;	// Elveszített élet pontok kiírása
                Sleep(1000);
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
                cout << "                                                                  ";
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 26);
                cout << "                                                                  ";
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 28);
                cout << "                                                                  ";
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 30);
                cout << "                                                                  ";
            }
        }													// Ha a szörny élete <= 0, a játékos győzött

        else if(combatOption == LEFT && *i < allBosses.size()){		// Bal nyíl lenyomása, kitérés a szörny elől
            int chance = generateNum(0, *dodgeChance);				// Szám generálása 0 és dodgeChance (150) között, később változhat
            bool runAway;
            chance % 5 == 0 ? runAway = true : runAway = false;		// Ha a generált szám osztható 5-tel, a játékos kitéra szörny elől (kezdetben 20% esély, később változhat)
            if(runAway){											// Ha sikeres a kitérés, kilépés a harcból, főciklus elejére ugrás
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
                cout << "\tSikeres kitérés!" << endl;
                Sleep(2000);
                break;
            }
            else{													// Ha nem sikerült a kitérés, a szörny támad
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
                cout << "\tSikertelen kitérés!" << endl;
                Sleep(1000);
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
                cout << "                                                                  ";
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
                cout << "\t" << bossName << " támad!" << endl;
                Sleep(1000);
                if(player->health - (allBosses[*i].damage - player->armor) > 0) {
                    player->health -= (allBosses[*i].damage - player->armor);
                }
                else {
                    newLine();
                    player->health = 0;
                    Sleep(2000);
                    system("cls");
                    readFile("../txtFiles/lose.txt", 7);
                    _getch();
                    gameOver = true;
                    exit(0);
                }
                displayStats(allBosses, *player, *i, dodgePercent, longestRow + 20, (bossHeight / 2) - 6);
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 26);
                cout << "\t" << allBosses[*i].damage - player->armor << " sebzést szenvedtél!" << endl;
                Sleep(1000);
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 24);
                cout << "                                                                  ";
                setCursorPosition(longestRow + 40, (bossHeight / 2) + 26);
                cout << "                                                                  ";
            }
        }
        else if(combatOption == ESC) {								// ESC-re kilép a program (harc közben is)
            system("cls");
            cout << "Kilépés!";
            Sleep(2000);
            exit(0);
        }
        else {														// Ha a felsorolt gombok közül egyiket sem nyomta le a felhasználó, hibaüzenetet kap
            setCursorPosition(longestRow + 40, (bossHeight / 2) + 32);
            SetConsoleOutputCP(1250);
            cout << "\t" << playerName;
            SetConsoleOutputCP(65001);
            cout << ", a folytatáshoz nyomd le a fent látható gombok egyikét!" << endl;
            Sleep(2000);
            setCursorPosition(longestRow + 40, (bossHeight / 2) + 32);
            cout << "                                                                  ";
        }
    } while ((player->health >= 0) && (allBosses[*i].health >= 0));	// Ha mind két félnek maradt élete, folytatódhat a harc
}

size_t gameLoop(HANDLE h, Player *player, vector<Bosses> allBosses, vector<ShopItems> shopGoods, vector<Debuffs> debuffs,
                int i, float *dodgeChance, string playerName, int shopRefresh, bool *gameOver, bool *itemPicked, int *bossHeight, int *doorHeight,
                int *doorLeftHeight, int *shopASCII, int *debuffsASCII, int *combatOption){
    string bossName;
    do
    {
        bossName = allBosses[i].fileName.substr(1, allBosses[i].fileName.length()-5);
        bossName[0] = toupper(bossName[0]);
        *bossHeight = 0;
        *doorHeight = 0;
        *doorLeftHeight = 0;
        *shopASCII = 0;
        *debuffsASCII = 0;
        *combatOption = 0;
        *gameOver = false;
        float dodgePercent = (*dodgeChance / 5);
        BlockInput(false);	/* User input engedélyezése (BlockInput függvény használata
							   rendszergazdaként való futtatást igényel, anélkül nem működik) */
        system("cls");
        *doorHeight = readFile("../txtFiles/doors.txt", 7, "\t\t\t\t", *doorHeight);	// Ajtók beolvasása fájlból
        newLine();
        newLine();
        newLine();
        SetConsoleOutputCP(1250);	// UTF-8 változóból kiíratáshoz
        cout << "\t\t\t\t" << playerName;
        SetConsoleOutputCP(65001);	// UTF-8 általános kiíratáshoz
        cout << ", " << "válassz egy ajtót jobb vagy bal nyíl használatával!" << endl;
        newLine();
        cout << "\t\t\t\t" << "Arany: " << player->gold << endl;
        cout << "\t\t\t\t" << "Kulcsok: " << player->keys << endl;
        int pressedChar = _getch();		// User inputra várakozás, majd a kapott karakter eltárolása
        if (pressedChar == 0 || pressedChar == 0xE0) pressedChar = _getch();	// Virtuális karakterek (nyilak) nem 1 értéket adnak vissza, ezért plusz ellenőrzés szükséges
        if(pressedChar == LEFT && i < allBosses.size()){			// ----Bal ajtó választása----
            setCursorPosition(0,0);	/*
									Kurzor pozíciója (innen kezdődik a nyomtatás)
									A program működésének egyik fő eleme. Ha nem felülírnánk a nyomtatott karaktereket,
									hanem minden képfrissítésnél törölnénk az egész kimenetet, akkor minden egyes alkalommal
									villanna egyet a kép, ami nagyon zavaró. Ezzel a módszerrel ezt kiküszöböltük, csak az
									változik, aminek az adott pillanatban szükséges.
									*/
            *doorLeftHeight = readFile("../txtFiles/doorsLeft.txt", 7, "\t\t\t\t", *doorLeftHeight);
            Sleep(1500);
            system("cls");
            do
            {
                setCursorPosition(0,0);
                *itemPicked = false;
                readFile("../txtFiles/doors.txt", 7, "\t\t\t\t");
                newLine();
                newLine();
                cout << "\t\t\t\t\t\t\t\t\tBolt" << "\t\t\t\t\t\t\t\t\t" << "Kijárat" << endl;
                int pickDoor = _getch();
                if (pickDoor == 0 || pickDoor == 0xE0) pickDoor = _getch();
                // ---- Bolt ----
                if(pickDoor == LEFT){
                    if(player->keys>0){	// Csak akkor enged be, ha a játékos rendelkezik kulccsal
                        player->keys--;		// Belépés után 1 kulcs elveszik
                        if(shopGoods.size() > 5){
                            do
                            {
                                shuffleArray(shopGoods);	// Az árukat tároló vektor összekeverése
                            } while ((shopGoods[0].type == shopGoods[1].type) ||
                                     (shopGoods[0].type == shopGoods[2].type) ||
                                     (shopGoods[1].type == shopGoods[2].type));
                        }
                        else shuffleArray(shopGoods);
                        setCursorPosition(0,0);
                        readFile("../txtFiles/doorsLeft.txt", 7, "\t\t\t\t");
                        Sleep(2000);
                        system("cls");
                        int shopASCIIRows = countRows("../txtFiles/shopASCII.txt");
                        *shopASCII = shopDisplay(h,shopGoods,allBosses,*player,*shopASCII,i,dodgePercent,bossName, shopASCIIRows);
                        Sleep(2000);
                        *itemPicked = false;	// Amíg a változó hamis, nem történt interakció
                        do
                        {
                            int pickShopItems = _getch();
                            if (pickShopItems == 0 || pickShopItems == 0xE0) pickShopItems = _getch();
                            switch(pickShopItems){
                                case LEFT: {	// Első áru megvásárlása
                                    if (player->gold >= shopGoods[0].price) {    // Ha a játékos pénze elegendő, az áru megvásárolható
                                        setCursorPosition(120, (*shopASCII * 3) + 15);
                                        cout << "                                                                                                                                    ";
                                        setCursorPosition(120, (*shopASCII * 3) + 15);
                                        cout << "\t\t\t" << shopGoods[0].name << " megvásárolva " << shopGoods[0].price << " aranyért!" << endl;
                                        player->gold -= shopGoods[0].price;    // Arany levonása az árnak megfelelően
                                        *itemPicked = true;                    // Változó igazra vált, kilépés a boltból
                                        buyItems(h, *player, shopGoods, allBosses, *shopASCII, i, dodgePercent, *dodgeChance, bossName, itemPicked, 0);
                                    }
                                    else {
                                        notEnoughGold(h,*shopASCII,shopGoods,*player,0);
                                    }
                                } break;
                                case UP: {	// Második áru megvásárlása
                                    if (player->gold >= shopGoods[1].price) {    // Ha a játékos pénze elegendő, az áru megvásárolható
                                        setCursorPosition(120, (*shopASCII * 3) + 15);
                                        cout << "                                                                                                                                    ";
                                        setCursorPosition(120, (*shopASCII * 3) + 15);
                                        cout << "\t\t\t" << shopGoods[1].name << " megvásárolva " << shopGoods[1].price << " aranyért!" << endl;
                                        player->gold -= shopGoods[1].price;    // Arany levonása az árnak megfelelően
                                        *itemPicked = true;                    // Változó igazra vált, kilépés a boltból
                                        buyItems(h, *player, shopGoods, allBosses, *shopASCII, i,dodgePercent,*dodgeChance,bossName,itemPicked,1);
                                    }
                                    else {
                                        notEnoughGold(h,*shopASCII,shopGoods,*player,1);
                                    }
                                } break;
                                case RIGHT: {	// Harmadik áru megvásárlása
                                    if (player->gold >= shopGoods[2].price) {    // Ha a játékos pénze elegendő, az áru megvásárolható
                                        setCursorPosition(120, (*shopASCII * 3) + 15);
                                        cout << "                                                                                                                                    ";
                                        setCursorPosition(120, (*shopASCII * 3) + 15);
                                        cout << "\t\t\t" << shopGoods[2].name << " megvásárolva " << shopGoods[2].price << " aranyért!" << endl;
                                        player->gold -= shopGoods[2].price;    // Arany levonása az árnak megfelelően
                                        *itemPicked = true;                    // Változó igazra vált, kilépés a boltból
                                        buyItems(h, *player, shopGoods, allBosses, *shopASCII, i,dodgePercent,*dodgeChance,bossName,itemPicked,2);
                                    }
                                    else {
                                        notEnoughGold(h,*shopASCII,shopGoods,*player,2);
                                    }
                                } break;
                                case DOWN: {	// Bolt frissítése
                                    if (player->gold >= shopRefresh) { // Ha a játékosnak van elég pénze, frissítheti az árukat
                                        player->gold -= shopRefresh;     // Az arany levonódik frissítés után
                                        if (shopGoods.size() > 5) {
                                            do {
                                                shuffleArray(shopGoods);    // Az árukat tároló vektor összekeverése
                                            } while ((shopGoods[0].type == shopGoods[1].type) ||
                                                     (shopGoods[0].type == shopGoods[2].type) ||
                                                     (shopGoods[1].type == shopGoods[2].type));
                                        } else { shuffleArray(shopGoods); }
                                        refreshShop(h, *player, shopGoods, allBosses, shopRefresh, shopASCIIRows, *shopASCII, i, dodgePercent, bossName);
                                    }
                                    else {    // Ha nincs elegendő arany a frissítéshez, a játékos hibaüzenetet kap
                                        setCursorPosition(120, *shopASCII + 15);
                                        cout << "                                                                                                                                    ";
                                        SetConsoleTextAttribute(h, 4);
                                        setCursorPosition(120, *shopASCII + 15);
                                        cout << "\t\t\t\t" << "További " << shopRefresh - player->gold << " arany szükséges az áruk frissítéséhez!" << endl;
                                    }
                                } break;
                                case ESC: {	// Kilépés a boltból, ha semmire sem elegendő a játékos aranya
                                    setCursorPosition(75,*shopASCII + 15);
                                    cout << "                                                                                                                                    ";
                                    SetConsoleTextAttribute(h, 4);
                                    setCursorPosition(75,*shopASCII + 15);
                                    cout << "\t\t\t\t" << "Kilépés!";
                                    *itemPicked=true;
                                } break;
                                default: {	// Ha a felsorolt gombok közül egyiket sem nyomta meg a játékos, hibaüzenetet kap, ami 1.5s múlva el is tűnik
                                    setCursorPosition(75,*shopASCII + 15);
                                    cout << "Helytelen input!" << endl;
                                    Sleep(1500);
                                    setCursorPosition(0,*shopASCII+28);
                                    cout << "                                                                                                                                    ";
                                } break;
                            }
                        } while (!itemPicked);	// do-while ciklus vége (BOLT)
                    }
                    else {	// Ha a játékosnak nincs 1 kulcsa sem, nem léphet be a boltba
                        setCursorPosition(0,*doorHeight+6);
                        cout << "\t\t\t\tNincs elegendő kulcs a belépéshez!" << endl;
                        Sleep(1500);
                        setCursorPosition(0,*doorHeight+6);
                        cout << "                                                                                                                                    ";
                    }
                    shuffleArray(shopGoods);	// Árukat tároló vektor elemeinek összekeverése, hogy a következő megnyitásnál más áruk legyenek
                }
                    // ---- Kijárat (debuffok) ----
                else if(pickDoor == RIGHT){
                    if(debuffs.size() > 5){
                        do
                        {
                            shuffleArray(debuffs);	// Az árukat tároló vektor összekeverése
                        } while ((debuffs[0].type == debuffs[1].type) ||
                                 (debuffs[0].type == debuffs[2].type) ||
                                 (debuffs[1].type == debuffs[2].type));
                    }
                    else {shuffleArray(debuffs);}
                    setCursorPosition(0,0);
                    readFile("../txtFiles/doorsRight.txt", 7, "\t\t\t\t");
                    Sleep(2000);
                    system("cls");
                    int debuffsASCIIRows = countRows("../txtFiles/debuffsASCII.txt");
                    exitDisplay(h, *player, debuffs, allBosses, *debuffsASCII, debuffsASCIIRows, i, dodgePercent, bossName);
                    Sleep(2000);
                    do
                    {
                        int pickShopItems = _getch();
                        if (pickShopItems == 0 || pickShopItems == 0xE0) pickShopItems = _getch();
                        switch(pickShopItems){	// Felsorolt gyengítések választásához szükséges input
                            case LEFT: {		// Első gyengítés választása
                                player->keys++;	// Játékos kap 1 kulcsot miután választott
                                pickDebuff(*player, debuffs, allBosses, *dodgeChance, i, 0);
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "                                                                                                                                    ";
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "\t\t\t\t" << debuffs[0].name << "kiválasztva!" << endl;
                                Sleep(4000);
                                debuffs.erase(debuffs.begin());							// Választás után a gyengítés törlése a vektorból, hogy ne ismétlődjön később
                                *itemPicked=true;
                            } break;
                            case UP:{			// Második gyengítés választása
                                player->keys++;
                                pickDebuff(*player, debuffs, allBosses, *dodgeChance, i, 1);
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "                                                                                                                                    ";
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "\t\t\t\t" << debuffs[1].name << "kiválasztva!" << endl;
                                Sleep(4000);
                                debuffs.erase(debuffs.begin()+1);
                                *itemPicked=true;
                            } break;
                            case RIGHT: {		// Harmadik gyengítés választása
                                player->keys++;
                                pickDebuff(*player, debuffs, allBosses, *dodgeChance, i, 2);
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "                                                                                                                                    ";
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "\t\t\t\t" << debuffs[2].name << "kiválasztva!" << endl;
                                Sleep(4000);
                                debuffs.erase(debuffs.begin()+2);
                                *itemPicked=true;
                            } break;
                            case ESC: exit(0);	        // ESC-re leáll a program
                            default: {					// Ha a felsorolt gombok közül egyiket sem nyomja meg a felhasználó, hibaüzenetet kap
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "                                                                                                                                    ";
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "Helytelen input!" << endl;
                                Sleep(1500);
                                setCursorPosition(0,(*debuffsASCII*3) + 31);
                                cout << "                                                                                                                                    ";
                            } break;
                        }
                    } while (!itemPicked);
                    shuffleArray(debuffs);	// Gyengítéseket tároló vektor összekeverése, hogy a következő megnyitáskor ne ismétlődjenek
                    Sleep(2000);
                    setCursorPosition(0,0);
                }
                else if (pickDoor == ESC) {system("cls"); exit(0);}	// ESC-re leáll a program
                else {						// Ha nem sikerült helyes gombot lenyomni
                    SetConsoleOutputCP(1250);
                    cout << "\t" << playerName;
                    SetConsoleOutputCP(65001);
                    cout << ", válassz ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";
                    Sleep(2000);
                }
            } while (!itemPicked);	// do-while ciklus vége (kijárat)
        }
            // ----Jobb ajtó választása (harc)----
        else if(pressedChar == RIGHT && i < allBosses.size()){
            setCursorPosition(0,0);
            readFile("../txtFiles/doorsRight.txt", 7, "\t\t\t\t");
            Sleep(2000);
            system("cls");
            *bossHeight = allBosses[i].getBoss(allBosses[i].fileName, allBosses[i].color, *bossHeight);	// Megfelelő szörny megjelenítése, ASCII art sorainak számának eltárolása
            int middleX = allBosses[i].middlePoint();												// Szörny vízszintes közepének meghatározása
            int longestRow = countRows("../Enemies/" + allBosses[i].fileName);						//Szörny függőleges közepének meghatározása
            setCursorPosition(middleX, *bossHeight + 6);
            SetConsoleTextAttribute(h, allBosses[i].color);
            cout << "\n\t\t\t\t\t\t   " << allBosses[i].name << "\n" << endl;
            SetConsoleTextAttribute(h, 7);
            displayStats(allBosses, *player,i, dodgePercent, longestRow + 20, (*bossHeight / 2) - 6);					// Játékos és szörny tulajdonságok megjelenítése
            combatInteractions(player, allBosses, &i, *combatOption, longestRow, *bossHeight, dodgePercent, dodgeChance, bossName, playerName, gameOver);
            i++;																// A harcnak vége, ciklusváltozó nő 1-gyel (azért, hogy a következő harcban más szörny legyen)
        }
        else if(pressedChar == ESC) {system("cls"); break;}					    // ESC-re kilép a program
        else {																	// Ha nem sikerült helyes gombot lenyomni
            SetConsoleOutputCP(1250);
            cout << playerName;
            SetConsoleOutputCP(65001);
            cout << "válassz ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";
            Sleep(2000);
        }
    } while (!*gameOver);
}
#endif //TOKFILKOK_MAIN_H
