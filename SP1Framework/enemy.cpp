#include "game.h"

extern COORD ConsoleSize;

int enemy = 0 ;
int dummy = 0 ; 
int tutdelay = 0;

void tutorial()
{
	if ( promptCondition[0] == false) 
	{
		prompt[0] = true;
	}

	else if ( promptCondition[1] == false) 
	{
		prompt[0] = false;
		prompt[1] = true;
	} 

	else if ( promptCondition[2] == false) 
	{ 
		prompt[1] = false;
		prompt[2] = true;
		spawndummy = 1;
	} 

	else if ( promptCondition[3] == false) 
	{ 
		prompt[2] = false;
		prompt[3] = true;
		spawndummy = 1;

		if (dummy == 0) //initialize dummy
		{
			dummyLocation.X = ConsoleSize.X - 5;
			dummyLocation.Y = ( ConsoleSize.Y / 2 ) + 3;
			dummy = 1;
		}
	} 

	else if ( promptCondition[4] == false) 
	{ 
		prompt[2] = false;
		prompt[3] = false;
		prompt[4] = true;
		tutdelay++;
	} 

	if (spawndummy == 1 && delay == 1) //move dummy
	{
		dummyLocation.X--;

		if (dummyLocation.X < 1)
		{
			promptCondition[2] = true;
			deathLocation = dummyLocation;
			spawndummy = 0;
			dummy = 0;
		}
	}
	

	if (dummyLocation.X < 18 )
	{
		for ( int j = 0 ; j < 17 ; j++ ) //x dimension of player hitbox
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) //y dimension of player hitbox
			{ 
				if ( dummyLocation.X == charLocation.X + j && dummyLocation.Y == charLocation.Y + k) //if collide
				{ 
					promptCondition[2] = true;
					deathLocation = dummyLocation;
					spawndummy = 0;
					dummy = 0;
				} 
			} 
		} 
	}

	for (int j = 0; j < 2; j++)
	{

		if ( (dummyLocation.X <= missileRLocation[j].X && dummyLocation.Y == missileRLocation[j].Y) ) //if collide
		{ 
			deathLocation = dummyLocation;
			promptCondition[2] = true;
			promptCondition[3] = true;
			spawndummy = 0;

			createMissileR[j] = 0; //reset missile position
			missileRLocation[j].X = charLocation.X + 10 ;
			missileRLocation[j].Y = charLocation.Y + 1 ;
		}

		if (dummyLocation.X <= missileLLocation[j].X && dummyLocation.Y == missileLLocation[j].Y)
		{
			deathLocation = dummyLocation;
			promptCondition[2] = true;
			promptCondition[3] = true;
			spawndummy = 0;

			createMissileL[j] = 0;
			missileLLocation[j].X = charLocation.X;
			missileLLocation[j].Y = charLocation.Y + 1;
		}

	}
	
}

void createEnemy()
{
	if (currentWave == 0)
	{
		tutorial();
	}

	if (tutdelay > 0)
	{
		currentWave = 1;
		tutdelay++;
	}

	if (tutdelay > 15)
	{	
		tutdelay = 0;
		prompt[4] = false;
	}

	//normal waves
	for ( int i = 0; i != currentWave; i++)
	{
		if (currentWave % 5 != 0)
		{
			enemy = rand() % (5*currentWave) + 1;

			if ( enemy == 1 && spawnenemy[i] == 0 ) 
			{ 
				spawnenemy[i] = 1 ; 
				enemyLocation[i].X = ConsoleSize.X - 5; //new spawn location
				enemyLocation[i].Y = rand() % 20 + 3 ;
			} 
		}

		if (i%2 == 0 && currentWave > 5)
		{
			enemyLocation[i].X--;
		}

		else if (spawnenemy[i] == 1 && delay == 1)
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
			deathLocation = enemyLocation[i];
			spawnenemy[i] = 0 ;
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
					deathLocation = enemyLocation[i];
					spawnenemy[i] = 0 ;
					enemyLocation[i].X = ConsoleSize.X - 5; //new spawn location
					enemyLocation[i].Y = rand() % 20 + 3 ;
					heart--; //heart decrease
				} 
			} 
		} 

		}
	}
}

