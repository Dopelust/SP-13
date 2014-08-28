#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

bool keyPressed[K_COUNT];

//Requisite
COORD ConsoleSize = {80,25};
double elapsedTime;
double deltaTime;
//Boss
Boss Pink;
Boss Mothership[3];
//Player
string names;
int heart = 15;
int score = 0; 
bool createMissile[4];
COORD missileLocation[4];
bool createUlti = 0;
int ultiBar = 50;
COORD charLocation;
COORD ultiLocation;
//Enemy
int currentWave = 10;
bool spawnenemy[20]; 
COORD enemyLocation[20];
//Tutorial
bool prompt[6];
bool promptCondition[5];
bool spawndummy = 0 ;
COORD dummyLocation; 
//PowerUps
bool laserSight = 1;
bool fourMissiles = 1;
//Misc
bool pause = 0;
bool menu = 1;
int comets = 1; 
bool delay = 0; //for blue asteroids and stars
int waveDelay = 0; //blinks the Wave
int deathFrame = 0; //boss death animation
int spawnFrame = 0; //boss spawn animation
COORD deathLocation;
COORD nullLocation;
COORD pointerLocation;
//Background
void comet(); 
COORD cometLocation[30]; 
bool spawnComet[30];

void init()
{
    //time
    elapsedTime = 0.0;

	//console
	initConsole(ConsoleSize, "SP1 Framework");

	//menu pointer
	pointerLocation.X = 6; 
	pointerLocation.Y = 10; 

    //character
    charLocation.X = 0;
    charLocation.Y = (ConsoleSize.Y / 2) - 2;  

	//tutorial dummy
	dummyLocation.X = ConsoleSize.X - 5;
	dummyLocation.Y = ( ConsoleSize.Y / 2 ) + 3;

	//background
	for ( int i = 0 ; i < 30 ; i++ ) 
	{ 
		spawnComet[i] = 1 ; 
		cometLocation[i].X = rand() % 80 + 1; //new spawn location
		cometLocation[i].Y = rand() % 20 + 4 ;
	}
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
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
    keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_X] = isKeyPressed(0x58);
	keyPressed[K_Z] = isKeyPressed(0x5A);
}

void update(double dt)
{
	if (!pause && !menu)
	{
		 // get the delta time
		elapsedTime += dt;
		deltaTime = dt;

		comet();

		if (currentWave != 0)
		{
			if (score >= (3*((currentWave*currentWave) + (3*currentWave))/2) && currentWave < 20)
			{
				if ( heart < 10)
				{
					heart++;
				}	

				currentWave++;
				waveDelay = 0;
			}
		}

		if (keyPressed[K_ESCAPE])
		{
			pause = true;
			pointerLocation.X = ConsoleSize.X - 45; 
			pointerLocation.Y = (ConsoleSize.Y / 2) - 2; 
		}

	    // Updating the location of the character based on the key press
		if (keyPressed[K_UP] && charLocation.Y > 0 && charLocation.Y != 2)
		{
			charLocation.Y--; 
			promptCondition[0] = true;
		}

		if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 1 && charLocation.Y != 21)
		{
			 charLocation.Y++;
			 promptCondition[0] = true;
		}
	
		missile();
		ulti();

		createEnemy();
		collisions();

		if (currentWave == 5)
		{
			Pink5();
		}

		if (currentWave == 10)
		{
			Mothership10();
		}
	}

	else if (menu == true)
	{
		if (keyPressed[K_UP] && pointerLocation.Y != 10)
		{
			pointerLocation.Y-=2; 
			Beep (3000,100);
		}

		if (keyPressed[K_DOWN] && pointerLocation.Y != 18)
		{
			pointerLocation.Y+=2; 
			Beep (3000,100);
		}

		if (keyPressed[K_X])
		{
			if (pointerLocation.Y == 10) //Play
			{
				menu = false;
			}
			else if (pointerLocation.Y == 12) //Instructions
			{
				
			}	
			else if (pointerLocation.Y == 14) //Leaderboard
			{
			
			}
			else if (pointerLocation.Y == 16) //Credits
			{
				
			}
			else if (pointerLocation.Y == 18) //Exit
			{

			}
		}
	}
	
	if (pause == true)
	{
		if (keyPressed[K_UP] && pointerLocation.Y != (ConsoleSize.Y / 2) - 2)
		{
			pointerLocation.Y-=2; 
			Beep (3000,100);
		}

		if (keyPressed[K_DOWN] && pointerLocation.Y != (ConsoleSize.Y / 2) + 2)
		{
			pointerLocation.Y+=2; 
			Beep (3000,100);
		}

		if (keyPressed[K_X])
		{
			if(pointerLocation.Y == (ConsoleSize.Y/2)-2)
			{
				pause = false;
			}
			else if (pointerLocation.Y == (ConsoleSize.Y/2))
			{
				pause = false;
				menu = true;
				pointerLocation.X = 6; 
				pointerLocation.Y = 10; 
			}	
			else if(pointerLocation.Y == (ConsoleSize.Y/2)+2)
			{
				g_quitGame = true;
			}
		}
	}

	

}

