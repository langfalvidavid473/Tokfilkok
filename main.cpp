#include "./Utilities/utilities.cpp"
#include "./Utilities/classes.h"

#define LEFT 75
#define RIGHT 77

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
	SetConsoleOutputCP(65001); // UTF-8 karakterek megjelenítése

	string name;
	int hp, dmg;
	int i = 0;
	char pressedChar;
	bool gameOver=false;
	vector<Bosses> allBosses = generateBoss();
	cout << "Játékos neve: "; getline(cin,name);
	Player player(1500,300,name);
	readFile("./txtFiles/bevezeto.txt",2);
	system("pause");
	do
	{
		readFile("./txtFiles/doors.txt",7);
		newLine();
		cout << name << ", " << "kérem válasszon egy ajtót jobb vagy bal nyíl használatával!" << endl;
		pressedChar = _getch();
		if (pressedChar == 0 || pressedChar == 0xE0) pressedChar=getch();
		if(pressedChar == LEFT){
			cout << "Balra";
		}
		else if(pressedChar == RIGHT){
			allBosses[i].getBoss(allBosses[i].name,6);
			cout <<"\tHealth: " << allBosses[i].health <<
		 	"\tDamage: " << allBosses[i].damage << endl;
		}
		else {cout << "Kérem válasszon ajtót jobb, illetve bal nyilak valamelyikének lenyomásával!";}
		newLine();
		system("pause");
	} while (!gameOver);
	
	return 0;
}