void Pink5()
{
	//Wave 5 - Codename Pink
	if (currentWave == 5 && Pink.createBoss == 0 && frame == 0)
	{
		//initializing Pink
		Pink.bossLocation.X = ConsoleSize.X - 2;
		Pink.bossLocation.Y = ConsoleSize.Y / 2;
		Pink.health = 400;
		Pink.moveDown = false; Pink.moveUp = false;
		Pink.shield = false;
		Pink.createBoss = 1;
	}

	if (frame > 0)
	{
		frame++;
		for ( int k = -1 ; k < 5 ; k++ ) //Pink's Y hitbox
		{
			for ( int j = -1 ; j < 10 ; j++ ) //Pink's X hitbox
			{	
				if ((rand() % 60 + 1) == 5)
				{
					deathLocation.X = Pink.bossLocation.X + j;
					deathLocation.Y = Pink.bossLocation.Y + k;
					break;
				}
			}
		}
		
	}

	if (frame > 80)
	{
		score +=10;
		currentWave++;
		waveDelay = 0;
		frame = 0;
	}

	//Codename Pink's AI
	if (Pink.createBoss == 1 )
	{
		// Death condition
		if (Pink.health <= 0)
		{
			frame++;
			Pink.createBoss = 0;
			fourMissiles = 1;
		}

		if (Pink.bossLocation.X > ConsoleSize.X - 15)//entering the frame
		{
			Pink.bossLocation.X--;

			if (Pink.bossLocation.X <= ConsoleSize.X - 15)
			{
				Pink.moveDown = true;
			}
		}

		//Moves up and down in a loop
		if (Pink.moveDown == true)
		{
			Pink.bossLocation.Y++;

			if (Pink.bossLocation.Y >= ConsoleSize.Y - 3)
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
			if (Pink.index < 8) //index uniquely identifies each projectile, up to a maximum of 8
			{
				//create or spawns in a projectile, frame by frame
				Pink.createProj[Pink.index] = true; 
				Pink.bossProjectile[Pink.index].X = Pink.bossLocation.X + 3;
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

	//Boss #1 (Pink) Collisions
	if (Pink.createBoss == 1)
	{
		for ( int k = 0 ; k < 4 ; k++ ) //Pink's Y hitbox
		{	
			//Ulti Collision
			if (ultiLocation.Y == Pink.bossLocation.Y + k)
			{
				Pink.shield = true;
				break;
			}

			else 
			{
				Pink.shield = false;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for ( int k = 0 ; k < 4 ; k++ ) //Pink's Y hitbox
			{	
				if (Pink.shield == true)
				{
					if (( Pink.bossLocation.X - 8 <= missileRLocation[i].X) && (Pink.bossLocation.Y + k == missileRLocation[i].Y))
					{
						missileRLocation[i].X = charLocation.X + 8;
						missileRLocation[i].Y = charLocation.Y + 1;
						createMissileR[i] = 0;
						break;
					}

					if (( Pink.bossLocation.X - 8 <= missileLLocation[i].X) && (Pink.bossLocation.Y + k == missileLLocation[i].Y))
					{
						missileLLocation[i].X = charLocation.X + 2;
						missileLLocation[i].Y = charLocation.Y + 1;
						createMissileL[i] = 0;
						break;
					}
				}

				if (Pink.shield == false)
				{

				for ( int j = 0 ; j < 9 ; j++ ) //Pink's X hitbox
				{	
					//Missile Collisions
					if (( Pink.bossLocation.X + j <= missileRLocation[i].X) && (Pink.bossLocation.Y + k == missileRLocation[i].Y))
					{
						Pink.health -=6;
						createMissileR[i] = 0;
						break;
					}

					if (( Pink.bossLocation.X + j <= missileLLocation[i].X) && (Pink.bossLocation.Y + k == missileLLocation[i].Y))
					{
						Pink.health -=6;
						createMissileL[i] = 0;
						break;
					}
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