#include "main.h"
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
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 		// Parancssor hívása
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);	// Kurzor villogásának eltűntetése
    string playerName;									// Játékos neve
    float dodgeChance = 150;                            // Kitérés esélye (alapértelmezett 30%)
    int i = 0;											// Ciklusváltozó (akkor nő, ha egy szörny meghal)
    int combatOption;			                        // Különböző változók felhasználói bemenet ellenőrzésére
    int bossHeight, doorHeight, doorLeftHeight,
    shopASCII, debuffsASCII;	                        // Különböző ASCII artok magasságának és szélességének megszámolására
    bool gameOver = false, itemPicked;					// gameOver akkor igaz, ha a játékos meghal, itemPicked változót boltnál és kijáratnál használjuk
    vector<Bosses> allBosses = generateBoss("../Enemies");// Szörnyek
    vector<ShopItems> shopGoods = shopSystem("../txtFiles/shop.txt", &dodgeChance);			// Áruk (bolt)
    int shopRefresh = 300;								// Áruk frissítésének költsége
    vector<Debuffs> debuffs = debuffSystem("../txtFiles/debuffs.txt", &dodgeChance);			// Kijárat (gyengítések)
    shuffleArray(shopGoods);
    shuffleArray(debuffs);
    cout << "Játékos neve: "; getline(cin,playerName);
    playerName[0] = toupper(playerName[0]);				// Nagy kezdőbetű a neveknek (cctype)
    Player player(1500,300,50,0,0);						// Játékos(élet,sebzés,páncél,arany,kulcsok)
    readFile("../txtFiles/bevezeto.txt",2);				// Bevezető fájl beolvasása
    system("pause");
    system("cls");
    // Fő ciklus
    gameLoop(h, &player, allBosses, shopGoods, debuffs, i, &dodgeChance, playerName, shopRefresh, &gameOver, &itemPicked, &bossHeight, &doorHeight, &doorLeftHeight, &shopASCII, &debuffsASCII, &combatOption);
    if(i > allBosses.size()){
        Sleep(2000);
        system("cls");
        readFile("../txtFiles/victory.txt", 7);
        _getch();
    }
    return 0;
}