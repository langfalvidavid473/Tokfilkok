#include "classes.h"

// Segédfüggvény ellenfelek generálásához (megszámolja a fájlokat az adott mappában)

int countEnemies(string filename) {
	int count = 0;
	std::filesystem::path p1 { filename };
	for (auto& p : std::filesystem::directory_iterator(p1)) {
		++count;
	}
	return count;
}

// ---- Függvény általános fájlból olvasáshoz ----

void readFile(string fileName, int color, string tab) {
		system("cls");	// Terminál sorainak törlése
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	// Parancssor hívása 
		string myText;	// Fájl egy sora
		ifstream MyReadFile(fileName);	// Fájl megnyitása
		SetConsoleTextAttribute(h, color);	// Parancssor betűszín változtatás 
		cout << "\n\n";	
		while (getline(MyReadFile, myText)) {	// Fájl soronkénti kiírása
			cout << tab << myText << endl;
		}
		MyReadFile.close();	// Fájl bezárása
		SetConsoleTextAttribute(h, 7);
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
			// string name = v[i].substr(0,v[i].length()-4);	// Beolvasott .txt fájlok formázása (kiterjesztés elhagyása)
			
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
		system("cls");
     };

void displayStats(vector<Bosses> boss, Player player, int i){
	cout << "\tTámadás [->]\t" << "Kitérés [<-]\t" << "Kilépés [ESC]\n" << endl;
	cout << "\tYour health: " << player.health <<
			"\tYour damage: " << player.damage <<
			"\tYour armor: "  << player.armor  << "\n\n" <<
			"\tBoss health: " << boss[i].health <<
		 	"\tBoss damage: " << boss[i].damage << endl;
}