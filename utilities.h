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
	COORD coord = {(SHORT)y, (SHORT)x};
	SetConsoleCursorPosition(hOut, coord);
}

// Segédfüggvény ellenfelek generálásához (megszámolja a fájlokat az adott mappában)

int countEnemies(const string& filename)
{
	int count = 0;
	std::filesystem::path p1{filename};
	for (auto &p : std::filesystem::directory_iterator(p1))
	{
		++count;
	}
	return count;
}

// ---- Függvény általános fájlból olvasáshoz + kiíráshoz ----

auto readFile(const string& fileName, int color, const string& tab = "", int rows = 0)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Parancssor hívása
	string myText;								// Fájl egy sora
	ifstream MyReadFile(fileName);				// Fájl megnyitása
	SetConsoleTextAttribute(h, color);			// Parancssor betűszín változtatás
	cout << "\n\n";

	while (getline(MyReadFile, myText))
	{ // Fájl soronkénti kiírása
		cout << tab << myText << endl;
		rows++;
	}
	MyReadFile.close(); // Fájl bezárása
	SetConsoleTextAttribute(h, 7);
	return rows;
}

auto countRows(const string& fileName){
	int longestRow = 0;
	string myText;								// Fájl egy sora
	ifstream MyReadFile(fileName);				// Fájl megnyitása
	while (getline(MyReadFile, myText))
	{ 
		if(myText.length() > longestRow){
			longestRow = myText.length();
		}	
	}
	MyReadFile.close(); // Fájl bezárása
	return longestRow;
}

// Segédfüggvény egy adott mappában lévő fájlok neveinek tárolásához
/*
Működés: végigmegy a mappa fájljain, eltárolja a nevüket <filesystem> formátumban,
ezt sztringgé konvertálja, a mappa elérési útját levágja a .substr() metódussal,
majd eltárolja egy sztring típusú vektorban
*/

vector<string> getFileNames(const string& path)
{
	vector<string> fileNames;
	for (const auto &entry : std::filesystem::directory_iterator(path))
	{
		string act = entry.path().string();
		fileNames.push_back(act.substr(10, act.length()));
	}
	return fileNames;
}

// ---- Random generátor ----

int generateNum(int from, int to)
{

	mt19937 rng(random_device{}());
	uniform_int_distribution<> dist(from, to);
	auto random_number = dist(rng);
	return random_number;
}

// Négyzetgyök függvény

int sqr(int a)
{
	return a * a;
}

// Új sor függvény

void newLine()
{
	cout << endl;
}

// Vektor keverő függvény

template <typename T>

void shuffleArray(vector<T> &v)
{
	random_device rd;				  // Random biteket generál, melyeket a default_random_engine felhasznál
	default_random_engine rng(rd());  // Random számokat generál a kapott bitek alapján
	shuffle(v.begin(), v.end(), rng); // Szörnyek sorrendjének keverése
}

// ---- Ellenfelek generálása (random értékek) ----

vector<Bosses> generateBoss(const string& filename)
{
	vector<string> v = getFileNames(filename); // A mappában lévő összes txt fájl nevének eltárolása

	shuffleArray(v);

	vector<Bosses> allBosses; // Ez a vektor lesz feltöltve a generált objektumokkal

	for (int i = 0; i < v.size(); i++)
	{ // Amennyi szörny van az adott mappában, annyi objektum jön létre (könnyen bővíthető!!!)

		int randomHealth = 1000 + generateNum((sqr(i + 1) * 60) - i * 100, (sqr(i + 1) * 70) - i * 100); // Random értékek generálása (1)
		int randomDamage = 150 + generateNum(sqr(i + 1) * 10, sqr(i + 1) * 20);							 // (2)
		string myText;
		string name;
		string color;
		int correctColor;
		ifstream MyReadFile("../Enemies/" + v[i]);
		while (getline(MyReadFile, myText))
		{
			if (myText.find("name") != std::string::npos)
			{
				name = (myText.substr(myText.find("name:") + 5, myText.length()));
			}

			if (myText.find("color") != std::string::npos)
			{
				color = (myText.substr(myText.find("color:") + 6, myText.length()));
				if (color == "red")
					correctColor = 4;
				else if (color.find("green") != std::string::npos)
					correctColor = 2;
				else if (color.find("blue") != std::string::npos)
					correctColor = 1;
				else if (color.find("yellow") != std::string::npos)
					correctColor = 6;
				else if (color.find("aqua") != std::string::npos)
					correctColor = 3;
				else if (color.find("purple") != std::string::npos)
					correctColor = 5;
				else if (color.find("white") != std::string::npos)
					correctColor = 7;
				else if (color.find("gray") != std::string::npos)
					correctColor = 8;
				else
					correctColor = 7;
			}
		}
		MyReadFile.close();
		Bosses *newBoss = new Bosses(randomHealth, i + 1, randomDamage, v[i], name, correctColor); // Új objektum létrehozása, értékek hozzárendelése konstruktorral
		allBosses.push_back(*newBoss);															   // vektor feltöltése a generált objektummal
	}

	return allBosses;
}

