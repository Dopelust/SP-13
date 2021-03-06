#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

extern bool keyPressed[K_COUNT];
extern COORD ConsoleSize;
string save[5];
bool shift = 0;
string input;

void renderMenu()
{
	COORD c;
	
	c.X = 0;
	c.Y = 0;

	writeToBuffer ( c, "       _   _   _             _                    ____                       ", 0x0A); c.Y++;
	writeToBuffer ( c, "      / \\ | |_| |_ __ _  ___| | __   ___  _ __   / ___| _ __   __ _  ___ ___ ", 0x0A); c.Y++;
	writeToBuffer ( c, "     / _ \\| __| __/ _` |/ __| |/ /  / _ \\| '_ \\  \\___ \\| '_ \\ / _` |/ __/ _ \\", 0x0A); c.Y++;
	writeToBuffer ( c, "    / ___ \\ |_| || (_| | (__|   <  | (_) | | | |  ___) | |_) | (_| | (_|  __/", 0x0A); c.Y++;
	writeToBuffer ( c, "   /_/   \\_\\__|\\__\\__,_|\\\___|_|\\_\\  \\___/|_| |_| |____/| .__/ \\__,_|\\___\\___|", 0x0A); c.Y++;
	writeToBuffer ( c, "                                                       | |                 ", 0x0A); c.Y++;
	writeToBuffer ( c, "================================================================================", 0x0A); c.Y+=4;

	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Play", 0x0A); c.Y+=2;
	}
	else
	{
		writeToBuffer ( c, "       Play", 0x02); c.Y+=2;
	}
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Profile", 0x0A); c.Y+=2;
	}
	else
	{
		writeToBuffer ( c, "       Profile", 0x02); c.Y+=2;
	}
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Leaderboard", 0x0A); c.Y+=2;
	}
	else
	{
		writeToBuffer ( c, "       Leaderboard", 0x02); c.Y+=2;
	}
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Credits", 0x0A); c.Y+=2;
	}
	else
	{
		writeToBuffer ( c, "       Credits", 0x02); c.Y+=2;
	}
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Exit", 0x0A); c.Y+=4;
	}
	else
	{
		writeToBuffer ( c, "       Exit", 0x02); c.Y+=4;
	}
	writeToBuffer ( c, "================================================================================", 0x0A); c.Y++;
	writeToBuffer ( c, "Press Enter or Spacebar to select ! " , 0x0A) ; 
	writeToBuffer ( pointerLocation , ">", 0x0A);
}

void renderInstruction()
{
	//declarations
	string inst;
	ifstream Reinst;
	//open txt file
	Reinst.open("instructions.txt");

	COORD c;
	c.X = 0;
	c.Y = 0;
	writeToBuffer ( c, "     ___            __ _ _      ", 0x0A); c.Y++;
	writeToBuffer ( c, "    / _ \\_ __ ___  / _(_) | ___ ", 0x0A); c.Y++;
	writeToBuffer ( c, "   / /_)/ '__/ _ \\| |_| | |/ _ \\ ", 0x0A); c.Y++;
	writeToBuffer ( c, "  / ___/| | | (_) |  _| | |  __/" , 0x0A); c.Y++;
	writeToBuffer ( c, "  \\/    |_|  \\___/|_| |_|_|\\___|", 0x0A); c.Y++;
	writeToBuffer ( c, "                                                         ", 0x0A); c.Y++;
	writeToBuffer ( c, "================================================================================", 0x0A); c.Y+=4;	

	//read from txt file
	while (!Reinst.eof( ))
	{
		if(Reinst.is_open())
		{
			getline(Reinst, inst);
			writeToBuffer ( c, inst, 0x0A); c.Y++;
		}
	}

	c.X = 50;
	c.Y = 14;
	writeToBuffer(c, "      -\\_____________", 0x07 ); c.Y++;
	writeToBuffer(c, "      |____________/_>", 0x07 ); c.Y++;
	writeToBuffer(c, "     __/___--====_/", 0x07 ); c.Y+=2;
	writeToBuffer(c, "Pacifista Model 07 / PX-07", 0x0A ); 

	c.X = 0;
	c.Y=16;
	if (pointerLocation.Y == 16)
	{
		writeToBuffer ( c, "        Report" , 0x0A); c.Y+=2;
	}
	else
	{
		writeToBuffer ( c, "       Report" , 0x02); c.Y+=2;
	}
	if (pointerLocation.Y == 18)
	{
		writeToBuffer ( c, "        Return to Menu" , 0x0A);
	}
	else
	{
		writeToBuffer ( c, "       Return to Menu" , 0x02);
	}
	c.Y=22;
	writeToBuffer ( c, "================================================================================", 0x0A);
	writeToBuffer ( pointerLocation , ">", 0x0A);
	
}

