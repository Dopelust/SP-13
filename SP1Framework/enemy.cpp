#include "game.h"

extern int heart;
extern int score;
extern bool createMissileR[2];
extern bool createMissileL[2];
extern int ultiBar;
extern COORD charLocation;
extern COORD missileRLocation[2];
extern COORD missileLLocation[2];
extern COORD ultiLocation;
extern COORD consoleSize;
//Enemy
extern int currentWave;
extern COORD enemyLocation[20];
extern bool spawnenemy[20] ; 
int enemy = 0 ; 
//Boss
extern Boss Pink;
extern Boss Zebra;
//Misc
extern COORD deathLocation;
extern COORD nullLocation;

void createEnemy()
{
	//normal waves
	if (currentWave % 5 != 0)
	{
		for ( int i = 0; i != currentWave; i++)
		{
			enemy = rand() % 15 + 1 ; 
			if ( enemy == 1 && spawnenemy[i] == 0 ) 
			{ 
				spawnenemy[i] = 1 ; 
				enemyLocation[i].X = consoleSize.X - 5; //new spawn location
				enemyLocation[i].Y = rand() % 20 + 3 ;
			} 
			if ( spawnenemy[i] == 1 ) 
			{ 
			enemyLocation[i].X--;
			} 
			if ( spawnenemy[i] != 1 ) 
			{ 
				enemyLocation[i].X = 1 ;
				enemyLocation[i].Y = 1 ;
			} 
			
		}
	}

	//wave 5 - Codename Pink
	else if (currentWave == 5 && Pink.createBoss == 0)
	{
		Pink.bossLocation.X = consoleSize.X - 2;
		Pink.bossLocation.Y = consoleSize.Y / 2;
		Pink.health = 40;
		Pink.createBoss = 1;
	}

	//Codename Pink's AI
	if (Pink.createBoss == 1 )
	{
		if (Pink.health <= 0)
		{
			score+=18;
			Pink.createBoss = 0;
		}

		if (Pink.bossLocation.X > consoleSize.X - 7)//entering the frame
		{
			Pink.bossLocation.X--;

			if (Pink.bossLocation.X == consoleSize.X - 7)
			{
				Pink.moveDown = true;
			}
		}

		if (Pink.moveDown == true)
		{
			Pink.bossLocation.Y++;

			if (Pink.bossLocation.Y == consoleSize.Y)
			{
				Pink.moveDown = false;
				Pink.moveUp = true;
			}
		}

		if (Pink.moveUp == true)
		{
			Pink.bossLocation.Y--;

			if (Pink.bossLocation.Y == 2)
			{
				Pink.moveUp = false;
				Pink.moveDown = true;
			}
		}

		if (Pink.moveDown == true || Pink.moveUp == true)
		{
			if (Pink.index < 10)
			{
				Pink.createProj[Pink.index] = true;
				Pink.bossProjectile[Pink.index].X = Pink.bossLocation.X - 1;
				Pink.bossProjectile[Pink.index].Y  = Pink.bossLocation.Y;
				Pink.index++;
			}

			for (int i = 0; i <= Pink.index; i++)
			{
				if (Pink.createProj[i] == true)
				{
					Pink.bossProjectile[i].X-=4;
				}
			}

			for (int i = 0; i <= Pink.index; i++)
			{
				if (Pink.bossProjectile[i].X < 0)
				{
					Pink.bossProjectile[i].X = Pink.bossLocation.X - 1;
					Pink.bossProjectile[i].Y  = Pink.bossLocation.Y;
				}
			}
		}
	}
}

void collisions()
{
	//ulti collisions
	if (Pink.bossLocation.Y == ultiLocation.Y)
	{
		Pink.health -=100;
	}

	//missile collisions
	for (int j = 0; j < 3; j++)
	{
		//collision with Codename Pink	
		if (( Pink.bossLocation.X <= missileRLocation[j].X) && (Pink.bossLocation.Y == missileRLocation[j].Y))
		{
			Pink.health -=5;
			break;
		}

		//collision with enemies
		for ( int i = 0; i != currentWave; i++)
		{

		if ( (enemyLocation[i].X <= missileRLocation[j].X && enemyLocation[i].Y == missileRLocation[j].Y) ) //if collide
		{ 
			spawnenemy[i] = 0 ; 
			deathLocation = enemyLocation[i]; //death animation
			score ++; //score increase

			createMissileR[j] = 0; //reset missile position
			missileRLocation[j].X = charLocation.X + 10 ;
			missileRLocation[j].Y = charLocation.Y + 1 ;

			if (ultiBar < 50)
			{
				ultiBar +=2; //charge up laser
			}
		} 

		if (enemyLocation[i].X <= missileLLocation[j].X && enemyLocation[i].Y == missileLLocation[j].Y)
		{
			spawnenemy[i] = 0 ; 
			deathLocation = enemyLocation[i] ; 
			score ++;
 
			createMissileL[j] = 0;
			missileLLocation[j].X = charLocation.X;
			missileLLocation[j].Y = charLocation.Y + 1;

			if (ultiBar < 50)
			{
				ultiBar +=2;
			}
		}

		//ulti collisions
		if (enemyLocation[i].Y == ultiLocation.Y) 
		{ 
			spawnenemy[i] = 0 ;
			score ++; 
		} 

		if (enemyLocation[i].X < 1 )
		{
			spawnenemy[i] = 0 ;
			enemyLocation[i].X = consoleSize.X - 5;
			enemyLocation[i].Y = rand() % 20 + 3;
			heart--; 
		}
		 

		//player collision
		else if (enemyLocation[i].X < 18 )
		{

		for ( int j = 0 ; j < 17 ; j++ ) //x dimension of player hitbox
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) //y dimension of player hitbox
			{ 
				if ( enemyLocation[i].X == charLocation.X + j && enemyLocation[i].Y == charLocation.Y + k) //if collide
				{ 
					spawnenemy[i] = 0 ;
					enemyLocation[i].X = consoleSize.X - 5; //new spawn location
					enemyLocation[i].Y = rand() % 20 + 3 ;
					heart--; //heart decrease
				} 
			} 
		} 

		}
	}

	if (Pink.createBoss == 1)
	{
		
		for ( int j = 0 ; j < 17 ; j++ ) 
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) 
			{ 
				for (int i = 0; i <= Pink.index; i++)
				{
					if (Pink.bossProjectile[i].X == charLocation.X + j && Pink.bossProjectile[i].Y == charLocation.Y + k )
					{	
						Pink.bossProjectile[i] = nullLocation;
						heart--;
					}
				}
			} 
		} 
	}
	}
}