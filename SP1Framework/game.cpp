#include "game.h"
#include "declare.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

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
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	keyPressed[K_Z] = isKeyPressed(0x5A);
}

void init()
{
	heart = 5; 
	score = 0; 
	ultiBar = 50; 
	currentWave = 0; 
	enemyLocation[0].X = ConsoleSize.X - 3;
	createMissile[0] = 0 ; 
	createMissile[1] = 0 ;
	laserSight = 0 ; 
	fourMissiles = 0 ; 
	createUlti = 0 ;

	for (int i = 0; i < 6; i++)
	{
		prompt[i] = 0;

		if (i < 5)
		{
			promptCondition[i] = 0;
		}
	}

    //time
    elapsedTime = 0.0;

	//console
	initConsole(ConsoleSize, "Attack On Space");

	//menu pointer
	pointerLocation.X = 6; 
	pointerLocation.Y = 10; 

    //character
    charLocation.X = 0;
    charLocation.Y = (ConsoleSize.Y / 2) - 2;  

	//tutorial dummy
	dummyLocation.X = ConsoleSize.X - 5;
	dummyLocation.Y = ( ConsoleSize.Y / 2 ) + 3;

	Mothership[0].health = 1;
	Mothership[1].health = 1;
	Mothership[2].health = 1;

	//background
	for ( int i = 0 ; i < 30 ; i++ ) 
	{ 
		spawnComet[i] = 1 ; 
		cometLocation[i].X = rand() % 80 + 1; //new spawn location
		cometLocation[i].Y = rand() % 20 + 4 ;
	}

	snd.loadWave("snk", "snk.WAV");
	snd.loadWave("bullet", "bullet.wav"); 
	snd.loadWave("collision", "collision.wav"); 
	snd.loadWave("playerCollision", "playerCollision.wav"); 
	snd.loadWave("laser", "bullet.wav"); 
	snd.loadWave("Pink", "pinkbullet.wav"); 
	snd.loadWave("death","death.wav");

	if (state == menu)
	{
		playGameSound(S_Intro); 
	}
}