void renderInfo()
{
	string eInfo;
	ifstream Info;
	Info.open("Info.txt");
	string saved;
	ifstream savefile;
	savefile.open ("save.txt");

	COORD c;
	c.X = 0;
	c.Y = 0;

	while (!Info.eof())
	{
		getline(Info,eInfo);
		writeToBuffer( c, eInfo,0x0A); c.Y++;
	}

	Info.close();

	while (!savefile.eof())
	{
		for (int i = 0; i < 5; i++)
		{
			getline(savefile, save[i]);

	c.X = 4;
	c.Y = 7;

	writeToBuffer(c, "۱�", 0x09 ); c.X+=9;
	writeToBuffer(c, "Cold Meteor", 0x09 ); 

	c.Y+=6; c.X = 4;

	if (save[2] == "red")
	{
		writeToBuffer(c, "۱�", 0x0C ); c.X+=9;
		writeToBuffer(c, "Meteor", 0x0C ); 
	}
	else
	{
		writeToBuffer(c, "???", 0x0A ); c.X+=9;
		writeToBuffer(c, "???? ?????", 0x0A ); 
	}
	c.Y+=6; c.X = 4;

	if (save[4] == "yellow")
	{
		writeToBuffer(c, "۱�", 0x0E ); c.X+=9;
		writeToBuffer(c, "Unstable Meteor", 0x0E );
	}
	else
	{
		writeToBuffer(c, "???", 0x0A ); c.X+=9;
		writeToBuffer(c, "???? ?????", 0x0A ); 
	}

	c.X = 37; c.Y = 7;
	if (save[1] == "pink")
	{
		writeToBuffer (c , "//--\\\\", 0x0D); c.X-=2; c.Y++;
		writeToBuffer (c , "_-======-_ ", 0x0D); c.X-=2; c.Y++;
		writeToBuffer (c , "(=__\\\\  //__=)", 0x0D); c.X+=5; c.Y++;
		writeToBuffer (c , "----", 0x0D);

		c.X = 54; c.Y = 7;
		writeToBuffer (c , "Agent Pink a.k.a. Anne", 0x0D); c.Y+=2; c.X = 51;
		writeToBuffer (c , "Betrayed the Attack on Space", 0x0D); 
	}

	else
	{
		c.X++; c.Y++;
		writeToBuffer (c , "????", 0x0A); 

		c.X = 62;
		writeToBuffer (c , "????", 0x0A); 
	}

	c.X = 39; c.Y = 14;

	if (save[3] == "white")
	{
		writeToBuffer (c, "\\--=-=��", 0x0F); c.Y++; c.X+=2;
		writeToBuffer (c, "/-�-||", 0x0F); c.Y++; c.X-=7;
		writeToBuffer (c, "/===========<", 0x0F); c.Y++;
		writeToBuffer (c, "|����۱������", 0x0F); c.Y++;
		writeToBuffer (c, "\\===========<", 0x0F); c.Y++; c.X+=7;
		writeToBuffer (c, "\\-�-||", 0x0F); c.Y++; c.X-=2;
		writeToBuffer (c, "/--=-=��", 0x0F); c.Y++;
		c.X = 57; c.Y = 17;
		writeToBuffer (c, "The Mothership", 0x0F); c.Y++; c.X+=2;
	}
	else
	{
		c.X--; c.Y+=3;
		writeToBuffer (c , "????", 0x0A); 

		c.X = 62;
		writeToBuffer (c , "????", 0x0A); 
	}

			}
	}

	savefile.close();
}

void renderHighscore()
{ 
	ifstream Read;
	ifstream Read2;

	string seethis;
	string words;
	string b; 

	COORD c ; 

	c.X = 0;
	c.Y = 0;
	writeToBuffer ( c, "      __                _           _                         _ ", 0x0A); c.Y++;
	writeToBuffer ( c, "     / /  ___  __ _  __| | ___ _ __| |__   ___   __ _ _ __ __| |", 0x0A); c.Y++;
	writeToBuffer ( c, "    / /  / _ \\/ _` |/ _` |/ _ \\ '__| '_ \\ / _ \\ / _` | '__/ _` |", 0x0A); c.Y++;
	writeToBuffer ( c, "   / /__|  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| |" , 0x0A); c.Y++;
	writeToBuffer ( c, "   \\____/\\___|\\__,_|\\__,_|\\___|_|  |_.__/ \\___/ \\__,_|_|  \\__,_|", 0x0A); c.Y++;
	writeToBuffer ( c, "                                                         ", 0x0A); c.Y++;
	writeToBuffer ( c, "================================================================================", 0x0A); c.Y+=4;

	c.X = 8; c.Y = 10;
	writeToBuffer ( c, "#1" , 0x0A);c.Y++;
	writeToBuffer ( c, "#2" , 0x0A);c.Y++;
	writeToBuffer ( c, "#3" , 0x0A);c.Y++;
	writeToBuffer ( c, "#4" , 0x0A);c.Y++;
	writeToBuffer ( c, "#5" , 0x0A);c.Y++;

	Read.open ("highscores.txt" ) ;  
	Read2.open ("highscorename.txt" ) ; 

	if (Read.is_open() && Read2.is_open() )
	{ 
		for ( int z = 0 ; z < 5 ; z++ ) 
		{
			getline(Read2,b);
			c.X = 11;
			c.Y = 10 + z ;
			seethis = b;
			writeToBuffer ( c , seethis , 0x0A ) ;

			getline(Read,words);
			c.X = 19;
			seethis = words  ; 
			writeToBuffer ( c , seethis , 0x0A ) ;
		}
	}

	Read.close();
	Read2.close();

	c.X = 0;
	c.Y = 18;

	writeToBuffer ( c, "        Return to Menu" , 0x0A);c.Y=22;
	writeToBuffer ( c, "================================================================================", 0x0A);
	writeToBuffer ( pointerLocation , ">", 0x0A);
} 

