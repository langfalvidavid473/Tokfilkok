#include "classes.h"



// x is the column, y is the row. The origin (0,0) is top-left.
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}



void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    
    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

// Segédfüggvény ellenfelek generálásához (megszámolja a fájlokat az adott mappában)

int countEnemies(string filename) {
	int count = 0;
	std::filesystem::path p1 { filename };
	for (auto& p : std::filesystem::directory_iterator(p1)) {
		++count;
	}
	return count;
}

// ---- Függvény általános fájlból olvasáshoz + kiíráshoz ----

auto readFile(string fileName, int color, string tab="",int rows=0) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	// Parancssor hívása 
		string myText;	// Fájl egy sora
		ifstream MyReadFile(fileName);	// Fájl megnyitása
		SetConsoleTextAttribute(h, color);	// Parancssor betűszín változtatás 
		cout << "\n\n";	

		while (getline(MyReadFile, myText)) {	// Fájl soronkénti kiírása
			cout << tab << myText << endl;
			rows++;
		}
		MyReadFile.close();	// Fájl bezárása
		SetConsoleTextAttribute(h, 7);
		return rows;
	}

void getFileContent(string fileName) {
		string myText;	// Fájl egy sora
		ifstream MyReadFile(fileName);	// Fájl megnyitása
		while (getline(MyReadFile, myText)) {	// Fájl soronkénti olvasása
		}
		MyReadFile.close();	// Fájl bezárása
	}

// Segédfüggvény egy adott mappában lévő fájlok neveinek tárolásához
/*
Működés: végigmegy a mappa fájljain, eltárolja a nevüket <filesystem> formátumban, 
ezt sztringgé konvertálja, a mappa elérési útját levágja a .substr() metódussal,
majd eltárolja egy sztring típusú vektorban
*/

vector<string> getFileNames(string path){
	vector<string> fileNames;
    for (const auto & entry : std::filesystem::directory_iterator(path)){
	string act = entry.path().string();
	fileNames.push_back(act.substr(10,act.length()));
	}
	return fileNames;
}

// ---- Random generátor ----

int generateNum(int from, int to) {
	
	mt19937 rng(random_device{}());
	uniform_int_distribution<> dist(from, to);
	auto random_number = dist(rng);
	return random_number;
}

// Négyzetgyök függvény

int sqr(int a){
	return a*a;
}

// Új sor függvény

void newLine(){
	cout << endl;
}

template <typename T>

void shuffleArray(vector<T> &v){
	random_device rd;	//Random biteket generál, melyeket a default_random_engine felhasznál
    default_random_engine rng(rd());	// Random számokat generál a kapott bitek alapján
    shuffle(v.begin(), v.end(), rng);	// Szörnyek sorrendjének keverése
}

// ---- Ellenfelek generálása (random értékek) ----

vector<Bosses> generateBoss(){
	vector<string> v = getFileNames("../Enemies");	// A mappában lévő összes txt fájl nevének eltárolása

	shuffleArray(v);

	vector<Bosses> allBosses;	// Ez a vektor lesz feltöltve a generált objektumokkal

		for(int i=0; i < v.size(); i++){	// Amennyi szörny van az adott mappában, annyi objektum jön létre (könnyen bővíthető!!!)

			int randomHealth = 1000+generateNum((sqr(i+1)*60)-i*100,(sqr(i+1)*70)-i*100);	// Random értékek generálása (1)
			int randomDamage = 150+generateNum(sqr(i+1)*10,sqr(i+1)*20);	// (2)
			
			Bosses *newBoss = new Bosses(randomHealth,i+1,randomDamage,v[i]);	// Új objektum létrehozása, értékek hozzárendelése konstruktorral
			allBosses.push_back(*newBoss);	// vektor feltöltése a generált objektummal
		}

	return allBosses;
}

// ---- Delay függvény ----

template <typename... ParamTypes>

    void setTimeOut(int milliseconds,std::function<void(ParamTypes...)> func,ParamTypes... parames)
    {   
        std::async(std::launch::async,[=]()
        {       
            Sleep(milliseconds);
            func(parames...); 
        });
     };

void displayStats(vector<Bosses> boss, Player player, int i){
	cout << "\tTámadás [->]\t" << "Kitérés [<-]\t" << "Kilépés [ESC]\n" << endl;
	cout << "\tYour health: " << player.health <<
			"\tYour damage: " << player.damage <<
			"\tYour armor: "  << player.armor << endl;
		cout <<	"\tBoss health: " << boss[i].health <<
		 	"\tBoss damage: " << boss[i].damage << endl;
}


vector<ShopItems> shopSystem (){
	vector<ShopItems> shopVector;
	string myText;	// Fájl egy sora
	ifstream MyReadFile("../txtFiles/shop.txt");	// Fájl megnyitása
	while (getline(MyReadFile, myText)) {	// Fájl soronkénti olvasása
		string name = myText.substr(myText.find("name:")+5,myText.find("price:",myText.find("name:")+5)-5);
		stringstream price(myText.substr(myText.find("price:")+6,myText.find("value:")-(myText.find("price:")+6))); 
		stringstream value(myText.substr(myText.find("value:")+6,myText.find("buff:")-(myText.find("value:")+6)))  ;
		stringstream buff(myText.substr(myText.find("buff:")+5,myText.length())) ;
		int p,v;
		bool b;
		price >> p;
		value >> v;
		buff >> b;
		ShopItems *s = new ShopItems(name,p,v,b);
		shopVector.push_back(*s);
	}
	MyReadFile.close();	// Fájl bezárása
	return shopVector;
}

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

