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
extern bool fourMissiles;
extern COORD deathLocation;
extern COORD nullLocation;

void createEnemy()
{
	//normal waves

	for ( int i = 0; i != currentWave; i++)
	{
		if (currentWave % 5 != 0)
		{
			enemy = rand() % (currentWave*currentWave) + 1;

			if ( enemy == 1 && spawnenemy[i] == 0 ) 
			{ 
				spawnenemy[i] = 1 ; 
				enemyLocation[i].X = consoleSize.X - 5; //new spawn location
				enemyLocation[i].Y = rand() % 20 + 3 ;
			} 
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

	//Wave 5 - Codename Pink
	if (currentWave == 5 && Pink.createBoss == 0)
	{
		//initializing Pink
		Pink.bossLocation.X = consoleSize.X - 2;
		Pink.bossLocation.Y = consoleSize.Y / 2;
		Pink.health = 400;
		Pink.moveDown = false; Pink.moveUp = false;
		Pink.createBoss = 1;
	}

	//Codename Pink's AI
	if (Pink.createBoss == 1 )
	{
		// Death condition
		if (Pink.health <= 0)
		{
			score+=18;
			Pink.createBoss = 0;
			fourMissiles = 1;
		}

		if (Pink.bossLocation.X > consoleSize.X - 15)//entering the frame
		{
			Pink.bossLocation.X--;

			if (Pink.bossLocation.X <= consoleSize.X - 15)
			{
				Pink.moveDown = true;
			}
		}

		//Moves up and down in a loop
		if (Pink.moveDown == true)
		{
			Pink.bossLocation.Y++;

			if (Pink.bossLocation.Y >= consoleSize.Y - 4)
			{
				Pink.moveDown = false;
				Pink.moveUp = true;
			}
		}

		if (Pink.moveUp == true)
		{
			Pink.bossLocation.Y--;

			if (Pink.bossLocation.Y <= 2)
			{
				Pink.moveUp = false;
				Pink.moveDown = true;
			}
		}

		//Shoots projectiles when moving up and down
		if (Pink.moveDown == true || Pink.moveUp == true)
		{
			if (Pink.index < 12) //index uniquely identifies each projectile, up to a maximum of 8
			{
				//create or spawns in a projectile, frame by frame
				Pink.createProj[Pink.index] = true; 
				Pink.bossProjectile[Pink.index].X = Pink.bossLocation.X - 1;
				Pink.bossProjectile[Pink.index].Y  = Pink.bossLocation.Y;
				Pink.index++;
			}
		}
	}
		for (int i = 0; i < Pink.index; i++) //moving the projectile
		{
			if (Pink.createProj[i] == true)				
			{
				Pink.bossProjectile[i].X-=3;
			}

		}
			
		for (int i = 0; i < Pink.index; i++) //if out of the screen, despawn
		{
			if (Pink.bossProjectile[i].X < 0)
			{
				Pink.createProj[i] = false;
			}
		}

		for (int i = 0; i < Pink.index; i++) //if there are no more projectiles on the screen, repeat
		{
			if (Pink.createProj[i] == true)
			{
				break;
			}

			if (i == Pink.index-1)
			{
				Pink.index = 0;
			}
		}
}
	


void collisions()
{	
	//Enemy Collisions
	for ( int i = 0; i != currentWave; i++)
	{
		//With Missiles
		for (int j = 0; j < 2; j++)
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

		}

		//With Ulti
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

		//With Player
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

	//Boss #1 (Pink) Collisions
	if (Pink.createBoss == 1)
	{
		//Pink's Hitbox
		for ( int j = 0 ; j < 9 ; j++ ) 
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) 
			{ 
				for (int i = 0; i < 2; i++)
				{
					//Missile Collisions
					if (( Pink.bossLocation.X + j <= missileRLocation[i].X) && (Pink.bossLocation.Y + k == missileRLocation[i].Y))
					{
						Pink.health -=2;
						createMissileR[i] = 0;
					}

					if (( Pink.bossLocation.X + j <= missileLLocation[i].X) && (Pink.bossLocation.Y + k == missileLLocation[i].Y))
					{
						Pink.health -=2;
						createMissileL[i] = 0;
					}

					//Ulti Collision
					if (Pink.bossLocation.Y + k == ultiLocation.Y)
					{
						Pink.health -=1;
					}
				}
			}
		}

		//Player's Hitbox
		for ( int j = 0 ; j < 17 ; j++ ) 
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) 
			{ 
				for (int i = 0; i <= Pink.index; i++)
				{
					if (Pink.bossProjectile[i].X == charLocation.X + j && Pink.bossProjectile[i].Y == charLocation.Y + k )
					{	
						Pink.createProj[i] = false;
						Pink.bossProjectile[i] = nullLocation;
						heart--;
					}
				}
			} 
		} 
	}
}