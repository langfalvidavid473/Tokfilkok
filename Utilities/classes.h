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
#include <typeinfo>

using namespace std;

#pragma execution_character_set( "utf-8" ) // UTF-8 karakterek engedélyezése

// ---- Játékos ----

class Player {
public:
	int health, damage, armor;
	Player(int hp, int dmg, int arm) {
		health = hp;
		damage = dmg;
		armor = arm;
	}
};

// ---- Szörnyek ----

class Bosses {
public:
	int health, level, damage;
	string name;
	Bosses(int hp, int lvl, int dmg, string n1)  { 
		health = hp;
		level = lvl;
		damage = dmg;
		name = n1;
	}
	// ---- Adott ellenfél beolvasása fájlból, ASCII art stílusban ----
		int getBoss(string fileName, int color,int rows) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Parancssor hívása 
		string myText;
		ifstream MyReadFile("../Enemies/" + fileName);
		SetConsoleTextAttribute(h, color); // Parancssor betűszín változtatás 
		while (getline(MyReadFile, myText)) {
			cout << "\t\t" << myText << endl;
			rows++;
		}
		MyReadFile.close();
		SetConsoleTextAttribute(h, 7);
		return rows;
	}
};

class ShopItems{
public:
int price, value;
string name;
bool buff;
ShopItems(string n, int p, int v, bool b){
	name = n;
	price = p;
	value = v;
	buff = b;
}
};

class Debuffs{
	public:
	int value;
	string name, type;
	Debuffs(int v, string n, string t){
		value = v;
		name = n;
		type = t;
	}
};



#endif 