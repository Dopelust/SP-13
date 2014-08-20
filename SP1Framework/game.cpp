// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

void missile();
void ulti();
void createEnemy();

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD missileRLocation;
COORD missileLLocation;
COORD ultiLocation;
COORD enemyLocation[20];
COORD deathLocation;
COORD consoleSize;
COORD nullLocation;
bool createMissileL = 0;
bool createMissileR = 0;
bool createUlti = 0;
int score = 0; 
int heart = 5;
int currentWave = 1;
int ultiBar = 0;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 0;
    charLocation.Y = consoleSize.Y / 2;  

	enemyLocation[0].X = 72; 
	enemyLocation[0].Y = rand() % 20 + 2 ; 

	nullLocation.X = '\0' ; 
	nullLocation.Y = '\0' ; 

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
    keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_Z] = isKeyPressed(0x5A);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	if (score == (3*((currentWave*currentWave) + (3*currentWave))/2))
	{
		score--;
		if ( heart < 10)
		{
			heart++;
		}
		currentWave++;
	}

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0 && charLocation.Y != 2)
    {
        charLocation.Y--; 
    }

    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        charLocation.Y++; 
    }

	missile();
	ulti();
	createEnemy();

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE] || heart <= 0)
	{
        g_quitGame = true;    
	}

}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
	/*
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
							0xFA, 0xFB, 0xFC, 0xFD
	                        };
	*/
    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x0A);
    std::cout << 1.0 / deltaTime << "fps";
	
	gotoXY(17, 1);
	colour(0x0B);
	for (int i = 0; i < ultiBar/10; i++)
	{
		std::cout << char(4) << " ";
	}

	gotoXY(52,0); 
	colour(0x0A);
	std::cout << score << " score"; 

	gotoXY(35,0);
	colour(0x0A);
	std::cout << "Wave " << currentWave; 

	gotoXY(deathLocation); 
	colour(0x7C); 
	std::cout << "BOOM";
	deathLocation = nullLocation ; 

	gotoXY(17,0); 
	colour(0x0C); 
	for (int i = 0; i < heart; i++)
	{
		std::cout << char(3) << " ";
	}

    gotoXY(0, 0);
    colour(0x09);
    std::cout << elapsedTime << "Time" << std::endl;

    // render character

	for ( int i = 0; i != currentWave; i++)
	{
		gotoXY(enemyLocation[i]); 
		colour(0x0F); 
		std::cout << "Enemy" ; 
	}

    gotoXY(charLocation);
    colour(0x09);
    std::cout << "  |\________________ " << std::endl;
	std::cout << "  |     ==== _______|"  << std::endl;
	std::cout << "__/___  ====_/       ";

	if (createUlti == 1)
	{
		gotoXY(ultiLocation);
		colour(0x0C);
		for ( int i = 14; i < ultiLocation.X; i++)
		{
			std::cout << "=";
		}
	}

	gotoXY(missileRLocation);
	colour(0x0C);  
	std::cout << "---=====>>"; 

	gotoXY(missileLLocation);
	colour(0x0C);
	std::cout << "---=====>>";

}

void missile()
{
	if (keyPressed[K_SPACE])
    {
		if (createMissileR == 0)
		{
			//Beep(10,200);
			createMissileR = 1;
		}

		else if (createMissileR == 1 && createMissileL == 0)
		{
			//Beep(10,200);
			createMissileL = 1;
		}
	}

	if (createMissileR == 1)
	{
		missileRLocation.X+=10;

		if (missileRLocation.X > consoleSize.X - 1)
		{
			createMissileR = 0;
			missileRLocation.X = charLocation.X + 10;
			missileRLocation.Y = charLocation.Y + 1;
		}
	}

	else
	{
		missileRLocation.X = charLocation.X + 10 ;
		missileRLocation.Y = charLocation.Y + 1 ;
	}

	if (createMissileL == 1)
	{
		missileLLocation.X+=10;

		if (missileLLocation.X > consoleSize.X - 1)
		{
			createMissileL = 0;
			missileLLocation.X = charLocation.X;
			missileLLocation.Y = charLocation.Y + 1;
		}
	}

	else
	{
		missileLLocation.X = charLocation.X;
		missileLLocation.Y = charLocation.Y + 1;
	}
}

void ulti()
{
	if (keyPressed[K_Z] && ultiBar == 50)
    {
		createUlti = 1;
	}

	if (createUlti == 1)
	{
		ultiLocation.X = consoleSize.X;
		ultiLocation.Y = charLocation.Y + 2;
		ultiBar--;

		if (ultiBar == 0)
		{
			createUlti = 0;
		}
	}
}

void createEnemy()
{
	for ( int i = 0; i != currentWave; i++)
	{
		enemyLocation[i].X--;

		if ( (enemyLocation[i].X <= missileRLocation.X && enemyLocation[i].Y == missileRLocation.Y) ) 
		{ 
			deathLocation = enemyLocation[i] ; 
			enemyLocation[i].X = consoleSize.X - 5;
			enemyLocation[i].Y = rand() % 20 + 3 ;
			score ++;

			createMissileR = 0;
			missileRLocation.X = charLocation.X + 10 ;
			missileRLocation.Y = charLocation.Y + 1 ;

			if (ultiBar < 50)
			{
				ultiBar +=2;
			}
		} 

		if (enemyLocation[i].X <= missileLLocation.X && enemyLocation[i].Y == missileLLocation.Y)
		{
			deathLocation = enemyLocation[i] ; 
			enemyLocation[i].X = consoleSize.X - 5;
			enemyLocation[i].Y = rand() % 20 + 3 ;
			score ++;
 
			createMissileL = 0;
			missileLLocation.X = charLocation.X;
			missileLLocation.Y = charLocation.Y + 1;

			if (ultiBar < 50)
			{
				ultiBar +=2;
			}
		}

		if (enemyLocation[i].Y == ultiLocation.Y) 
		{ 
			enemyLocation[i].X = consoleSize.X - 5;
			enemyLocation[i].Y = rand() % 20 + 3 ;
			score ++; 
		} 

		if (enemyLocation[i].X < 1 )
		{
			enemyLocation[i].X = consoleSize.X - 5;
			enemyLocation[i].Y = rand() % 20 + 3;
			heart--; 
		}

		for ( int j = 0 ; j < 21 ; j++ ) 
		{ 
			for ( int k = 0 ; k < 3 ; k++ ) 
			{ 
				if ( enemyLocation[i].X == charLocation.X + j && enemyLocation[i].Y == charLocation.Y + k)
				{ 
					enemyLocation[i].X = consoleSize.X - 5;
					enemyLocation[i].Y = rand() % 20 + 3 ;
					heart--; 
				} 
			} 
		} 


	}
	
}