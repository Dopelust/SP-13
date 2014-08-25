// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "Framework\console.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
using std::cin;

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 10; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

bool g_playGame = 1;
extern int heart;
extern string names;
void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	while (!g_playGame)
	{
		menu();
	}

	init();      // initialize your variables
	mainLoop();  // main loop
	shutdown();  // do clean up, if any. free memory.

	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame

    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      

		if ( heart <= 0)
		{
			colour(0x0A);
			system ("cls");
			cout << ""<< endl;
			cout << "   ______                             ___                        "<< endl; 
			cout << " .' ___  |                          .'   `.                      "<< endl;
			cout << "/ .'   \_| ,--.  _ .--..--. .---.  /  .-.  \_   __ .---. _ .--.  "<< endl;
			cout <<" | |   ____`'_\ :[ `.-. .-. / /__\\ | |   | [ \ [  / /__\[ `/'`\] "<< endl;
			cout << "\ `.___]  // | |,| | | | | | \__., \  `-'  /\ \/ /| \__.,| |    "<< endl;
			cout << " `._____.'\'-;__[___||__||__'.__.'  `.___.'  \__/  '.__.[___]  "<< endl << endl;
			cout << " Please enter your name : " ;
			cin >> names;
			system ("cls");
			updateScore();
			g_quitGame= true;
		}
	}    
}