void renderCredit()
{ 
	//declarations
	string credit[17];
	ifstream ReadCre;
	//open txt file
	ReadCre.open("credits.txt");
	COORD c;
	c.X=20;
	c.Y=3;

	//read from txt file
	for (int i = 0; i < 17; i++)
	{
		getline(ReadCre, credit[i]);
		writeToBuffer ( c, credit[i], 0x0A); c.Y++;
	}
} 

void renderUI()
{
	COORD c;
	
	// displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / deltaTime << "fps";
    c.X = ConsoleSize.X-9;
    c.Y = 0;
    writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << elapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    writeToBuffer(c, ss.str());

	char scoreDisplay[10];
	c.X = 13;
    c.Y = 0;
    writeToBuffer(c, "Score:", 0x0F);
	c.X+=6;
	writeToBuffer(c, itoa (score, scoreDisplay, 10), 0x0F);

	c.X = 25;
	c.Y = 0;
	for (int i = 0; i < heart; i++)
	{
		writeToBuffer (c, char(3), 0x0C);
		c.X+=2;
	}

	c.X = 25;
	c.Y = 1;

	for (int i = 0; i < ultiBar/10; i++)
	{
		if ( i < 5)
		{
			writeToBuffer (c, char(4), 0x0B);
			c.X+=2;
		}

		else if (i == 5)
		{
			c.X = 25;
			writeToBuffer (c, char(4), 0x0F);
			c.X+=2;
		}
		
		else if (i > 5)
		{
			writeToBuffer (c, char(4), 0x0F);
			c.X+=2;
		}
	}

	for (int i = 0; i < 5 - ultiBar/10; i++)
	{
		writeToBuffer (c, char(4), 0x03);
		c.X+=2;
	}

	if (state == pause)
	{
		c.X = ConsoleSize.X - 60;
		c.Y = ( ConsoleSize.Y / 2 ) - 6;
		writeToBuffer ( c, "===========================================", 0x0A); c.Y++;
		writeToBuffer ( c, "|               Game Paused               |", 0x0A); c.Y++;
		writeToBuffer ( c, "===========================================", 0x0A); c.Y++;
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		if (pointerLocation.Y == c.Y)
		{
			writeToBuffer ( c, "|                Resume                   |", 0x0A); c.Y++;
		}
		else
		{
			writeToBuffer ( c, "|", 0x0A); c.X++;
			writeToBuffer ( c, "               Resume                    ", 0x02); c.X+=41;
			writeToBuffer ( c, "|", 0x0A); c.X = ConsoleSize.X - 60;  c.Y++; 
		}
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		if (pointerLocation.Y == c.Y)
		{
			writeToBuffer ( c, "|                Main Menu                |", 0x0A); c.Y++;
		}
		else
		{
			writeToBuffer ( c, "|", 0x0A); c.X++;
			writeToBuffer ( c,"               Main Menu                 ", 0x02); c.X+=41;
			writeToBuffer ( c,"|", 0x0A); c.X = ConsoleSize.X - 60;  c.Y++; 
		}
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		if (pointerLocation.Y == c.Y)
		{
			writeToBuffer ( c, "|                Exit                     |", 0x0A); c.Y++;
		}
		else
		{
			writeToBuffer ( c, "|", 0x0A); c.X++;
			writeToBuffer ( c, "               Exit                      ", 0x02); c.X+=41;
			writeToBuffer ( c,"|", 0x0A); c.X = ConsoleSize.X - 60;  c.Y++; 
		}
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		writeToBuffer ( c, "===========================================", 0x0A); c.Y++;

		writeToBuffer ( pointerLocation, ">", 0x0A);
	}

	if (state == Exit)
	{
		c.X = ConsoleSize.X - 60;
		c.Y = ( ConsoleSize.Y / 2 ) - 6;
		writeToBuffer ( c, "===========================================", 0x0A); c.Y++;
		writeToBuffer ( c, "|            Exiting Game                 |", 0x0A); c.Y++;
		writeToBuffer ( c, "===========================================", 0x0A); c.Y++;
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		writeToBuffer ( c, "|   Are you sure you want to exit game?   |", 0x0A); c.Y++;
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		if (pointerLocation.Y == c.Y)
		{
			writeToBuffer ( c, "|                Yes                      |", 0x0A); c.Y++;
		}
		else
		{
			writeToBuffer ( c, "|", 0x0A); c.X++;
			writeToBuffer ( c,"               Yes                       ", 0x02); c.X+=41;
			writeToBuffer ( c,"|", 0x0A); c.X = ConsoleSize.X - 60;  c.Y++; 
		}
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		if (pointerLocation.Y == c.Y)
		{
			writeToBuffer ( c, "|                No                       |", 0x0A); c.Y++;
		}
		else
		{
			writeToBuffer ( c, "|", 0x0A); c.X++;
			writeToBuffer ( c, "               No                        ", 0x02); c.X+=41;
			writeToBuffer ( c,"|", 0x0A); c.X = ConsoleSize.X - 60;  c.Y++; 
		}
		writeToBuffer ( c, "|                                         |", 0x0A); c.Y++;
		writeToBuffer ( c, "===========================================", 0x0A); c.Y++;

		writeToBuffer ( pointerLocation, ">", 0x0A);
	}

}