void displayStats(vector<Bosses> boss, Player player, int i, float dodge, int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Parancssor hívása 
	SetConsoleTextAttribute(h, 7); // Parancssor betűszín változtatás (fehér)
	string bossNameEnglishChars = boss[i].fileName.substr(1, boss[i].fileName.length()-5);
    string bossName = boss[i].name.substr(boss[i].name.find(' ', bossNameEnglishChars.length() - 2) ,boss[i].name.length());
	bossName[0] = toupper(bossName[0]);
	setCursorPosition(x + 20, y - 2);
	cout << "\t" << "━━━━━━━━━━━━━━━";
	setCursorPosition(x + 20, y - 1);
	cout << "\t" << "┃ INTERAKCIÓK ┃";
	setCursorPosition(x + 20, y);
	cout << "\t" << "━━━━━━━━━━━━━━━";
	setCursorPosition(x + 20, y + 4);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 6);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 8);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 14);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 16);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 2);
		SetConsoleTextAttribute(h, 4);	// Parancssor betűszín változtatás (piros)
	cout << "\tTámadás [->]";
	setCursorPosition(x + 20, y + 4);
		SetConsoleTextAttribute(h, 6);	// Parancssor betűszín változtatás (sárga)
	cout << "\tKitérés (" << dodge << "%) [<-]";
	setCursorPosition(x + 20, y + 6);
		SetConsoleTextAttribute(h, 8);	// Parancssor betűszín változtatás (szürke)
	cout << "\tKilépés [ESC]";
		SetConsoleTextAttribute(h, 7); // Parancssor betűszín változtatás (fehér)
	setCursorPosition(x + 20, y + 10);
	cout << "\t" << "━━━━━━━━━━━━━━━━━━";
	setCursorPosition(x + 20, y + 11);
	cout << "\t" << "┃ JÁTÉKOS STATOK ┃";
	setCursorPosition(x + 20, y + 12);
	cout << "\t" << "━━━━━━━━━━━━━━━━━━";
		SetConsoleTextAttribute(h, 2); // Parancssor betűszín változtatás (zöld)
	setCursorPosition(x + 20, y + 14);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 14);
	cout << "\tÉlet: " << player.health;
		SetConsoleTextAttribute(h, 3); // Parancssor betűszín változtatás (aqua)
	setCursorPosition(x + 20, y + 16);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 16);
	cout << "\tSebzés: " << player.damage;
		SetConsoleTextAttribute(h, 5); // Parancssor betűszín változtatás (lila)
	setCursorPosition(x + 20, y + 18);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 18);
	cout << "\tPáncél: " << player.armor;
		SetConsoleTextAttribute(h, 7); // Parancssor betűszín változtatás (fehér)
	setCursorPosition(x + 20, y + 22);
	cout << "\t" << "━━━━━━━━━━━━━━━━━━";
	setCursorPosition(x + 20, y + 23);
	cout << "\t" << "┃ SZÖRNY STATOK  ┃";
	setCursorPosition(x + 20, y + 24);
	cout << "\t" << "━━━━━━━━━━━━━━━━━━";
	SetConsoleTextAttribute(h, 2); // Parancssor betűszín változtatás (zöld)
	setCursorPosition(x + 20, y + 26);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 26);
	cout << "\t" << bossName << " élete: " << boss[i].health;
	SetConsoleTextAttribute(h, 3); // Parancssor betűszín változtatás (aqua)
	setCursorPosition(x + 20, y + 28);
	cout << "                                                                  ";
	setCursorPosition(x + 20, y + 28);
	cout << "\t" << bossName << " sebzése: " << boss[i].damage;
	SetConsoleTextAttribute(h, 7); // Parancssor betűszín változtatás

}

