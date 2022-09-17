#include "./Utilities/utilities.cpp"
#include "./Utilities/classes.h"

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
	readFile("./txtFiles/bevezeto.txt",2);
	vector<Bosses> allBosses = generateBoss();
	for (size_t i = 0; i < allBosses.size(); i++)
	{
		cout << "Name: " << allBosses[i].name << "\tHealth: " << allBosses[i].health 
		<< "\tDamage: " << allBosses[i].damage << "\tLevel: " << allBosses[i].level << endl;
	}
	getchar();
	return 0;
}