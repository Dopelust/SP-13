#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
extern bool g_playGame;
extern void gameMenu(int x);
extern void menu();
using namespace::std;
void Inmenu();
void Ingame(int u);
enum Menu
{
	resume,
	MM,
	quit,
};

void Inmenu()
{
	system ("cls");
	cout << " Game Paused! " << endl;
	cout << "1. Resume " <<endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Quit" << endl;
	int u;
	cin >> u;

	if ( u < quit && u>0 ) 
	{
		Ingame(u);
	} 
}
void Ingame(int u)
{
	system("cls") ; 
	switch(u)
	{
		//Game Start
	case 1 : g_playGame = true;
		break;
		//Options
	case 2: g_playGame = false;
		menu();
		break;
	case 3 : exit(1);
		break;
	}
}