void renderPlayer()
{
	COORD c;
	c.X = charLocation.X;
	c.Y = charLocation.Y;
	writeToBuffer(c, " -\\_____________", 0x07 );
	c.Y++;
	writeToBuffer(c, " |____________/_>", 0x07 );
	if (createUlti == true)
	{
		c.X = 17;
		for ( int i = 17; i < ConsoleSize.X; i++)
		{
			if (delay == 1)
			{
				if (i%2 == 0)
				{
					writeToBuffer(c, "-", 0x0F);
				}
				else
				{
					writeToBuffer(c, "=", 0x0B);
				}
			}

			else 
			{
				if (i%2 == 0)
				{
					writeToBuffer(c, "=", 0x0B);
				}
				else
				{
					writeToBuffer(c, "-", 0x0F);
				}
			}

			c.X++;

			if (Pink.shield == true && i == ConsoleSize.X - 18)
			{
				break;
			}

		}
		c.X = charLocation.X;
	}
	else if (laserSight == true)
	{
		for ( int i = 17; i < ConsoleSize.X; i++)
		{
			c.X = i;
			writeToBuffer(c, "-", 0x04 );
		}
		c.X = charLocation.X;
	}
	c.Y++;
	writeToBuffer(c, "__/___--====_/", 0x07 );

	if (fourMissiles == 1)
	{
		writeToBuffer (missileLocation[2], "--===>", 0x0E);
		writeToBuffer (missileLocation[3], "--===>", 0x0E);
	}
	writeToBuffer (missileLocation[0], "--===>", 0x0C);
	writeToBuffer (missileLocation[1], "--===>", 0x0C);
	
}

void renderBack()
{
	COORD c;

	c.X = 0;
	c.Y = 23;

	if (currentWave == 5)
	{
		for (int i = 0; i < Pink.health/5; i++)
		{
			writeToBuffer(c, "|", 0x04);
			c.X++;
		}
	}
	if (waveDelay % 2 == 0)
	{
		renderWaveAlt(); 
	}

	else
	{
		renderWave();
	}		


	//background comets (fast and slow)
	for ( int i = 0; i < 30 ; i++)
	{
		if ( spawnComet[i] == 1 ) 
		{ 
			writeToBuffer (cometLocation[i], "." , 0x0F);
		}
	}
}

void renderPink()
{
	COORD c;

	if ((Pink.createBoss == 1 || deathFrame[0] <= 70) && currentWave == 5)
	{
		if (spawnFrame == 1)
		{
			c.X = Pink.bossLocation.X ; c.Y = Pink.bossLocation.Y + 2;
			writeToBuffer (c , "(", 0x0D);
		}
		if (spawnFrame == 2)
		{
			c.X = Pink.bossLocation.X ; c.Y = Pink.bossLocation.Y + 2;
			writeToBuffer (c , "(=", 0x0D);
		}
		if (spawnFrame == 3)
		{
			c.X = Pink.bossLocation.X + 2; c.Y = Pink.bossLocation.Y + 1;
			writeToBuffer (c , "_", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=_", 0x0D);
		}
		if (spawnFrame == 4)
		{
			c.X = Pink.bossLocation.X + 2; c.Y = Pink.bossLocation.Y + 1;
			writeToBuffer (c , "_-", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__", 0x0D);
		}
		if (spawnFrame == 5)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "/", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-=", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\", 0x0D);
		}
		if (spawnFrame == 6)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-==", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "-", 0x0D);
		}
		if (spawnFrame == 7)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//-", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-===", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\ ", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "--", 0x0D);
		}
		if (spawnFrame == 8)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-====", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  ", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "---", 0x0D);
		}
		if (spawnFrame == 9)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--\\", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-=====", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  /", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "----", 0x0D);
		}
		if (spawnFrame == 10)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--\\\\", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-======", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  //", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "----", 0x0D);
		}
		if (spawnFrame == 11)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--\\\\", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-======-", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  //_", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "----", 0x0D);
		}
		if (spawnFrame == 12)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--\\\\", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-======-_", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  //__", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "----", 0x0D);
		}
		if (spawnFrame == 13)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--\\\\", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-======-_ ", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  //__=", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "----", 0x0D);
		}
		if (spawnFrame >= 14)
		{
			c.X = Pink.bossLocation.X + 4; c.Y = Pink.bossLocation.Y;
			writeToBuffer (c , "//--\\\\", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "_-======-_ ", 0x0D); c.X-=2; c.Y++;
			writeToBuffer (c , "(=__\\\\  //__=)", 0x0D); c.X+=5; c.Y++;
			writeToBuffer (c , "----", 0x0D);
		}

		if (Pink.shield == true)
		{
			c.X = ConsoleSize.X - 18;
			c.Y = Pink.bossLocation.Y - 1;
			writeToBuffer (c , " /", 0x0D); c.Y++;
			writeToBuffer (c , "|", 0x0D); c.Y++;
			writeToBuffer (c , "|", 0x0D); c.Y++;
			writeToBuffer (c , "|", 0x0D); c.Y++;
			writeToBuffer (c , "|", 0x0D); c.Y++;
			writeToBuffer (c , " \\", 0x0D);
		}

		for (int i = 0; i < Pink.index; i++)
		{
			if (Pink.createProj[i] == true)
			{
				writeToBuffer (Pink.bossProjectile[i] , "-", 0x0E);
			}
		}
	}

}

