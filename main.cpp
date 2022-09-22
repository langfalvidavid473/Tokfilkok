#include "./Utilities/utilities.cpp"
#include "./Utilities/classes.h"

#define LEFT 75
#define RIGHT 77
#define ESC 27

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



int main() {
	system("cls");
	SetConsoleOutputCP(CP_UTF8); // UTF-8 karakterek megjelenítése
	SetConsoleCP(1250);
	string name;
	int i = 0;
	char pressedChar, combatOption;
	bool gameOver=false;
	vector<Bosses> allBosses = generateBoss();
	cout << "Játékos neve: "; getline(cin,name);
	name[0] = toupper(name[0]);		// Nagy kezdőbetű a neveknek (cctype)
	Player player(1000,300,50);
	readFile("./txtFiles/bevezeto.txt", 2, "");
	system("pause");
	do
	{
		BlockInput(false); 
		readFile("./txtFiles/doors.txt", 7, "\t\t\t\t\t\t");
		newLine();
		SetConsoleOutputCP(1250);	// UTF-8 változóból kiíratáshoz
		cout << name;
		SetConsoleOutputCP(65001);	// UTF-8 általános kiíratáshoz
		cout << ", " << "válassz egy ajtót jobb vagy bal nyíl használatával!" << endl;
		pressedChar = _getch();
		if (pressedChar == 0 || pressedChar == 0xE0) pressedChar=_getch();
		if(pressedChar == LEFT && i < 16){
			readFile("./txtFiles/doorsLeft.txt", 7, "\t\t\t\t\t\t");
			Sleep(2000);
			cout << "Balra";
		}
		else if(pressedChar == RIGHT && i < 16){
			readFile("./txtFiles/doorsRight.txt", 7, "\t\t\t\t\t\t");
			Sleep(2000);
			allBosses[i].getBoss(allBosses[i].name,6);
			displayStats(allBosses, player, i);
				do
				{	
					BlockInput(false);
					combatOption = _getch();
					BlockInput(true);
					if (combatOption == 0 || combatOption == 0xE0) combatOption = _getch();
					if (combatOption == RIGHT && i < 16){
						newLine();
						cout << "\tTámadás!!!" << endl;
						Sleep(3000);
						allBosses[i].health -= player.damage;
						allBosses[i].getBoss(allBosses[i].name,6);
						displayStats(allBosses, player, i);
						newLine();
						cout << "\t" << player.damage << " sebzést okoztál!" << endl;
						Sleep(3000);
					if(allBosses[i].health >= 1){
						allBosses[i].getBoss(allBosses[i].name,6);
						displayStats(allBosses, player, i);
						newLine();
						cout << "\tSzörny támad!" << endl;
						Sleep(3000);
						player.health -= (allBosses[i].damage - player.armor);
						allBosses[i].getBoss(allBosses[i].name,6);
						displayStats(allBosses, player, i);
						newLine();
						cout << "\t" << allBosses[i].damage - player.armor << " sebzést szenvedtél!" << endl;
						Sleep(2000);
						allBosses[i].getBoss(allBosses[i].name,6);
						displayStats(allBosses, player, i);
						
					}
					else {
						newLine();
						cout << "\tGratulálok! Győztél!" << endl;
						Sleep(2000);
						}
					if(player.health <= 0) {
						newLine();
						cout << "Game over!" << endl;
						Sleep(2000);
						gameOver = true;}
					}
					else if(combatOption == ESC) {system("cls"); return 0;}
				} while ((player.health >= 0) && (allBosses[i].health >= 0));
			i++;
		}
		else if(pressedChar == ESC) {system("cls"); return 0;}
		else {
			SetConsoleOutputCP(1250);
			cout << name;
			SetConsoleOutputCP(65001);
			cout << "válassz ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";
			}
		newLine();
	} while (!gameOver);
	
	return 0;
}