void render()
{
    // clear previous screen
    clearBuffer(0x0F);

	COORD c;
	
	if (menu == true)
	{
		renderMenu();
	}

	else
	{

	renderBack();	

	//player render
    renderPlayer();

	if (spawndummy == true)
	{
		writeToBuffer (dummyLocation, "Û±°", 0x09);
	}

	if ( currentWave == 0 ) 
	{ 
		c.X = 3;
		c.Y = ConsoleSize.Y - 3 ;

		if ( prompt[0] == true ) 
		{
			writeToBuffer ( c , "Press UP/DOWN to move" , 0x0A ) ; 
		}

		if ( prompt[1] == true ) 
		{
			writeToBuffer( c, "Good job! Now press SPACE to shoot!" , 0x0A) ; 
		} 

		if ( prompt[2] == true ) 
		{ 
			writeToBuffer( c, "Oh no, an enemy appears! Hurry, shoot it down before it reaches your base!" , 0x0A) ; 
		} 

		if ( prompt[3] == true ) 
		{ 
			writeToBuffer(c, "Oh no! Try again!" , 0x0A) ; 
		} 

	} 

	c.X = 3;
	c.Y = ConsoleSize.Y - 3 ;

	if ( prompt[4] == true ) 
	{ 
		writeToBuffer(c, "Good job! Wave 1 begins!" , 0x0A) ; 
	} 

	//enemy render
	for ( int i = 0; i != currentWave; i++)
	{
		if ( spawnenemy[i] == 1 ) 
		{ 
			if (i%2 == 0 & currentWave > 5)
			{
				writeToBuffer (enemyLocation[i], "Û±°", 0x0C);
			}

			else
			{
				writeToBuffer (enemyLocation[i], "Û±°", 0x09);
			}
		}
	}

	renderPink();

	for ( int m = 0; m < 3; m++)
	{
		if (Mothership[m].createBoss == true)
		{
			if (Mothership[m].health > 400)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=ÛÛ", 0x0F); c.Y++; c.X+=2;
				writeToBuffer (c, "/-°-||", 0x0F); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x0F); c.Y++;
				writeToBuffer (c, "|ÛÛÛÛÛ±±±±°°°", 0x0F); c.Y++;
				writeToBuffer (c, "\\===========<", 0x0F); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-°-||", 0x0F); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=ÛÛ", 0x0F); c.Y++;
			}

			else if (Mothership[m].health > 300)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=ÛÛ", 0x07); c.Y++; c.X+=2;
				writeToBuffer (c, "/-°-||", 0x07); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x07); c.Y++;
				writeToBuffer (c, "|ÛÛÛÛÛ±±±±°°°", 0x07); c.Y++;
				writeToBuffer (c, "\\===========<", 0x07); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-°-||", 0x07); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=ÛÛ", 0x07); c.Y++;
			}

			else if (Mothership[m].health > 200)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=ÛÛ", 0x08); c.Y++; c.X+=2;
				writeToBuffer (c, "/-°-||", 0x08); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x08); c.Y++;
				writeToBuffer (c, "|ÛÛÛÛÛ±±±±°°°", 0x08); c.Y++;
				writeToBuffer (c, "\\===========<", 0x08); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-°-||", 0x08); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=ÛÛ", 0x08); c.Y++;
			}

			else if (Mothership[m].health > 100)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=ÛÛ", 0x04); c.Y++; c.X+=2;
				writeToBuffer (c, "/-°-||", 0x04); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x04); c.Y++;
				writeToBuffer (c, "|ÛÛÛÛÛ±±±±°°°", 0x04); c.Y++;
				writeToBuffer (c, "\\===========<", 0x04); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-°-||", 0x04); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=ÛÛ", 0x04); c.Y++;
			}

			else if (Mothership[m].health > 0)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=ÛÛ", 0x0C); c.Y++; c.X+=2;
				writeToBuffer (c, "/-°-||", 0x0C); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x0C); c.Y++;
				writeToBuffer (c, "|ÛÛÛÛÛ±±±±°°°", 0x0C); c.Y++;
				writeToBuffer (c, "\\===========<", 0x0C); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-°-||", 0x0C); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=ÛÛ", 0x0C); c.Y++;
			}
		}
	}

	writeToBuffer (deathLocation, "BOOM", 0x7C);
	deathLocation = nullLocation;
	
	//renders the UI - hearts, wave number, etc.
	renderUI();

	}

	flushBufferToConsole();
}