void renderMothership()
{
	COORD c;

	for ( int m = 0; m < 3; m++)
	{
		for (int i = 0; i < 24; i++)
		{
			if (Mothership[m].createProj[i] == true)
			{
				if (currentWave == 10)
				{
					writeToBuffer (Mothership[m].bossProjectile[i] , "۱�", 0x09);
				}

				if (currentWave == 15)
				{
					writeToBuffer (Mothership[m].bossProjectile[i] , "۱�", 0x0C);
				}
			}
		
		}
	}

	for ( int m = 0; m < 3; m++)
	{
		if (Mothership[m].createBoss == false && deathFrame[m] >= 1 && deathFrame[m] < 30)
		{
			c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
			writeToBuffer (c, "\\--=-=��", 0x0C); c.Y++; c.X+=2;
			writeToBuffer (c, "/-�-||", 0x0C); c.Y++; c.X-=7;
			writeToBuffer (c, "/===========<", 0x0C); c.Y++;
			writeToBuffer (c, "|����۱������", 0x0C); c.Y++;
			writeToBuffer (c, "\\===========<", 0x0C); c.Y++; c.X+=7;
			writeToBuffer (c, "\\-�-||", 0x0C); c.Y++; c.X-=2;
			writeToBuffer (c, "/--=-=��", 0x0C); c.Y++;
		}	

		else if (Mothership[m].createBoss == true)
		{
			if (Mothership[m].health > 600)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x05); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x05); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x05); c.Y++;
				writeToBuffer (c, "|����۱������", 0x05); c.Y++;
				writeToBuffer (c, "\\===========<", 0x05); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x05); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x05); c.Y++;
			}

			else if (Mothership[m].health > 500)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x0D); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x0D); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x0D); c.Y++;
				writeToBuffer (c, "|����۱������", 0x0D); c.Y++;
				writeToBuffer (c, "\\===========<", 0x0D); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x0D); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x0D); c.Y++;
			}

			else if (Mothership[m].health > 400)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x0F); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x0F); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x0F); c.Y++;
				writeToBuffer (c, "|����۱������", 0x0F); c.Y++;
				writeToBuffer (c, "\\===========<", 0x0F); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x0F); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x0F); c.Y++;
			}

			else if (Mothership[m].health > 300)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x07); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x07); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x07); c.Y++;
				writeToBuffer (c, "|����۱������", 0x07); c.Y++;
				writeToBuffer (c, "\\===========<", 0x07); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x07); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x07); c.Y++;
			}

			else if (Mothership[m].health > 200)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x08); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x08); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x08); c.Y++;
				writeToBuffer (c, "|����۱������", 0x08); c.Y++;
				writeToBuffer (c, "\\===========<", 0x08); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x08); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x08); c.Y++;
			}

			else if (Mothership[m].health > 100)
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x04); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x04); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x04); c.Y++;
				writeToBuffer (c, "|����۱������", 0x04); c.Y++;
				writeToBuffer (c, "\\===========<", 0x04); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x04); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x04); c.Y++;
			}

			else
			{
				c.X = Mothership[m].bossLocation.X; c.Y = Mothership[m].bossLocation.Y - 2; c.X+=5;
				writeToBuffer (c, "\\--=-=��", 0x0C); c.Y++; c.X+=2;
				writeToBuffer (c, "/-�-||", 0x0C); c.Y++; c.X-=7;
				writeToBuffer (c, "/===========<", 0x0C); c.Y++;
				writeToBuffer (c, "|����۱������", 0x0C); c.Y++;
				writeToBuffer (c, "\\===========<", 0x0C); c.Y++; c.X+=7;
				writeToBuffer (c, "\\-�-||", 0x0C); c.Y++; c.X-=2;
				writeToBuffer (c, "/--=-=��", 0x0C); c.Y++;
			}	
		}
	}

}

