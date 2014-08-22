#include "Framework\timer.h"
#include "game.h"
#include <iostream>

using namespace::std;

extern bool g_playGame;
char P;

void menu()
{
	system("cls");
	cout<<" ###       ###        #######                       #####  ######          ### "<<endl;
	cout<<"  #  ##### ###  ####  #     # #    # ###### #####  #     # #     # # ##### ### "<<endl;
	cout<<"  #    #    #  #      #     # #    # #      #    # #     # #     # #   #   ###"<<endl;
	cout<<"  #    #   #    ####  #     # #    # #####  #    #  #####  ######  #   #    #  "<<endl;
	cout<<"  #    #            # #     # #    # #      #####  #     # #     # #   #       "<<endl;
	cout<<"  #    #       #    # #     #  #  #  #      #   #  #     # #     # #   #   ### "<<endl;
	cout<<" ###   #        ####  #######   ##   ###### #    #  #####  ######  #   #   ###"<<endl<< endl;
	cout<<"                Welcome! This is our game - It's Over 8 Bit!!."<<endl;
	cout<<"                            1. Start Game" <<endl;
	cout<<"                            2. Options" << endl;
	cout<<"                            3. Highscore" << endl;
	cout<<"                            4. Rules" << endl;
	cout<<"                            5. Credits" << endl;
	cout<<"                            6. Exit" <<endl;
	cout<<"                   *Input number in menu and press enter " << endl;
	cout<<"--------------------------------------------------------------------------------";
	cout<<" Your input : " ;

	int x;
	cin >> x ;

	if (x > 7 || x < 0)
	{
		menu();
	}

	else if (x < 7 && x > 0 )
	{
		gameMenu(x);
	}

	else
	{
		cout << "Closing Application" << endl;
	}

}

void gameMenu(int x)
{
	system("cls") ; 
	switch(x)
	{
		//Game Start
	case 1 : g_playGame = true;
		break;
		//Options
	case 2: cout << "-Options- " <<endl;
		cout <<"                        ----Return to Main Menu ? (Y/N) -----"<< endl;
		cin >> P;
		if(P =='Y' || P=='y')
		{
			menu();
		}
		else if (P=='N' || P=='n')
		{
			cout<<"Goodbye! see you soon!      ";
		}
		else 
		{
			cout <<" Error unknown input" <<endl;
		}
		break;
		// HighScore
	case 3: cout <<"                          Welcome to the Hall of Fame! "<< endl;
		cout <<"                        ----Return to Main Menu ? (Y/N) -----"<< endl;
		cin >> P;
		if(P =='Y' || P=='y')
		{
			menu();
		}
		else if (P=='N' || P=='n')
		{
			cout<<"Goodbye! see you soon!      ";
		}
		else 
		{
			cout <<" Error unknown input" <<endl;
		}
		break;
		//Rules
	case 4: cout << "                         Rules are simple: "<< endl;
		cout << "                         1: Defend your base (5 lives) "<< endl;
		cout << "                         2: Space to shoot rockets to defend "<<endl;
		cout << "                         3: Arrow keys to move up and down" << endl << endl;
		cout << "                         -----Return to menu? (Y/N)-----" <<endl <<endl;
		cin >> P;
		if(P =='Y' || P=='y')
		{
			menu();
		}
		else if (P=='N' || P=='n')
		{
			cout<<"Goodbye! see you soon!      ";
		}
		else 
		{
			cout <<" Error unknown input" <<endl;
		}
		break;
	case 5: cout <<"Made by : Ricsson , Jun Sen , Andy , Lazarus" << endl;
		cout << "                         -----Return to menu? (Y/N)-----" <<endl <<endl;
		cin >> P;
		if(P =='Y' || P=='y')
		{
			menu();
		}
		else if (P=='N' || P=='n')
		{
			cout<<"Goodbye! see you soon!      ";
		}
		else 
		{
			cout <<" Error unknown input" <<endl;
		}
		break;
	}
}