void missile()
{
	//calls missile creation when space is pressed
	if (keyPressed[K_SPACE])
    {
		promptCondition[1] = true;

		if (createMissile[0] == 0 && createMissile[3] == 0)
		{
			createMissile[0] = 1;
		}

		else if (fourMissiles == true && createMissile[2] == 0  && createMissile[3] == 0)
		{
			createMissile[2] = 1;
		}

		else if (createMissile[0] == 1 && createMissile[1] == 0 && createMissile[3] == 0)
		{
			createMissile[1] = 1;
		}

		else if (fourMissiles == true && createMissile[3] == 0)
		{	
			createMissile[3] = 1;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (fourMissiles == false && i == 2)
		{
			break;
		}

		if (createMissile[i] == 1)
		{
			missileLocation[i].X+=8; //shot speed

			if (missileLocation[i].X >= ConsoleSize.X - 3) //if over the screen
			{
				createMissile[i] = 0;
			}
		}

		if (i%2 == 0 && createMissile[i] == 0) //Left Missile
		{
			missileLocation[i].X = charLocation.X + 8;
			missileLocation[i].Y = charLocation.Y + 1; //follow the player
		}
	
		else if (createMissile[i] == 0) //Right Missile
		{
			missileLocation[i].X = charLocation.X + 2;
			missileLocation[i].Y = charLocation.Y + 1; //follow the player
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
		ultiLocation.X = ConsoleSize.X;
		ultiLocation.Y = charLocation.Y + 1;
		ultiBar--;

		if (ultiBar == 0)
		{
			createUlti = 0;
		}
	}

	else 
	{
		ultiLocation = nullLocation;
	}
}

//highscore
void updateScore()
{
	int scores[5];
	int hscore[5];
	string hname[5];
	string namae[5];
	int lowest = INT_MAX ; 
	int highest = -1;
	string topnames;
	int a; 
	int index = 0; 

	ifstream Read;
	ifstream Read2;
	ofstream Writein; 
	ofstream Writeinto; 
	string words ;
	string b;
	

	Read.open ("highscores.txt" ) ;  
	Read2.open ("highscorename.txt" ) ;  


	if (Read.is_open() && Read2.is_open() )
	{ 
		for ( int z = 0 ; z < 5 ; z++ ) 
		{
			getline(Read,words);
			stringstream convert(words) ;
			convert >> a ;  
			scores[z] = a ; 

			//names
			getline(Read2,b);
			hname[z] = b;
		} 


		for ( int k = 0 ; k < 5 ; k++ ) 
		{ 
			if ( scores[k] < lowest ) 
			{ 
				lowest = scores[k] ;
				index = k ;
			} 
		}
		//replace
		if ( score > lowest ) 
		{ 
			scores[index] = score ; 
			hname[index] = names;
		} 

		for (int j = 0; j < 5; j++)
		{
			for ( int i = 0; i < 5; i++)
			{
				if (scores[i] > highest)
				{
					highest = scores[i];
					topnames = hname[i];
				}

			}

			for ( int i = 0; i < 5; i++)
			{
				if (scores[i] == highest)
				{
					hscore[j] = scores[i];
					namae[j] = hname[i];
					scores[i] = 0;
					hname[i] = "";
					highest = 0;
					topnames = "";
					break;
				}
			}
		}

		Writein.open ("highscores.txt" ); 
		Writeinto.open ("highscorename.txt" ); 

		for (int i = 0; i < 5; i++)
		{
			Writein << hscore[i] << endl; 
			Writeinto << namae[i] << endl;
		}

		Writein.close();
		Writeinto.close();
		Read.close();
		Read2.close();

	} 
}

void gameOver()
{
	clearBuffer(0x0F);

	COORD c;
	c.X = 0;
	c.Y = 0;
	writeToBuffer(c, "   ______                             ___                        ", 0x0A); c.Y++;
	writeToBuffer(c, " .' ___  |                          .'   `.                      ", 0x0A); c.Y++;
	writeToBuffer(c, "/ .'   \_| ,--.  _ .--..--. .---.  /  .-.  \_   __ .---. _ .--.  ", 0x0A); c.Y++;
	writeToBuffer(c, "| |   ____`'_\ :[ `.-. .-. / /__\\ | |   | [ \ [  / /__\[ `/'`\] ", 0x0A); c.Y++;
	writeToBuffer(c, "\ `.___]  // | |,| | | | | | \__., \  `-'  /\ \/ /| \__.,| |    ", 0x0A); c.Y++;
	writeToBuffer(c,"  `._____.'\'-;__[___||__||__'.__.'  `.___.'  \__/  '.__.[___]  ", 0x0A); c.Y++;
	writeToBuffer(c, " Please enter your name : ", 0x0A); 

	flushBufferToConsole();
			
}

void comet() 
{ 
	if (delay == 1)
	{
		delay = 0;
	}

	else if (delay == 0)
	{
		for ( int i = 0 ; i < 30 ; i++ ) 
		{ 
			comets = rand() % 100 + 1;

			if ( comets == 1 && spawnComet[i] == 0 ) 
			{ 
				spawnComet[i] = 1 ; 
				cometLocation[i].X = ConsoleSize.X - 1; //new spawn location
				cometLocation[i].Y = rand() % 25 ;
			} 

			if ( spawnComet[i] == 1 ) 
			{ 
				cometLocation[i].X--;
			} 

			if ( cometLocation[i].X < 1 ) 
			{ 
				cometLocation[i].X = ConsoleSize.X - 1; //new spawn location
				cometLocation[i].Y = rand() % 25 ;
			}
		}

		delay++;
	}
	
} 