void renderWave()
{
	COORD c;

	c.X = 2;
	c.Y = 2;

	if (currentWave != 0 && currentWave %5 == 0)
	{
		writeToBuffer (c , "                                                          " , 0x04); c.Y++;
		writeToBuffer (c , "                             .                 .          " , 0x04); c.Y++;
		writeToBuffer (c , "                           dP                   9b        " , 0x04); c.Y++;
		writeToBuffer (c , "                          dX                     Xb       " , 0x04); c.Y++;
		writeToBuffer (c , "                        __                         __        " , 0x04); c.Y++;
		writeToBuffer (c , "                    ,6dXXXXbo.                 .odXXXXbb, " , 0x04); c.Y++;
		writeToBuffer (c , "                   XXVXXXXXXXXOo.           .oOXXXXXXXXVXX " , 0x04); c.Y++;
		writeToBuffer (c , "                   XXXXXX'~   ~`OOO8b   d8OOO'~   ~`XXXXXX" , 0x04); c.Y++;
		writeToBuffer (c , "                    `9XX'          `98v8P'          `XXP' " , 0x04); c.Y++;
		writeToBuffer (c , "                      9X.          .db|db.          .XP       " , 0x04); c.Y++;
		writeToBuffer (c , "                        )b.  .dbo.dP'`v'`9b.odb.  .dX(" , 0x04); c.Y++;
		writeToBuffer (c , "                      ,dXXXXXXXXXXXb     dXXXXXXXXXXXb." , 0x04); c.Y++;
		writeToBuffer (c , "                     dXXXXXXXXXXXP'   .   `9XXXXXXXXXXXb" , 0x04); c.Y++;
		writeToBuffer (c , "                    dXXXXXXXXXXXXb   d|b   dXXXXXXXXXXXXb" , 0x04); c.Y++;
		writeToBuffer (c , "                    9XXb'   `XXXXXb.dX|Xb.dXXXXX'   `dXXP" , 0x04); c.Y++;
		writeToBuffer (c , "                     `'      9XXXXXX(   )XXXXXXP      `'" , 0x04); c.Y++;
		writeToBuffer (c , "                              XXXX X.`v'.X XXXX" , 0x04); c.Y++;
		writeToBuffer (c , "                              XP^X'`b   d'`X^XX" , 0x04); c.Y++;
		writeToBuffer (c , "                              X. 9  `   '  P )X" , 0x04); c.Y++;
		writeToBuffer (c , "                              `b  `       '  d'" , 0x04); c.Y++;
		writeToBuffer (c , "                               `             '" , 0x04); c.Y++;
	}

	c.X = ConsoleSize.X - 55;
	c.Y = (ConsoleSize.Y / 2) - 2;

	if (currentWave == 1)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / /"  , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/"   , 0x03); c.Y++;
	}
	if (currentWave == 2)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___ " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ |_  |" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  / __/ " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/ /____/ " , 0x03); c.Y++;
	}

	if (currentWave == 3)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ |_  /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  _/_ < " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/ /____/ " , 0x03); c.Y++;
	}

	if (currentWave == 4)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ / / /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  /_  _/" , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/  " , 0x03); c.Y++;
	}
	if (currentWave == 6)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ / __/" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  / _ \\ " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  \\___/ " , 0x03); c.Y++;
	}

	if (currentWave == 7)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ /_  /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / / " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/  " , 0x03); c.Y++;
	}

	if (currentWave == 8)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___ " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ < _ >" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / _ \\" , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   \\___/ " , 0x03); c.Y++;
	}

	if (currentWave == 9)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___ " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ / _ \\" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   \\_, /" , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/    /_/ " , 0x03); c.Y++;
	}

	if (currentWave == 11)
	{
		writeToBuffer (c , "  _      _____ _   ______   ______ " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  <  /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / // /  " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_//_/    " , 0x03); c.Y++;
	}

	if (currentWave == 12)
	{
		writeToBuffer (c , "  _      _____ _   ______   ______  " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  /_  |" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / / __/ " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/____/ " , 0x03); c.Y++;
	}

	if (currentWave == 13)
	{
		writeToBuffer (c , "  _      _____ _   ______   _______" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  /_  /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / //_ < " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/____/ " , 0x03); c.Y++;
	}

	if (currentWave == 14)
	{

		writeToBuffer (c , "  _      _____ _   ______   _______" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  / / /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / /_  _/" , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/ /_/  " , 0x03); c.Y++;
	}
	if (currentWave == 16)
	{

		writeToBuffer (c , "  _      _____ _   ______  _______" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  / __/" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / / _ \\ " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/\\___/ " , 0x03); c.Y++;
	}
	if (currentWave == 17)
	{

		writeToBuffer (c , "  _      _____ _   ______  _______" , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  /_  /" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / / / / " , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/ /_/  " , 0x03); c.Y++;
	}
	if (currentWave == 18)
	{

		writeToBuffer (c , "  _      _____ _   ______  ______ " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  < _ >" , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / / _  |" , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/\\___/ " , 0x03); c.Y++;
	}
	if (currentWave == 19)
	{

		writeToBuffer (c , "  _      _____ _   ______  ______ " , 0x03); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  / _ \\ " , 0x03); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / /\\_, /" , 0x03); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/  /_/  " , 0x03); c.Y++;
	}
}

void renderWaveAlt()
{
	COORD c;

	c.X = 2;
	c.Y = 2;

	if (currentWave != 0 && currentWave %5 == 0)
	{
		writeToBuffer (c , "          .                                                      ." , 0x0C); c.Y++;
		writeToBuffer (c , "        .n                   .                 .                  n." , 0x0C); c.Y++;
		writeToBuffer (c , "  .   .dP                  dP                   9b                 9b.    ." , 0x0C); c.Y++;
		writeToBuffer (c , " 4    qXb         .       dX                     Xb       .        dXp     t" , 0x0c); c.Y++;
		writeToBuffer (c , "dX.    9Xb      .dXb    __                         __    dXb.     dXP     .Xb " , 0x0C); c.Y++;
		writeToBuffer (c , "9XXb._       _.dXXXXb dXXXXbo.                 .odXXXXb dXXXXb._       _.dXXP" , 0x0C); c.Y++;
		writeToBuffer (c , " 9XXXXXXXXXXXXXXXXXXXVXXXXXXXXOo.           .oOXXXXXXXXVXXXXXXXXXXXXXXXXXXXP" , 0x0C); c.Y++;
		writeToBuffer (c , "  `9XXXXXXXXXXXXXXXXXXXXX'~   ~`OOO8b   d8OOO'~   ~`XXXXXXXXXXXXXXXXXXXXXP'" , 0x0C); c.Y++;
		writeToBuffer (c , "    `9XXXXXXXXXXXP' `9XX'          `98v8P'          `XXP' `9XXXXXXXXXXXP'" , 0x0C); c.Y++;
		writeToBuffer (c , "        ~~~~~~~       9X.          .db|db.          .XP       ~~~~~~~" , 0x0C); c.Y++;
		writeToBuffer (c , "                        )b.  .dbo.dP'`v'`9b.odb.  .dX(" , 0x0C); c.Y++;
		writeToBuffer (c , "                      ,dXXXXXXXXXXXb     dXXXXXXXXXXXb." , 0x0C); c.Y++;
		writeToBuffer (c , "                     dXXXXXXXXXXXP'   .   `9XXXXXXXXXXXb" , 0x0C); c.Y++;
		writeToBuffer (c , "                    dXXXXXXXXXXXXb   d|b   dXXXXXXXXXXXXb" , 0x0C); c.Y++;
		writeToBuffer (c , "                    9XXb'   `XXXXXb.dX|Xb.dXXXXX'   `dXXP" , 0x0C); c.Y++;
		writeToBuffer (c , "                     `'      9XXXXXX(   )XXXXXXP      `'" , 0x0C); c.Y++;
		writeToBuffer (c , "                              XXXX X.`v'.X XXXX" , 0x0C); c.Y++;
		writeToBuffer (c , "                              XP^X'`b   d'`X^XX" , 0x0C); c.Y++;
		writeToBuffer (c , "                              X. 9  `   '  P )X" , 0x0C); c.Y++;
		writeToBuffer (c , "                              `b  `       '  d'" , 0x0C); c.Y++;
		writeToBuffer (c , "                               `             '" , 0x0C); c.Y++;
	}

	c.X = ConsoleSize.X - 55;
	c.Y = (ConsoleSize.Y / 2) - 2;

	if (currentWave == 1)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / /"  , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/"   , 0x0C); c.Y++;
	}
	if (currentWave == 2)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___ " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ |_  |" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  / __/ " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/ /____/ " , 0x0C); c.Y++;
	}

	if (currentWave == 3)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ |_  /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  _/_ < " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/ /____/ " , 0x0C); c.Y++;
	}

	if (currentWave == 4)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ / / /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  /_  _/" , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/  " , 0x0C); c.Y++;
	}
	if (currentWave == 6)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ / __/" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/  / _ \\ " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  \\___/ " , 0x0C); c.Y++;
	}

	if (currentWave == 7)
	{
		writeToBuffer (c , "  _      _____ _   ______  ____" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ /_  /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / / " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/  " , 0x0C); c.Y++;
	}

	if (currentWave == 8)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___ " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ < _ >" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / _ \\" , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   \\___/ " , 0x0C); c.Y++;
	}

	if (currentWave == 9)
	{
		writeToBuffer (c , "  _      _____ _   ______  ___ " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ / _ \\" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   \\_, /" , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/    /_/ " , 0x0C); c.Y++;
	}

	if (currentWave == 11)
	{
		writeToBuffer (c , "  _      _____ _   ______   ______ " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  <  /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / // /  " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_//_/    " , 0x0C); c.Y++;
	}

	if (currentWave == 12)
	{
		writeToBuffer (c , "  _      _____ _   ______   ______  " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  /_  |" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / / __/ " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/____/ " , 0x0C); c.Y++;
	}

	if (currentWave == 13)
	{
		writeToBuffer (c , "  _      _____ _   ______   _______" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  /_  /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / //_ < " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/____/ " , 0x0C); c.Y++;
	}

	if (currentWave == 14)
	{

		writeToBuffer (c , "  _      _____ _   ______   _______" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/  <  / / /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/    / /_  _/" , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/   /_/ /_/  " , 0x0C); c.Y++;
	}
	if (currentWave == 16)
	{

		writeToBuffer (c , "  _      _____ _   ______  _______" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  / __/" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / / _ \\ " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/\\___/ " , 0x0C); c.Y++;
	}
	if (currentWave == 17)
	{

		writeToBuffer (c , "  _      _____ _   ______  _______" , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  /_  /" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / / / / " , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/ /_/  " , 0x0C); c.Y++;
	}
	if (currentWave == 18)
	{

		writeToBuffer (c , "  _      _____ _   ______  ______ " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  < _ >" , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / / _  |" , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/\\___/ " , 0x0C); c.Y++;
	}
	if (currentWave == 19)
	{

		writeToBuffer (c , "  _      _____ _   ______  ______ " , 0x0C); c.Y++;
		writeToBuffer (c , " | | /| / / _ | | / / __/ <  / _ \\ " , 0x0C); c.Y++;
		writeToBuffer (c , " | |/ |/ / __ | |/ / _/   / /\\_, /" , 0x0C); c.Y++;
		writeToBuffer (c , " |__/|__/_/ |_|___/___/  /_/  /_/  " , 0x0C); c.Y++;
	}

}

void gameOver()
{
	ifstream Read;
	ifstream Read2;

	string seethis;
	string words;
	string b; 

	ifstream savefile;
	ofstream writesave; 
	savefile.open ("save.txt");

	while (!savefile.eof())
	{
		for (int i = 0; i < 5; i++)
		{
			getline(savefile, save[i]);
		}
	}

	savefile.close();

	writesave.open ("save.txt" ); 

	if (currentWave > 1 || save[0] == "blue")
	{
		writesave << "blue" << endl;
	}
	else
	{
		writesave << "0" << endl;
	}

	if (currentWave > 4 || save[1] == "pink")
	{
		writesave << "pink" << endl;
	}
	else
	{
		writesave << "0" << endl;
	}

	if (currentWave > 5 || save[2] == "red")
	{
		writesave << "red" << endl;
	}
	else
	{
		writesave << "0" << endl;
	}

	if (currentWave > 9 || save[3] == "white")
	{
		writesave << "white" << endl;
	}
	else
	{
		writesave << "0" << endl;
	}

	if (currentWave > 10 || save[4] == "yellow")
	{
		writesave << "yellow" << endl;
	}
	else
	{
		writesave << "0" << endl;
	}

	writesave.close();
	
	string Keyboard[27] = {"[A]", "[B]", "[C]", "[D]", "[E]", "[F]", "[G]", "[H]", "[I]", "[J]", "[K]", "[L]", "[M]", "[N]", "[O]", "[P]", "[Q]", "[R]", "[S]", "[T]", "[U]", "[V]", "[W]", "[X]", "[Y]", "[Z]", "[SHIFT]"};
	char Alpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	string keyboard[27] = {"[a]", "[b]", "[c]", "[d]", "[e]", "[f]", "[g]", "[h]", "[i]", "[j]", "[k]", "[l]", "[m]", "[n]", "[o]", "[p]", "[q]", "[r]", "[s]", "[t]", "[u]", "[v]", "[w]", "[x]", "[y]", "[z]", "[SHIFT]"};
	char alpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	COORD c;
	
	c.X = 27; c.Y = 1;

	writeToBuffer(c,"      - Game Over -", 0x0A);

	c.X = 27; c.Y = 20;
	
	for (int i = 0; i < 27; i++)
	{
		if (i == 7 || i == 14 || i == 21)
		{
			c.X = 27;
			c.Y++;
		}

		if (pointerLocation.X == c.X && pointerLocation.Y == c.Y  )
		{
			if (shift == 1)
			{
				writeToBuffer(c, keyboard[i], 0x0A); c.X+=4;
			}

			else if (shift == 0)
			{
				writeToBuffer(c, Keyboard[i], 0x0A); c.X+=4;
			}

			if ((keyPressed[K_ENTER] || keyPressed[K_SPACE]))
			{
				if (pointerLocation.X == 47 && pointerLocation.Y == 23  )
				{
					Beep (10000,200);

					if (shift == 1)
					{
						shift = 0;
					}

					else
					{
						shift = 1;
					}
				}

				else if (input.length() != 7)
				{
					Beep (10000,200);

					if (shift == 1)
					{
						input += alpha[i];
					}

					else
					{
						input += Alpha[i];
					}
				}
			}
		}

		else 
		{
			if (shift == 1)
			{
				writeToBuffer(c, keyboard[i], 0x02); c.X+=4;
			}

			else if (shift == 0)
			{
				writeToBuffer(c, Keyboard[i], 0x02); c.X+=4;
			}
		}
	}

	c.X = 27; c.Y = 18;
	if (pointerLocation.X == c.X && pointerLocation.Y == c.Y  )
	{
		writeToBuffer(c, "[CLEAR]", 0x0A); c.X+=4;

		if ((keyPressed[K_ENTER] || keyPressed[K_SPACE])&& input.length() > 0)
		{
			Beep (10000,200);
			input.pop_back();
		}
	}
	else
	{
		writeToBuffer(c, "[CLEAR]", 0x02); c.X+=4;
	}

	c.X = 47; c.Y = 18;
	if (pointerLocation.X == c.X && pointerLocation.Y == c.Y  )
	{
		writeToBuffer(c, "[ENTER]", 0x0A); c.X+=4;
		

		if (keyPressed[K_ENTER] || keyPressed[K_SPACE] && input.length() > 0)
		{
			updateScore();
			Beep (26000,200);
			state = leaderboard;
			pointerLocation.X = 6; 
			pointerLocation.Y = 18; 
		}	
	}
	else
	{
		writeToBuffer(c, "[ENTER]", 0x02); c.X+=4;
	}

	c.X = 32; c.Y = 10;
	writeToBuffer ( c, "#1" , 0x0A);c.Y++;
	writeToBuffer ( c, "#2" , 0x0A);c.Y++;
	writeToBuffer ( c, "#3" , 0x0A);c.Y++;
	writeToBuffer ( c, "#4" , 0x0A);c.Y++;
	writeToBuffer ( c, "#5" , 0x0A);c.Y++;

	Read.open ("highscores.txt" ) ;  
	Read2.open ("highscorename.txt" ) ; 

	c.Y = 10;

	if (Read.is_open() && Read2.is_open() )
	{ 
		for ( int z = 0 ; z < 5 ; z++ ) 
		{
			getline(Read2,b);
			c.X = 40;
			seethis = b;
			writeToBuffer ( c , seethis , 0x0A ) ;

			getline(Read,words);
			c.X = 36;
			seethis = words  ; 
			writeToBuffer ( c , seethis , 0x0A ) ; 	c.Y++;
		}
	}

	Read.close();
	Read2.close();
	
	char intscore[10];
	c.Y++;
	c.X=27;
	writeToBuffer(c, "Your Final score is :",0x0A);
	c.X=49;
	writeToBuffer(c, itoa(score, intscore, 10), 0x0A);c.Y+=2;
	c.X=37;
	writeToBuffer(c, "_______",0x0A);
	writeToBuffer(c, input, 0x0A); 		
}