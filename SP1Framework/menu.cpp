#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

using namespace::std;

COORD pointerLocation;
extern bool g_playGame;
char P;

void menu()
{
	system("cls");
	colour(0x0A);
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

	if ( x < Exit && x > 0 ) 
	{
		gameMenu(x); 
	} 

	else if ( x == Exit )  
	{ 
		colour(0x0C);
		cout << "Closing Application" << endl ;
		colour(0x07);
		exit(1); 
	} 

	else if ( x != Exit || x == 0  ) 
	{ 
		menu(); 
	}
}

void gameMenu(int x)
{
	ifstream Read;
	string words ; 
	Read.open ("highscores.txt" ) ;

	ifstream Read2;
	string names ; 
	Read2.open ("highscorename.txt" ) ;

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
			colour(0x0C);
			system("cls") ; 
			cout<<"                         ----Goodbye! see you soon!----"<<endl;
			cout<<"                          ";
			exit(1);
		}
		else 
		{
			exit(1);
			cout <<" Error unknown input" <<endl;
		}
		break;
		// HighScore
	case 3: cout <<"                                 Top Highscores! "<< endl; 
		if (Read.is_open() && Read2.is_open()) 
		{ 
			for ( int z = 0 ; z < 5 ; z++ )  
			{
				colour(0x0F);
				getline(Read,words);
				colour(0x0F);
				getline(Read2,names);
				cout <<"                          "<< z+1  << ".  "<< names << "     " << words << endl ;
				colour(0x0A);
			}

		}
		cout <<"                        ----Return to Main Menu ? (Y/N) -----"<< endl;
		cin >> P;
		if(P =='Y' || P=='y')
		{
			menu();
		}
		else if (P=='N' || P=='n')
		{
			colour(0x0C);
			system("cls") ; 
			cout<<"                         ----Goodbye! see you soon!----"<<endl;
			cout<<"                          ";
			exit(1);
		}
		else 
		{
			exit(1);
			cout <<" Error unknown input" <<endl;
		}
		break;
		//Rules
	case 4: cout << "                         Rules are simple: "<< endl<<endl;
		cout << "   1: Defend your base (5 lives) "<< endl;
		cout << "   2: Space to shoot rockets to defend "<<endl;
		cout << "   3: Arrow keys to move up and down" << endl;
		cout << "   4: Press Z to fire your laser!(Has cooldown)" << endl;
		cout << "   5: For every wave you clear, you will recieve 1 extra heart (10 total)" << endl<< endl;
		cout << "                         -----Return to menu? (Y/N)-----" <<endl <<endl;
		cin >> P;
		if(P =='Y' || P=='y')
		{
			menu();
		}
		else if (P=='N' || P=='n')
		{
		    colour(0x0C);
			system("cls") ; 
			cout<<"                         ----Goodbye! see you soon!----"<<endl;
			cout<<"                          ";
			exit(1);
		}
		else 
		{

			exit(1);
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

		    colour(0x0C);
			system("cls") ; 
			cout<<"                         ----Goodbye! see you soon!----"<<endl;
			cout<<"                          ";
			exit(1);
		}
		else 
		{
			exit(1);
			cout <<" Error unknown input" <<endl;
		}
		break;
	}
}

void pause()
{
	system ("cls");
	cout << " Game Paused! " << endl;
	cout << "1. Resume " <<endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Quit" << endl;
	int u;
	cin >> u;

	if ( u < 4 && u>0 ) 
	{
		system("cls") ; 

		switch(u)
		{
			//Game Start
		case 1 :
			break;
			//Options
		case 2: g_playGame = false;
			menu();
			break;
		case 3 : g_quitGame = true;
			break;
		}
	} 
}