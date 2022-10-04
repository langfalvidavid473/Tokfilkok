#include "classes.h"
#ifndef UTILITIES_H
#define UTILITIES_H


// ---- Kurzor mozgató függvény ----
// y az oszlop, x a sor (Azért vannak megcserélve, mert általában az oszlop 0,
// a sorral kell számolgatni, ezért a függvény hívásakor így egyszerűbbnek találtam)
void setCursorPosition(int y, int x)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)y, (SHORT)x };
    SetConsoleCursorPosition(hOut, coord);
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

// Vektor keverő függvény

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

vector<Debuffs> debuffSystem (){
	vector<Debuffs> debuffs;
	string myText;	// Fájl egy sora
	ifstream MyReadFile("../txtFiles/debuffs.txt");	// Fájl megnyitása
	while (getline(MyReadFile, myText)) {	// Fájl soronkénti olvasása
		string name = myText.substr(myText.find("name:")+5,myText.find("value:",myText.find("name:")+5)-5);
		stringstream value(myText.substr(myText.find("value:")+6,myText.find("type:")-(myText.find("value:")+6))); 
		string type = myText.substr(myText.find("type:")+5,myText.length());
		int v;
		value >> v;
		Debuffs *d = new Debuffs(name,v,type);
		debuffs.push_back(*d);
	}
	MyReadFile.close();	// Fájl bezárása
	return debuffs;
}

#endif