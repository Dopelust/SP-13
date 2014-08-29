#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

extern COORD ConsoleSize;

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
		writeToBuffer ( c, "        Play                                                        ", 0x0A); c.Y++;
	}
	else
	{
		writeToBuffer ( c, "       Play                                                         ", 0x02); c.Y++;
	}
	writeToBuffer ( c, "                                                                              ", 0x0A); c.Y++;
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Instructions                                                ", 0x0A); c.Y++;
	}
	else
	{
		writeToBuffer ( c, "       Instructions                                                 ", 0x02); c.Y++;
	}
		writeToBuffer ( c, "                                                                              ", 0x0A); c.Y++;
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Leaderboard                                                 ", 0x0A); c.Y++;
	}
	else
	{
		writeToBuffer ( c, "       Leaderboard                                                  ", 0x02); c.Y++;
	}
	writeToBuffer ( c, "                                                                              ", 0x0A); c.Y++;
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Credits                                                     ", 0x0A); c.Y++;
	}
	else
	{
		writeToBuffer ( c, "       Credits                                                      ", 0x02); c.Y++;
	}
	writeToBuffer ( c, "                                                                              ", 0x0A); c.Y++;
	if (pointerLocation.Y == c.Y)
	{
		writeToBuffer ( c, "        Exit                                                         ", 0x0A); c.Y++;
	}
	else
	{
		writeToBuffer ( c, "       Exit                                                        ", 0x02); c.Y++;
	}
	writeToBuffer ( c, "                                                                              ", 0x0A); c.Y+=3;
	writeToBuffer ( c, "================================================================================", 0x0A); 
	writeToBuffer ( pointerLocation , ">", 0x0A);
}

