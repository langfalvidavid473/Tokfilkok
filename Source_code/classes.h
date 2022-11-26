#ifndef CLASSES_H
#define CLASSES_H
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

#include <iostream>		// Alapvető input, output műveletekhez
#include <fstream>		// Fájlból olvasáshoz
#include <string>		// Sztringekkel való munkálatokhoz, getline() használatához
#include <windows.h>	// Parancssorral történő interakciókhoz
#include <random>		// Véletlenszerű értékek generálásához
#include <filesystem>	// fájlokkal való munkálatokhoz
#include <vector>		// Az elemek könnyebb tárolásához
#include <algorithm>	// shuffle()
#include <cctype>		// toupper() 
#include <cstdio>		// getchar()
#include <conio.h>		// getch()
#include <locale>		// UTF-8 karakterek kiírása
#include <future>		// delay
#include <WinUser.h>	// BlockInput()
// #include <typeinfo>
#include <sstream>



using namespace std;

#pragma execution_character_set( "utf-8" ) // UTF-8 karakterek engedélyezése

// ---- Játékos ----

class Player {
public:
	int health, damage, armor, gold, keys;
	Player(int hp, int dmg, int arm, int g, int k) {
		health = hp;
		damage = dmg;
		armor = arm;
		gold = g;
		keys = k;
	}
};

// ---- Szörnyek ----

class Bosses {
public:
	int health, level, damage, color;
	string fileName, name;
	Bosses(int hp, int lvl, int dmg, string fn, string n, int c)  { 
		health = hp;
		level = lvl;
		damage = dmg;
		fileName = fn;
		name = n;
		color = c;
	}
	// ---- Adott ellenfél beolvasása fájlból, ASCII art stílusban ----
		int getBoss(string fn,int color1, int rows=0) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Parancssor hívása 
		string myText;
		ifstream MyReadFile("../Enemies/" + fn);
		SetConsoleTextAttribute(h, color1); // Parancssor betűszín változtatás
		cout << "\n\n\n\n\n";
		while(getline(MyReadFile, myText)){
		if(myText.find("name") != std::string::npos ){MyReadFile.close();}
		else{
			cout << "\t\t" << myText << endl;
			rows++;
		}
		}
		MyReadFile.close();
		SetConsoleTextAttribute(h, 7);
		return rows;
		}
		int middlePoint(){			// ASCII art középpontjának keresése
			int middlePoint = 0;
			int row = 0;
			int i = 0;
			string myText;								// Fájl egy sora
			ifstream MyReadFile("../Enemies/" + fileName);				// Fájl megnyitása
			while (getline(MyReadFile, myText))
			{ 
				row = myText.length();
				middlePoint += row;
				i++;
			}
			MyReadFile.close(); // Fájl bezárása
			return middlePoint / i;
		}
	};


class ShopItems{
public:
int price, value, type, color;
string name, attribute;
bool buff;
ShopItems(string n, int t, int p, int v, bool b, string a, int c){
	name = n;
	type = t;
	price = p;
	value = v;
	buff = b;
	attribute = a;
	color = c;
}
};

class Debuffs{
	public:
	int value, type;
	string name, attribute;
	Debuffs(string n, int v, int t, string a){
		value = v;
		name = n;
		type = t;
		attribute = a;
	}
};



#endif 