vector<ShopItems> shopSystem(const string& path)
{
	vector<ShopItems> shopVector;
	string myText;			   // Fájl egy sora
	ifstream MyReadFile(path); // Fájl megnyitása
	while (getline(MyReadFile, myText))
	{ // Fájl soronkénti olvasása
		string name = myText.substr(myText.find("name:") + 5, myText.find("type:", myText.find("name:") + 5) - 5);
		stringstream type(myText.substr(myText.find("type:") + 5, myText.find("price:") - (myText.find("type:") + 5)));
		stringstream price(myText.substr(myText.find("price:") + 6, myText.find("value:") - (myText.find("price:") + 6)));
		stringstream value(myText.substr(myText.find("value:") + 6, myText.find("buff:") - (myText.find("value:") + 6)));
		stringstream buff(myText.substr(myText.find("buff:") + 5, myText.length()));
		unsigned int p, v, t;
		bool b;
		type >> t;
		price >> p;
		value >> v;
		buff >> b;
		// (t > 4) && (t < 8) ? v = generateNum(v, v * 1.1) : v = generateNum(v, v * 0.9);
		if(t>3 && t<8){
			v = generateNum(v, v * 1.1);
		}
		else if(t>7){
			v = generateNum(v * 0.9, v);
		}
		p = generateNum(p, p * 1.1 );
		stringstream attr;
		int color;
		switch(t){
			case 1: attr << "ÉLET + " << v; color = 2; break;
			case 2: attr << "SEBZÉS + " << v; color = 3;  break;
			case 3: attr << "PÁNCÉL + " << v; color = 5;  break;
			case 4: attr << "ÉLET + " << v - 100 << '%'; color = 2;  break;
			case 5: attr << "SEBZÉS + " << v - 100 << '%'; color = 3; break;
			case 6: attr << "PÁNCÉL + " << v - 100 << '%'; color = 5;  break;
			case 7: attr << "KITÉRÉS + " << v - 100 << '%'; color = 9;  break;
			case 8: attr << "SZÖRNY ÉLET - " << 100 - v << '%'; color = 4;  break;
			case 9: attr << "SZÖRNY SEBZÉS - " << 100 - v << '%'; color = 4;  break;
			default: attr << ""; break;
		}
		string attribute = attr.str();
		ShopItems *s = new ShopItems(name, t, p, v, b, attribute, color);
		shopVector.push_back(*s);
	}
	MyReadFile.close(); // Fájl bezárása
	return shopVector;
}

vector<Debuffs> debuffSystem(const string& path)
{
	vector<Debuffs> debuffs;
	string myText;			   // Fájl egy sora
	ifstream MyReadFile(path); // Fájl megnyitása
	while (getline(MyReadFile, myText))
	{ // Fájl soronkénti olvasása
		string name = myText.substr(myText.find("name:") + 5, myText.find("value:", myText.find("name:") + 5) - 5);
		stringstream value(myText.substr(myText.find("value:") + 6, myText.find("type:") - (myText.find("value:") + 6)));
		stringstream type(myText.substr(myText.find("type:") + 5, myText.length()));
		int v, t;
		value >> v;
		type >> t;
		t > 4 ? v = generateNum(v, v * 1.1) : v = generateNum(v * 0.9, v);
		stringstream attr;
        int color;
		switch(t){
			case 1: attr << "ÉLET - " << 100 - v << '%'; color=2; break;
			case 2: attr << "SEBZÉS - " << 100 - v << '%'; color=3; break;
			case 3: attr << "KITÉRÉS - " << 100 - v << '%'; color=9; break;
			case 4: attr << "PÁNCÉL - " << 100 - v << '%'; color=5; break;
			case 5: attr << "SZÖRNY ÉLET + " << v - 100 << '%'; color=4; break;
			case 6: attr << "SZÖRNY SEBZÉS + " << v - 100 << '%'; color=4; break;
			default: attr << ""; break;
		}
		string attribute = attr.str();
		Debuffs *d = new Debuffs(name, v, t, attribute, color);
		debuffs.push_back(*d);
	}
	MyReadFile.close(); // Fájl bezárása
	return debuffs;
}

#endif