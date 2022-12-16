#include "main.h"

int main(){
    system("cls");
    // Alap parancssori beállítások
    HANDLE h = basicSettingsAndVariableDeclarations();
    // Fő ciklus
    gameLoop(h);
    return 0;
}