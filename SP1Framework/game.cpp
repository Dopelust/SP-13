#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

//Requisite
COORD consoleSize;
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

//Player
int heart = 5;
int score = 0; 
COORD charLocation;
COORD missileRLocation;
bool createMissileR = 0;
COORD missileLLocation;
bool createMissileL = 0;
COORD ultiLocation;
bool createUlti = 0;
int ultiBar = 50;

//Enemy
int currentWave = 1;
COORD enemyLocation[20];

//Boss
Boss Pink;
Boss Zebra;

//PowerUps
bool laserSight = 0;

//Misc
COORD deathLocation;
COORD nullLocation;

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

	if (score >= (3*((currentWave*currentWave) + (3*currentWave))/2) && currentWave < 20)
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

    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1 && charLocation.Y != 21)
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

	//player render
    renderPlayer();

	gotoXY(deathLocation); 
	colour(0x7C); 
	std::cout << "BOOM"; 
	deathLocation = nullLocation; 
	
    //renders the UI - hearts, wave number, etc.
	renderUI();
	
	//enemy render
	for ( int i = 0; i != currentWave; i++)
	{
		gotoXY(enemyLocation[i]); 
		colour(0x02); 
		std::cout << "Enemy" ; 
	}

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
		missileRLocation.X+=8;

		if (missileRLocation.X >= consoleSize.X - 5)
		{
			createMissileR = 0;
			missileRLocation.X = charLocation.X + 8;
			missileRLocation.Y = charLocation.Y + 1;
		}
	}

	else
	{
		missileRLocation.X = charLocation.X + 8 ;
		missileRLocation.Y = charLocation.Y + 1 ;
	}

	if (createMissileL == 1)
	{
		missileLLocation.X+=8;

		if (missileLLocation.X >= consoleSize.X - 5)
		{
			createMissileL = 0;
			missileLLocation.X = charLocation.X + 2;
			missileLLocation.Y = charLocation.Y + 1;
		}
	}

	else
	{
		missileLLocation.X = charLocation.X + 2;
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
		ultiLocation.Y = charLocation.Y + 1;
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

		else if (enemyLocation[i].X < 18 )
		{

		for ( int j = 0 ; j < 17 ; j++ ) 
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) 
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
	
}

void renderUI()
{
	gotoXY(0, 0);
    colour(0x0F);
    std::cout << elapsedTime << "Time" << std::endl;

	gotoXY(14,0);
	colour(0x0F);
	std::cout << "Wave " << currentWave;

	gotoXY(25,0); 
	colour(0x0C); 
	for (int i = 0; i < heart; i++)
	{
		std::cout << char(3) << " ";
	}

	gotoXY(25, 1);
	colour(0x0B);
	for (int i = 0; i < ultiBar/10; i++)
	{
		std::cout << char(4) << " ";
	}

	gotoXY(38,1); 
	colour(0x0F);
	if (currentWave == 2)
	{
		std::cout << "Wave 1 Complete! Laser Sight Installed.";
		laserSight = true;
	}
	if (currentWave == 6)
	{
		std::cout << "Score: ";
	}
	if (currentWave == 11)
	{
		std::cout << "Score: ";
	}

	gotoXY(50,0); 
	colour(0x0F);
	std::cout << "Score: " << score;

	gotoXY(70, 0);
    colour(0x0F);
    std::cout << 1.0 / deltaTime << "fps";
}

void renderPlayer()
{

	gotoXY(charLocation);
    colour(0x07);
    std::cout << "  /---\\_________" << std::endl;
	std::cout << " |____________|_|";
	if (createUlti == true)
	{
		gotoXY(ultiLocation);
		colour(0x0B);
		for ( int i = 18; i < ultiLocation.X; i++)
		{
			std::cout << "=";
		}
		colour(0x07);
	}
	else if (laserSight == true)
	{
		colour(0x04);
		for ( int i = 18; i < consoleSize.X; i++)
		{
			std::cout << "-";
		}
		colour(0x07);
	}
	std::cout << std::endl << "  /===========\\" << std::endl ;
	std::cout << "  \\_@_@_@_@_@_/";

	gotoXY(missileRLocation);
	colour(0x0C);  
	std::cout << "--===>"; 

	gotoXY(missileLLocation);
	colour(0x0C);
	std::cout << "--===>";

}