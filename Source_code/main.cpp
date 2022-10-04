#include "utilities.h"

/*
		  ===============
		  |C++ színkódok|
		  ===============
 
1		Blue	9	Light Blue
2		Green	0	Black
3		Aqua	A	Light Green
4		Red		B	Light Aqua
5		Purple	C	Light Red
6		Yellow	D	Light Purple
7		White	E	Light Yellow
8		Gray	F	Bright White
*/

int main(){
	system("cls");
	SetConsoleOutputCP(CP_UTF8); 						// UTF-8 karakterek megjelenítése
	SetConsoleCP(1250);
	string playerName;									// Játékos neve
	int bossHeight;										// Fájlból beolvasott szörny magassága (sorok száma)
	int i = 0;											// Ciklusváltozó (akkor nő, ha egy szörny meghal)
	int pressedChar, combatOption, pickDoor,			// Különböző változók felhasználói bemenet ellenőrzésére
	pickDebuff, pickShopItems;
	bool gameOver = false, itemPicked;					// gameOver akkor igaz, ha a játékos meghal, itemPicked változót boltnál és kijáratnál használjuk
	vector<Bosses> allBosses = generateBoss();			// Szörnyek
	vector<ShopItems> shopGoods = shopSystem();			// Áruk (bolt)	
	vector<Debuffs> debuffs = debuffSystem();			// Kijárat (gyengítések)
	cout << "Játékos neve: "; getline(cin,playerName);
	playerName[0] = toupper(playerName[0]);				// Nagy kezdőbetű a neveknek (cctype)
	Player player(1500,300,50);							// Játékos
	readFile("../txtFiles/bevezeto.txt",2);				// Bevezető fájl beolvasása
	system("pause");
	// Fő ciklus
	do
	{
		BlockInput(false);	/* User input engedélyezése (BlockInput függvény használata 
							   rendszergazdaként való futtatást igényel, anélkül nem működik) */
		system("cls");
		int doorHeight = readFile("../txtFiles/doors.txt", 7, "\t\t\t\t",doorHeight);	// Ajtók beolvasása fájlból
		newLine();
		newLine();
		SetConsoleOutputCP(1250);	// UTF-8 változóból kiíratáshoz
		cout << "\t" << playerName;
		SetConsoleOutputCP(65001);	// UTF-8 általános kiíratáshoz
		cout << ", " << "válassz egy ajtót jobb vagy bal nyíl használatával!" << endl;
		pressedChar = _getch();		// User inputra várakozás, majd a kapott karakter eltárolása
		if (pressedChar == 0 || pressedChar == 0xE0) pressedChar = _getch();	// Virtuális karakterek (nyilak) nem 1 értéket adnak vissza, ezért plusz ellenőrzés szükséges
		if(pressedChar == LEFT && i < 16){			// ----Bal ajtó választása----
			setCursorPosition(0,0);	/*
									Kurzor pozíciója (innen kezdődik a nyomtatás)
									A program működésének egyik fő eleme. Ha nem felülírnánk a nyomtatott karaktereket,
									hanem minden képfrissítésnél törölnénk az egész kimenetet, akkor minden egyes alkalommal
									villanna egyet a kép, ami nagyon zavaró. Ezzel a módszerrel ezt kiküszöböltük, csak az
									változik, aminek az adott pillanatban szükséges.
									*/
			int doorLeftHeight = readFile("../txtFiles/doorsLeft.txt", 7, "\t\t\t\t",doorLeftHeight);
			Sleep(1500);
			do
			{
			itemPicked = false;
			system("cls");
			readFile("../txtFiles/doors.txt", 7, "\t\t\t\t");
			setCursorPosition(0,doorHeight+4); // Azért 4-et adunk hozzá, mivel az elején 2 új sor van,
											   // hogy ne érjen a képernyő tetejéhez, utána pedig további 2, hogy kényelmesen elférjen.
			cout << "\t\t\t\t\t\t\t\t\tBolt" << "\t\t\t\t\t\t\t\t\t" << "Kijárat" << endl;
			pickDoor = _getch();
			if (pickDoor == 0 || pickDoor == 0xE0) pickDoor = _getch();
			// ---- Bolt ----
			if(pickDoor == LEFT){
				setCursorPosition(0,0);
				readFile("../txtFiles/doorsLeft.txt", 7, "\t\t\t\t");
				Sleep(2000);
				system("cls");
				int shopASCII = readFile("../txtFiles/shopASCII.txt", 7, "\t\t\t\t", shopASCII);	// Bolt menü beolvasása
				setCursorPosition(0, shopASCII+5);
				cout << "\t\t\t\t" << shopGoods[0].name << "\t" << shopGoods[1].name << "\t" << shopGoods[2].name << endl;
				cout << "\t\t\t\t" << shopGoods[0].price << "\t" << shopGoods[1].price << "\t" << shopGoods[2].price << endl;
				newLine();
				newLine();
				cout << "\t" << shopGoods[0].name <<"[<]" << "\t" << shopGoods[1].name << "[^]" << "\t" << shopGoods[2].name << "[>]" << "\tFrissítés (300 arany) [v]" << "\tKilépés [ESC]\n";
				Sleep(2000);
				itemPicked=false;
				do
				{
				pickShopItems = _getch();
				if (pickShopItems == 0 || pickShopItems == 0xE0) pickShopItems = _getch();
				switch(pickShopItems){
					case LEFT: cout << "első item"; itemPicked=true; break;
					case UP: cout << "második item"; itemPicked=true; break;
					case RIGHT: cout << "harmadik item"; itemPicked=true; break;
					case DOWN: {
						shuffleArray(shopGoods);
						setCursorPosition(0, shopASCII+5);
						cout << "\x1b[2K";
						setCursorPosition(0, shopASCII+6);
						cout << "\x1b[2K";
						setCursorPosition(0, shopASCII+5);
						cout << "\t\t\t\t" << shopGoods[0].name << "\t" << shopGoods[1].name << "\t" << shopGoods[2].name << endl;
						cout << "\t\t\t\t" << shopGoods[0].price << "\t" << shopGoods[1].price << "\t" << shopGoods[2].price << endl;
						setCursorPosition(0,shopASCII+9);
						cout << "\x1b[2K";
						setCursorPosition(0,shopASCII+9);
						cout << "\t" << shopGoods[0].name <<"[<]" << "\t" << shopGoods[1].name << "[^]" << "\t" << shopGoods[2].name << "[>]" << "\tFrissítés (300 arany) [v]" << "\tKilépés [ESC]\n";
					} break;	
					case ESC: return 0; break;
					default: {
						setCursorPosition(0,shopASCII+8);
						cout << "nem jó input";
						Sleep(1500);
						setCursorPosition(0,shopASCII+8);
						cout << "\x1b[2K";
						} break;
				}
				} while (!itemPicked);
				
				Sleep(1500);
			}
			// ---- Kijárat ----
			else if(pickDoor == RIGHT){
				setCursorPosition(0,0);
				readFile("../txtFiles/doorsRight.txt", 7, "\t\t\t\t");
				Sleep(2000);
				system("cls");
				int debuffsASCII = readFile("../txtFiles/debuffsASCII.txt", 4, "\t\t\t\t", debuffsASCII);	// Gyengítés "rendszer" beolvasása
				setCursorPosition(0, debuffsASCII+4);
				cout << "\t\t\t\t" << debuffs[0].name << "\t" << debuffs[1].name << "\t" << debuffs[2].name << endl;
				cout << "\t\t\t\t" << debuffs[0].value << "\t" << debuffs[1].value << "\t" << debuffs[2].value << endl;
				newLine();
				newLine();
				cout << "\t" << debuffs[0].name << "[<]" << "\t" << debuffs[1].name << "[^]" << "\t" << debuffs[2].name << "[>]" << "\tKilépés [ESC]\n";
				do
				{
					pickShopItems = _getch();
					if (pickShopItems == 0 || pickShopItems == 0xE0) pickShopItems = _getch();
					switch(pickShopItems){
						case LEFT: cout << "első item"; itemPicked=true; break;
						case UP: cout << "második item"; itemPicked=true; break;
						case RIGHT: cout << "harmadik item"; itemPicked=true; break;
						case ESC: return 0; break;
						default: {
							setCursorPosition(0,debuffsASCII+11);
							cout << "nem jó input";
							Sleep(1500);
							setCursorPosition(0,debuffsASCII+11);
							cout << "\x1b[2K";
						} break;
				}
				} while (!itemPicked);
				Sleep(3000);
			}
			else if (pickDoor == ESC) {system("cls"); return 0;}
			else {										// Ha nem sikerült helyes gombot lenyomni
			SetConsoleOutputCP(1250);
			cout << "\t" << playerName;
			SetConsoleOutputCP(65001);
			cout << ", válassz ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";
			Sleep(2000);
			}
			} while (!itemPicked);
		}
			
		// ----Jobb ajtó választása (harc)----
		else if(pressedChar == RIGHT && i < 16){	
			bossHeight = 0;
			setCursorPosition(0,0);	
			readFile("../txtFiles/doorsRight.txt", 7, "\t\t\t\t");
			Sleep(2000);
			system("cls");
			bossHeight = allBosses[i].getBoss(allBosses[i].name,6,bossHeight);	// Megfelelő szörny megjelenítése
			setCursorPosition(0,bossHeight+3);
			displayStats(allBosses, player, i);			// Játékos és szörny tulajdonságok megjelenítése
				do
				{	
					BlockInput(false);					// User input engedélyezése, hogy ismét lehessen választani
					combatOption = _getch();			// Változó a harc közben lenyomható billentyűkre
					BlockInput(true);					/* User input megszűntetése (azért, hogy tudjon automatikusan működni a harc,
														   ne lépjen fel semmi furcsa jelenség, ha a felhasználó nyomkodja a gombokat) */
					if (combatOption == 0 || combatOption == 0xE0) combatOption = _getch();
					if (combatOption == RIGHT && i < 16){ // Jobb nyíl lenyomása (támadás)
						setCursorPosition(0,bossHeight+8);
						cout << "\tTámadás!!!" << endl;
						Sleep(2000);
						allBosses[i].health -= player.damage;
						setCursorPosition(0,bossHeight+5);
						cout << "\x1b[2K";
						setCursorPosition(0,bossHeight+6);
						cout << "\x1b[2K";
						setCursorPosition(0,bossHeight+3);
						displayStats(allBosses, player, i);
						setCursorPosition(0,bossHeight+10);
						cout << "\t" << player.damage << " sebzést okoztál!" << endl;
						Sleep(2000);
					if (allBosses[i].health >= 1) {		// Ha a szörnynek maradt élete, támadjon vissza, ha nincs, akkor a játékos győzőtt
						setCursorPosition(0,bossHeight+8);
						cout << "\tSzörny támad!" << endl;
						Sleep(2000);
						player.health -= (allBosses[i].damage - player.armor);
						setCursorPosition(0,bossHeight+5);
						cout << "\x1b[2K";
						setCursorPosition(0,bossHeight+6);
						cout << "\x1b[2K";
						setCursorPosition(0,bossHeight+3);
						displayStats(allBosses, player, i);
						setCursorPosition(0,bossHeight+10);
						cout << "\t" << allBosses[i].damage - player.armor << " sebzést szenvedtél!" << endl;
						Sleep(2000);
						setCursorPosition(0,bossHeight+8);
						cout << "\x1b[2K";
						setCursorPosition(0,bossHeight+10);
						cout << "\x1b[2K";
					}
					else {
						newLine();
						cout << "\tGratulálok! Győztél!" << endl;
						Sleep(2000);
						}
					if(player.health <= 0) {									// Ha a játékosnak elfogyott az élete, vége a játéknak
						newLine();
						cout << "Game over!" << endl;
						Sleep(2000);
						gameOver = true;
						}
					}
					else if(combatOption == ESC) {system("cls"); return 0;}		// ESC-re kilép a program (harc közben is)
					else {
						setCursorPosition(0,bossHeight+10);
						SetConsoleOutputCP(1250);
						cout << playerName;
						SetConsoleOutputCP(65001);
						cout << ", a folytatáshoz nyomd le a fent látható gombok egyikét!" << endl;
						Sleep(2000);
						// allBosses[i].getBoss(allBosses[i].name,6);
						// displayStats(allBosses, player, i);
					}
			
				
					
				} while ((player.health >= 0) && (allBosses[i].health >= 0));	// Ha mind két félnek maradt élete, folytatódhat a harc
			i++;																// A harcnak vége, ciklusváltozó nő 1-gyel (azért, hogy a következő harcban más szörny legyen)
		}
		else if(pressedChar == ESC) {system("cls"); return 0;}					// ESC-re kilép a program
		else {																	// Ha nem sikerült helyes gombot lenyomni
			SetConsoleOutputCP(1250);
			cout << playerName;
			SetConsoleOutputCP(65001);
			cout << "válassz ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";
			Sleep(2000);
			}
	
	} while (!gameOver);														// Ha a változó hamis, folytatódhat a játék
	


	return 0;
}