// vector<ShopItems> shopGoods = shopSystem();
// shuffleArray(shopGoods);
// cout << shopGoods[0].name << "\t" << shopGoods[0].value << "\t" << shopGoods[0].price << "\t" << shopGoods[0].buff;

	system("cls");
	SetConsoleOutputCP(CP_UTF8); // UTF-8 karakterek megjelenítése
	SetConsoleCP(1250);
	string playerName;
	int hp, dmg, armor;
	int i = 0;
	int pressedChar, combatOption, pickDoor, pickDebuff, pickShopItems;
	bool gameOver=false, itemPicked;
	vector<Bosses> allBosses = generateBoss();
	vector<ShopItems> shopGoods = shopSystem();
	cout << "Játékos neve: "; getline(cin,playerName);
	playerName[0] = toupper(playerName[0]);		// Nagy kezdőbetű a neveknek (cctype)
	Player player(1500,300,50);
	readFile("../txtFiles/bevezeto.txt",2);
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
		cout << playerName;
		SetConsoleOutputCP(65001);	// UTF-8 általános kiíratáshoz
		cout << ", " << "válassz egy ajtót jobb vagy bal nyíl használatával!" << endl;
		pressedChar = _getch();		// User inputra várakozás, majd a kapott karakter eltárolása
		if (pressedChar == 0 || pressedChar == 0xE0) pressedChar = _getch();	// Virtuális karakterek (nyilak) nem 1 értéket adnak vissza, ezért plusz ellenőrzés szükséges
		if(pressedChar == LEFT && i < 16){			// ----Bal ajtó választása----
			setCursorPosition(0,0);
			int doorLeftHeight = readFile("../txtFiles/doorsLeft.txt", 7, "\t\t\t\t",doorLeftHeight);
			Sleep(1500);
			do
			{
			itemPicked = false;
			setCursorPosition(0,0);
			readFile("../txtFiles/doors.txt", 7, "\t\t\t\t");
			setCursorPosition(0,doorHeight+4);
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
				cout << "\telső [<]" << "\tmásodik [^]" << "\tharmadik [>]" << "\trefresh [v]" << "\tkilépés [ESC]\n";
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
						setCursorPosition(0, shopASCII+5);
						cout << "\t\t\t\t" << shopGoods[0].name << "\t" << shopGoods[1].name << "\t" << shopGoods[2].name << endl;
						cout << "\t\t\t\t" << shopGoods[0].price << "\t" << shopGoods[1].price << "\t" << shopGoods[2].price << endl;
					} break;	
					case ESC: return 0; break;
					default: {
						cout << "nem jó input";
						Sleep(2000);
						readFile("../txtFiles/shop.txt", 7, "\t\t\t\t");	// Bolt menü beolvasása
						newLine();
						newLine();
						cout << "\telső [<]" << "\tmásodik [^]" << "\tharmadik [>]" << "\trefresh [v]" << "\tkilépés [ESC]\n";
						} break;
				}
				} while (!itemPicked);
				
				Sleep(1500);
			}
			// ---- Kijárat ----
			else if(pickDoor == RIGHT){
				readFile("../txtFiles/doorsRight.txt", 7, "\t\t\t\t");
				Sleep(2000);
				readFile("../txtFiles/debuffs.txt", 7, "\t\t\t\t");	// Gyengítés "rendszer" beolvasása
				newLine();
				newLine();
				cout << "\telső [<]" << "\tmásodik [^]" << "\tharmadik [>]" << "\tkilépés [ESC]\n";
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
							cout << "nem jó input";
							Sleep(2000);
							readFile("../txtFiles/debuffs.txt", 7, "\t\t\t\t");
							newLine();
							newLine();
							cout << "\telső [<]" << "\tmásodik [^]" << "\tharmadik [>]" << "\tkilépés [ESC]\n";
						} break;
				}
				} while (!itemPicked);
				Sleep(3000);
			}
			else {										// Ha nem sikerült helyes gombot lenyomni
			SetConsoleOutputCP(1250);
			cout << playerName;
			SetConsoleOutputCP(65001);
			cout << "válassz ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";
			Sleep(2000);
			}
			} while (!itemPicked);
		}
			
		// ----Jobb ajtó választása (harc)----
		else if(pressedChar == RIGHT && i < 16){	
			setCursorPosition(0,0);	
			readFile("../txtFiles/doorsRight.txt", 7, "\t\t\t\t");
			Sleep(2000);
			system("cls");
			setCursorPosition(0,0);
			int bossHeight = allBosses[i].getBoss(allBosses[i].name,6,bossHeight);	// Megfelelő szörny megjelenítése
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