void update(double dt)
{
	if (delay == 1)
	{
		delay = 0;
	}

	else if (delay == 0)
	{
		delay = 1;
	}

	if (state == play)
	{
		// get the delta time
		elapsedTime += dt;
		deltaTime = dt;

		comet();

		if (currentWave != 0 && currentWave < 16)
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

		if ((currentWave == 5 || currentWave == 10 || currentWave == 15) && waveDelay <= 16)
		{
			waveDelay++;
		}

		else if (waveDelay <= 12)
		{
			waveDelay++;
		}

		if (laserSight == false && currentWave > 1)
		{
			laserSight = true;
		}

		if (keyPressed[K_ESCAPE])
		{
			state = pause;
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

		playerProjectile();
		createEnemy();

		if (currentWave == 5)
		{
			Pink5();
		}

		if (currentWave == 10)
		{
			Mothership10();
		}

		if (currentWave == 15)
		{
			Mothership10();
		}

		if ( heart <= 0 )
		{
			state = over;
			pointerLocation.X = 27;
			pointerLocation.Y = 20;
		}
	}

	else if (state == over)
	{
		if (keyPressed[K_LEFT])
		{
			Beep (1500,200);

			if (pointerLocation.X == 47 && pointerLocation.Y == 18) //Enter to Clear
			{
				pointerLocation.X = 27;
			}

			else if (pointerLocation.X == 27) //left to right
			{
				pointerLocation.X = 51;
			}

			else
			{
				pointerLocation.X-=4; 
			}	
		}

		if (keyPressed[K_RIGHT])
		{
			Beep (1500,200);

			if (pointerLocation.X == 27 && pointerLocation.Y == 18) //Clear to Enter
			{
				pointerLocation.X = 47;
			}

			else if (pointerLocation.X == 47 && pointerLocation.Y == 18) //Enter to Clear
			{
				pointerLocation.X = 27;
			}

			else if (pointerLocation.X == 51) //Right to Left
			{
				pointerLocation.X = 27;
			}

			else if (pointerLocation.Y == 23 && pointerLocation.X == 47) // Shift to 
			{
				pointerLocation.X = 27;
			}

			else 
			{
				pointerLocation.X+=4;
			}
		}

		if (pointerLocation.X == 51 && pointerLocation.Y == 18) //[ENTER], 47 to 51
		{
			pointerLocation.X = 47; 
			pointerLocation.Y = 18;
		}

		if (pointerLocation.X == 51 && pointerLocation.Y == 23) //[SHIFT], 47 to 51
		{
			pointerLocation.X = 47; 
			pointerLocation.Y = 23;
		}

		if (pointerLocation.Y < 18)
		{
			pointerLocation.Y = 18;
		}

		if (keyPressed[K_UP])
		{
			Beep (1500,200);

			if ((pointerLocation.X == 27 || pointerLocation.X == 31) && pointerLocation.Y == 20) // to CLEAR
			{
				pointerLocation.X = 27;
				pointerLocation.Y-=2;
			}

			else if (pointerLocation.X == 27 && pointerLocation.Y == 18) //CLEAR to V
			{
				pointerLocation.Y = 23;
			}

			else if ((pointerLocation.X == 47 || pointerLocation.X == 51) && pointerLocation.Y == 20) // to ENTER
			{
				pointerLocation.X = 47;
				pointerLocation.Y-=2;
			}

			else if (pointerLocation.X == 47 && pointerLocation.Y == 18) //ENTER to SHIFT
			{
				pointerLocation.Y = 23;
			}

			else if (pointerLocation.X == 47 && pointerLocation.Y == 23) //SHIFT to U
			{
				pointerLocation.X = 51;
				pointerLocation.Y--; 
			}

			else if (pointerLocation.Y == 20) // Up to Down
			{
				pointerLocation.Y = 23;
			}

			else 
			{
				pointerLocation.Y--; 
			}
		}

		if (keyPressed[K_DOWN])
		{
			Beep (1500,200);

			if (pointerLocation.X == 47 && pointerLocation.Y == 23) //SHIFT LOCATION
			{
				pointerLocation.Y = 18;
			}

			else if (pointerLocation.X == 47 && pointerLocation.Y == 18) //ENTER LOCATION
			{
				pointerLocation.Y+=2;
				pointerLocation.X = 51;
			}

			else if ((pointerLocation.X == 27 ||pointerLocation.X == 31)  && pointerLocation.Y == 23) //CLEAR LOCATION
			{
				pointerLocation.X =27 ;
				pointerLocation.Y = 18;
			}

			else if (pointerLocation.X == 27 && pointerLocation.Y == 18) //CLEAR LOCATION
			{
				pointerLocation.Y+=2;
			}

			else if (pointerLocation.Y == 23)
			{
				pointerLocation.Y = 20;
			}

			else 
			{
				pointerLocation.Y++;
			}
		}

		if (pointerLocation.X == 51 && pointerLocation.Y == 18) //[ENTER], 47 to 51
		{
			pointerLocation.X = 47; 
			pointerLocation.Y = 18;
		}

		if (pointerLocation.X == 51 && pointerLocation.Y == 23) //[SHIFT], 47 to 51
		{
			pointerLocation.X = 47; 
			pointerLocation.Y = 23;
		}

		if (pointerLocation.Y < 18)
		{
			pointerLocation.Y = 18;
		}
	}

	else if (state == menu)
	{
		if (keyPressed[K_UP])
		{
			pointerLocation.Y-=2; 
			Beep (1500,200);

			if (pointerLocation.Y == 8)
			{
				pointerLocation.Y = 18;
			}
		}

		if (keyPressed[K_DOWN])
		{
			pointerLocation.Y+=2; 
			Beep (1500,200);

			if (pointerLocation.Y == 20)
			{
				pointerLocation.Y = 10;
			}
		}

		if (keyPressed[K_ESCAPE])
		{
			Sleep(150);
			state = menu;
			pointerLocation.X = 6; 
			pointerLocation.Y = 18; 
		}

		if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
		{
			Beep (10000,200);

			if (pointerLocation.Y == 10) //Play
			{
				init(); 
				state = play;
			}
			else if (pointerLocation.Y == 12) //Instructions
			{
				state = rule;
				pointerLocation.X = 6; 
				pointerLocation.Y = 18; 
			}	
			else if (pointerLocation.Y == 14) //Leaderboard
			{
				state = leaderboard;
				pointerLocation.X = 6; 
				pointerLocation.Y = 18; 
			}
			else if (pointerLocation.Y == 16) //Credits
			{
				state = credits;
			}
			else if (pointerLocation.Y == 18) //Exit
			{
				g_quitGame = true ; 
			}
		}
	}
	
	else if (state == rule)
	{
		if (keyPressed[K_ESCAPE])
		{
			Sleep(150);
			state = menu;
			pointerLocation.X = 6; 
			pointerLocation.Y = 12; 
		}

		if (keyPressed[K_UP])
		{
			pointerLocation.Y-=2; 
			Beep (1500,200);

			if (pointerLocation.Y == 14)
			{
				pointerLocation.Y = 18;
			}
		}

		if (keyPressed[K_DOWN])
		{
			pointerLocation.Y+=2; 
			Beep (1500,200);

			if (pointerLocation.Y == 20)
			{
				pointerLocation.Y = 16;
			}
		}

		if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
		{
			Beep (10000,200);
			
			if (pointerLocation.Y == 18)
			{
				state = menu;
				pointerLocation.X = 6; 
				pointerLocation.Y = 12; 
			}	

			else
			{
				state = info;
			}
		}
	}

	else if (state == info) // for info
	{
		if (keyPressed[K_ESCAPE])
		{
			Sleep(150);
			state = rule;
			pointerLocation.X = 6; 
			pointerLocation.Y = 16; 
		}

	}

	else if (state == leaderboard)
	{
		if (keyPressed[K_ESCAPE])
		{
			Sleep(150);
			state = menu;
			pointerLocation.X = 6; 
			pointerLocation.Y = 14; 
		}

		if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
		{
			Beep (10000,200);
			state = menu;
			pointerLocation.X = 6; 
			pointerLocation.Y = 14; 
		}
	}

	else if (state == credits)
	{
		if (keyPressed[K_ESCAPE])
		{
			Sleep(150);
			state = menu;
			pointerLocation.X = 6; 
			pointerLocation.Y = 16; 
		}
	}

	else if (state == pause)
	{
		if (keyPressed[K_UP] && pointerLocation.Y != (ConsoleSize.Y / 2) - 2)
		{
			pointerLocation.Y-=2; 
			Beep (1500,200);
		}

		if (keyPressed[K_DOWN] && pointerLocation.Y != (ConsoleSize.Y / 2) + 2)
		{
			pointerLocation.Y+=2; 
			Beep (1500,200);
		}

		if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
		{
			Beep (10000,200);

			if(pointerLocation.Y == (ConsoleSize.Y/2)-2)
			{
				state = play;
			}
			else if (pointerLocation.Y == (ConsoleSize.Y/2))
			{
				state = menu;
				pointerLocation.X = 6; 
				pointerLocation.Y = 10; 
			}	
			else if(pointerLocation.Y == (ConsoleSize.Y/2)+2)
			{
				pointerLocation.X = 30;
				pointerLocation.Y = ConsoleSize.Y / 2 ;
				state = Exit;
			}
		}
	}
	 
	else if (state == Exit )
	{
		if (keyPressed[K_UP] && pointerLocation.Y != (ConsoleSize.Y / 2))
		{
			pointerLocation.Y-=2; 
			Beep (1500,200);
		}

		if (keyPressed[K_DOWN] && pointerLocation.Y == (ConsoleSize.Y / 2) )
		{
			pointerLocation.Y+=2; 
			Beep (1500,200);
		}

		if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
		{
			Beep (10000,200);

			if (pointerLocation.Y == (ConsoleSize.Y/2)) //quit game
			{
				g_quitGame = true ;
			}	
			else if(pointerLocation.Y == (ConsoleSize.Y/2)+2) // resume game , bug if u exit in menu cuz state = play 
			{
				state = play ;
			}
		}
	}
	

}

void render()
{
    // clear previous screen
    clearBuffer(0x0F);

	COORD c;
	
	if (state == menu)
	{
		renderMenu();
	}

	else if (state == rule)
	{
		renderInstruction();
	}

	else if (state == info)
	{
		renderInfo();
	}

	else if (state == leaderboard)
	{
		renderHighscore();
	}

	else if (state == credits)
	{
		renderCredit();
	}

	else if (state == over)
	{
		gameOver();
	}

	else
	{
	//Background
	renderBack();	

	//Player
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

		c.Y = ConsoleSize.Y - 4 ;

		if ( prompt[2] == true ) 
		{ 
			writeToBuffer( c, "Oh no, a meteor appears! Shoot it down before it goes past/hits your ship!" , 0x0A) ; c.Y++;
			writeToBuffer( c, "This will cause you to lose a heart." , 0x0A) ; c.Y++;
			writeToBuffer( c, "If it goes past your ship it will land on Earth!" , 0x0A) ;
		} 

		c.Y = ConsoleSize.Y - 3 ;

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
		c.X = 25;
		c.Y = 2;
		writeToBuffer(c, "Your laser is now fully charged! 'Z' to use." , 0x0A) ; 
	} 

	//Meteors
	for ( int i = 0; i != currentWave; i++)
	{
		if ( spawnenemy[i] == 1 ) 
		{ 
			if (i%2 == 0 & currentWave > 5)
			{
				writeToBuffer (enemyLocation[i], "Û±°", 0x0C);
			}

			else if (currentWave > 10)
			{
				writeToBuffer (enemyLocation[i], "Û±°", 0x0E);
			}

			else
			{
				writeToBuffer (enemyLocation[i], "Û±°", 0x09);
			}
		}
	}

	if (currentWave == 5)
	{
		renderPink();
	}

	if (currentWave == 10 || currentWave == 15)
	{
		renderMothership();
	}

	for (int i = 0; i != currentWave; i++)
	{
		if (rand() % 2 == 0 )
		{
			writeToBuffer (explosionLocation, "BOOM", 0x47);
			writeToBuffer (deathLocation[i], "BOOM", 0x47);
		}
	
		else
		{
			writeToBuffer (explosionLocation, "BOOM", 0x7C);
			writeToBuffer (deathLocation[i], "BOOM", 0x7C);
		}
	}

	for (int i = 0; i != currentWave; i++)
	{
		deathLocation[i].X = 0;
		deathLocation[i].Y = 0;
	}
	explosionLocation.X = 0;
	explosionLocation.Y = 0;
	

	//User Interface
	renderUI();

	}

	flushBufferToConsole();
}

void playerProjectile()
{
	//calls missile creation when space is pressed

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

	if (keyPressed[K_SPACE])
    {
		promptCondition[1] = true;

		if (createMissile[0] == 0 && createMissile[3] == 0)
		{
			playGameSound(S_Bullet);
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

	if (keyPressed[K_Z] && ultiBar >= 50)
    {
		playGameSound(S_Lazer);
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
			hname[index] = input;
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

void comet() 
{ 
	if (delay == 0)
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

	}
	
} 

void playGameSound(SoundType sound)
{
	switch (sound)
	{
	case S_Intro : snd.playSound("snk") ; 
		break; 
	case S_Bullet : snd.playSound("bullet"); 
		break; 
	case S_Collision : snd.playSound("collision");
		break;
	case S_playerCollision : snd.playSound("playerCollision");
		break;
	case S_Pink : snd.playSound("Pink");
		break;
	case S_Death : snd.playSound("death"); 
		break;
	case S_Lazer : snd.playSound("laser"); 
		break;
	}
}