void renderInstruction()
{
	COORD c;
	c.X = 0;
	c.Y = 0;
	writeToBuffer ( c, "    _____           _                   _   _             ", 0x0A); c.Y++;
	writeToBuffer ( c, "    \\_   \\_ __  ___| |_ _ __ _   _  ___| |_(_) ___  _ __  ", 0x0A); c.Y++;
	writeToBuffer ( c, "     / /\\/ '_ \\/ __| __| '__| | | |/ __| __| |/ _ \\| '_ \\ ", 0x0A); c.Y++;
	writeToBuffer ( c, "  /\\/ /_ | | | \\__ \\ |_| |  | |_| | (__| |_| | (_) | | | |" , 0x0A); c.Y++;
	writeToBuffer ( c, "  \\____/ |_| |_|___/\\__|_|   \\__,_|\\___|\\__|_|\\___/|_| |_|", 0x0A); c.Y++;
	writeToBuffer ( c, "                                                         ", 0x0A); c.Y++;
	writeToBuffer ( c, "================================================================================", 0x0A); c.Y+=4;
	writeToBuffer ( c, "        1.Defend yourself from the aliens!", 0x0A);c.Y++;
	writeToBuffer ( c, "        2.Press 'spacebar' to fire your missles!", 0x0A);c.Y++;
	writeToBuffer ( c, "        3.Press 'z' to fire your laser!(Has cooldown and does not work on bosses)", 0x0A);c.Y++;
	writeToBuffer ( c, "        4.After wave 4, there will be a boss battle", 0x0A);c.Y++;
	writeToBuffer ( c, "        5.Have fun!!!", 0x0A);c.Y=18;
	writeToBuffer ( c, "        Return to Menu" , 0x0A);c.Y=22;
	writeToBuffer ( c, "================================================================================", 0x0A);
	writeToBuffer ( pointerLocation , ">", 0x0A);
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
			c.X = 18;
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
	COORD c;
	c.X=1;
	c.Y=1;
	writeToBuffer(c," Thank you for playing our game! We Hope you enjoyed it.",0x0A);c.Y+=2;
	writeToBuffer(c," Credits go to : ", 0x0A);c.Y++;
	writeToBuffer(c,"__________.__                                   ", 0x0A);c.Y++;
	writeToBuffer(c,"\\______   \\__| ____   ______ __________   ____  ", 0x0A);c.Y++;
	writeToBuffer(c," |       _/  |/ ___\\ /  ___//  ___/  _ \\ /    \\ ", 0x0A);c.Y++;
	writeToBuffer(c," |    |   \\  \\  \\___ \\___ \\ \\___ (  <_> )   |  \\ ", 0x0A);c.Y++;
	writeToBuffer(c," |____|_  /__|\\___  >____  >____  >____/|___|  /", 0x0A);c.Y++;
	writeToBuffer(c,"   _____              .___      ", 0x0A);c.Y++;
	writeToBuffer(c,"  /  _  \\   ____    __| _/__.__.", 0x0A);c.Y++;
	writeToBuffer(c," /  /_\\  \\ /    \\  / __ <   |  |", 0x0A);c.Y++;
	writeToBuffer(c,"/    |    \\   |  \\/ /_/ |\\___  |", 0x0A);c.Y++;
	writeToBuffer(c,"\\____|__  /___|  /\\____ |/ ____|", 0x0A);c.Y++;
	writeToBuffer(c,"     ____.              _________             ", 0x0A);c.Y++;
	writeToBuffer(c,"    |    |__ __  ____  /   _____/ ____   ____  ", 0x0A);c.Y++;
	writeToBuffer(c,"    |    |  |  \\/    \\ \\_____  \\_/ __ \\ /    \\ ", 0x0A);c.Y++;
	writeToBuffer(c,"/\\__|    |  |  /   |  \\/        \\  ___/|   |  \\", 0x0A);c.Y++;
	writeToBuffer(c,"\\________|____/|___|  /_______  /\\___  >___|  /", 0x0A);c.Y++;
	writeToBuffer(c,".____       _____  __________  _____ __________ ____ ___  _________", 0x0A);c.Y++;
	writeToBuffer(c,"|    |     /  _  \\ \\____    / /  _  \\\\______   \\    |   \\/   _____/", 0x0A);c.Y++;
	writeToBuffer(c,"|    |    /  /_\\  \\  /     / /  /_\\  \\|       _/    |   /\\_____  \\ ", 0x0A);c.Y++;
	writeToBuffer(c,"|    |___/    |    \\/     /_/    |    \\    |   \\    |  / /        \\", 0x0A);c.Y++;
	writeToBuffer(c,"|_______ \\____|__  /_______ \\____|__  /____|_  /______/ /_______  /", 0x0A);c.Y++;
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
		writeToBuffer (c, char(4), 0x0B);
		c.X+=2;
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
			writeToBuffer ( c, "               Resume                   ", 0x02); c.X+=41;
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
}

void renderPlayer()
{
	COORD c;
	c.X = charLocation.X;
	c.Y = charLocation.Y;
	writeToBuffer(c, "  /---\\_________", 0x07 );
	c.Y++;
	writeToBuffer(c, " |____________|_|", 0x07 );
	if (createUlti == true)
	{
		c.X = 17;
		for ( int i = 17; i < ConsoleSize.X; i++)
		{
			writeToBuffer(c, "=", 0x0B);
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
	writeToBuffer(c, "  /===========\\", 0x07 );
	c.Y++;
	writeToBuffer(c, "  \\_@_@_@_@_@_/", 0x07 );

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

	for (int i = 0; i < Pink.health/5; i++)
	{
		writeToBuffer(c, "|", 0x04);
		c.X++;
	}

	if (currentWave == 5 || currentWave == 10 || currentWave == 15 || currentWave == 20)
	{
		if (waveDelay % 2 == 0)
		{
			renderWaveAlt(); 
		}

		else
		{
			renderWave();
		}		

		if (waveDelay <= 12)
		{
			waveDelay++;
		}
	}

	else if (currentWave > 0)
	{
		if (waveDelay % 2 == 0)
		{
			renderWaveAlt(); 
		}

		else
		{
			renderWave();
		}		

		if (waveDelay <= 8)
		{
			waveDelay++;
		}
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