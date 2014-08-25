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
COORD missileRLocation[2];
bool createMissileR[2] = {0,0};
COORD missileLLocation[2];
bool createMissileL[2] = {0,0};
COORD ultiLocation;
bool createUlti = 0;
int ultiBar = 50;

//Enemy
int currentWave = 1;
bool spawnenemy[20] ; 
COORD enemyLocation[20];

//Boss
Boss Pink;
Boss Zebra;

//PowerUps
bool laserSight = 1;
bool fourMissiles = 1;

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
		enemyLocation[currentWave-1].X = consoleSize.X - 5;
		enemyLocation[currentWave-1].Y = rand() % 20 + 3 ;	
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
	collisions();

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE] || heart <= 0)
	{
		updateScore();
        g_quitGame = true;    
	}

}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

	gotoXY(deathLocation); 
	colour(0x7C); 
	std::cout << "BOOM"; 
	deathLocation = nullLocation; 
	
	//player render
    renderPlayer();

	//enemy render
	if (currentWave % 5 != 0)
	{
		for ( int i = 0; i != currentWave; i++)
		{
			if ( spawnenemy[i] == 1 ) 
			{ 
			gotoXY(enemyLocation[i]); 
			colour(0x02); 
			std::cout << "Enemy" ; 
			}
		}
	}
	
	else if (currentWave == 5)
	{
		gotoXY(Pink.bossLocation); 
		colour(0x0D); 
		std::cout << "Pink"; 

		for (int i = 0; i < Pink.index + 1; i++)
		{
			gotoXY(Pink.bossProjectile[i]); 
			colour(0x0E); 
			std::cout << "-"; 
		}
	}

	//renders the UI - hearts, wave number, etc.
	renderUI();
}

void missile()
{
	//calls missile creation when space is pressed
	if (keyPressed[K_SPACE])
    {
		if (createMissileR[0] == 0 && createMissileL[1] == 0)
		{
			createMissileR[0] = 1;
		}

		else if (fourMissiles == true && createMissileR[1] == 0  && createMissileL[1] == 0)
		{
			createMissileR[1] = 1;
		}

		else if (createMissileR[0] == 1 && createMissileL[0] == 0 && createMissileL[1] == 0)
		{
			createMissileL[0] = 1;
		}

		else if (fourMissiles == true && createMissileL[1] == 0)
		{	
			createMissileL[1] = 1;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		//if create called
		if (createMissileR[i] == 1)
		{
			missileRLocation[i].X+=8; //shot speed

			if (missileRLocation[i].X >= consoleSize.X - 5) //if over the screen
			{
				createMissileR[i] = 0;
				missileRLocation[i].X = charLocation.X + 8;
				missileRLocation[i].Y = charLocation.Y + 1; //ready for fire again
			}
		}

		//if create called
		if (createMissileL[i] == 1)
		{
			missileLLocation[i].X+=8; //shot speed

			if (missileLLocation[i].X >= consoleSize.X - 5) //if over the screen
			{
				createMissileL[i] = 0;
				missileLLocation[i].X = charLocation.X + 8;
				missileLLocation[i].Y = charLocation.Y + 1; //ready for fire again
			}
		}

	}
		
	if (createMissileL[0] == 0)
	{
		missileLLocation[0].X = charLocation.X + 2;
		missileLLocation[0].Y = charLocation.Y + 1; //follow the player
	}
	
	if (createMissileR[0] == 0)
	{
		missileRLocation[0].X = charLocation.X + 8;
		missileRLocation[0].Y = charLocation.Y + 1; //follow the player
	}

	if (fourMissiles == true)
	{
		if (createMissileL[1] == 0)
		{
			missileLLocation[1].X = charLocation.X + 2;
			missileLLocation[1].Y = charLocation.Y + 1; //follow the player
		}
	
		if (createMissileR[1] == 0)
		{
			missileRLocation[1].X = charLocation.X + 8;
			missileRLocation[1].Y = charLocation.Y + 1; //follow the player
		}
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

void renderUI()
{
	gotoXY(0, 0);
    colour(0x0F);
    std::cout << "Time: " << elapsedTime << std::endl;

	gotoXY(15,0);
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
	colour(0x01);
	for (int i = 0; i < 5 - (ultiBar/10); i++)
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
		std::cout << "Wave 5 Complete! ";
	}
	if (currentWave == 11)
	{
		std::cout << "Wave 10 Complete! ";
	}

	gotoXY(50,0); 
	colour(0x0F);
	std::cout << "Score: " << score;

	gotoXY(70, 0);
    colour(0x0F);
    std::cout << 1.0 / deltaTime << "fps";

	gotoXY(0, 23);
	colour(0x04);
	for (int i = 0; i < Pink.health*2; i++)
	{
		std::cout << "|";
	}
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

	gotoXY(missileRLocation[1]);
	colour(0x0E);  
	std::cout << "--===>"; 

	gotoXY(missileLLocation[1]);
	colour(0x0E);
	std::cout << "--===>";

	gotoXY(missileRLocation[0]);
	colour(0x0C);  
	std::cout << "--===>"; 

	gotoXY(missileLLocation[0]);
	colour(0x0C);
	std::cout << "--===>";

}

void updateScore()
{
	int scores[5];
	int hscore[5];
	int lowest = INT_MAX ; 
	int highest = -1;
	int a; 
	int index = 0; 

	ifstream Read;
	ofstream Writein; 
	string words ; 

	Read.open ("highscores.txt" ) ;  

	if (Read.is_open()) 
	{ 
		for ( int z = 0 ; z < 5 ; z++ ) 
		{
			getline(Read,words);
			stringstream convert(words) ;
			convert >> a ;  
			scores[z] = a ; 
		} 

		for ( int k = 0 ; k < 5 ; k++ ) 
		{ 
			if ( scores[k] < lowest ) 
			{ 
				lowest = scores[k] ;
				index = k ;
			} 
		}

		if ( score > lowest ) 
		{ 
			scores[index] = score ; 
		} 

		for (int j = 0; j < 5; j++)
		{
			for ( int i = 0; i < 5; i++)
			{
				if (scores[i] > highest)
				{
					highest = scores[i];
				}
			}

			for ( int i = 0; i < 5; i++)
			{
				if (scores[i] == highest)
				{
					hscore[j] = scores[i];
					scores[i] = 0;
					highest = 0;
					break;
				}
			}
		}

		Writein.open ("highscores.txt" ); 

		for (int i = 0; i < 5; i++)
		{
			Writein << hscore[i] << endl; 
		}

		Writein.close();
		Read.close();

	} 
}