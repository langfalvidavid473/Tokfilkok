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

void readFile(string fileName, int color, string tab,int rows) {
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


// ---- Ellenfelek generálása (random értékek) ----

vector<Bosses> generateBoss(){
	vector<string> v = getFileNames("./Enemies");	// A mappában lévő összes txt fájl nevének eltárolása

	random_device rd;	//Random biteket generál, melyeket a default_random_engine felhasznál
    default_random_engine rng(rd());	// Random számokat generál a kapott bitek alapján
    shuffle(v.begin(), v.end(), rng);	// Szörnyek sorrendjének keverése

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

// hp poti: 25-50-100 --- 300 arany (egyszeri)

// hp buff poti: 2-4-10 --- 500 arany

// damage buff poti: 2-4-10 --- 500 arany

// armor buff poti: 2-5-10 --- 300 arany

// kitérés buff poti: +5% --- 400 arany

// növény hp debuff: 5-10-15 --- 500 arany

// növény damage debuff: 2-5-10 --- 300 arany

// hp debuff poti: 1-3-9 --- +1 kulcs

// damage debuff poti: 1-3-9 --- +1 kulcs

// armor debuff poti: 1-4-9 --- +1 kulcs

			// string name = v[i].substr(0,v[i].length()-4);	// Beolvasott .txt fájlok formázása (kiterjesztés elhagyása)
vector<ShopItems> shopSystem (){
	vector <string> v;
	vector <ShopItems> shopVector;
	string myText;	// Fájl egy sora
	// string comma = "oti";
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
