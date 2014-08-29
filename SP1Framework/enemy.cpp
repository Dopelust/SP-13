#include "game.h"

extern COORD ConsoleSize;

int enemy = 0 ;
int dummy = 0 ; 
int tutdelay = 0;

int wait = 0;

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
		for ( int j = 0 ; j < 14 ; j++ ) //x dimension of player hitbox
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) //y dimension of player hitbox
			{ 
				if ( dummyLocation.X >= charLocation.X + j && dummyLocation.Y == charLocation.Y + k) //if collide
				{ 
					promptCondition[2] = true;
					deathLocation = dummyLocation;
					spawndummy = 0;
					dummy = 0;
				} 
			} 
		} 
	}

	for (int j = 0; j < 4; j++)
	{
		if (fourMissiles == false && j == 2)
		{
			break;
		}

		if ( (dummyLocation.X <= missileLocation[j].X && dummyLocation.Y == missileLocation[j].Y) ) //if collide
		{ 
			deathLocation = dummyLocation;
			promptCondition[2] = true;
			promptCondition[3] = true;
			spawndummy = 0;

			createMissile[j] = 0; //reset missile position

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
		for (int j = 0; j < 4; j++)
		{
			if (fourMissiles == false && j == 2)
			{
				break;
			}

		
		if ( (enemyLocation[i].X <= missileLocation[j].X && enemyLocation[i].Y == missileLocation[j].Y) ) //if collide
		{ 
			spawnenemy[i] = 0 ; 
			deathLocation = enemyLocation[i]; //death animation
			score ++; //score increase

			createMissile[j] = 0; //reset missile position

			if (ultiBar < 50)
			{
				ultiBar +=2; //charge up laser
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

		for ( int l = 0 ; l < 14 ; l++ ) //x dimension of player hitbox
		{ 
			for ( int k = 0 ; k < 4 ; k++ ) //y dimension of player hitbox
			{ 
				if ( enemyLocation[i].X >= charLocation.X + l && enemyLocation[i].Y == charLocation.Y + l ) //if collide
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

void Mothership10()
{
	wait ++;

	if (wait > 21)
	{
		wait = 0;
	}

	for (int m = 0; m < 3; m++)
	{

	//Wave 10 - The Mothership
	if (Mothership[m].createBoss == 0 && deathFrame == 0 && Mothership[m].health > 0)
	{
		//initializing Mothership
		if (m == 0)
		{
			Mothership[m].bossLocation.X = ConsoleSize.X - 13;
			Mothership[m].bossLocation.Y = 5;
		}

		if (m == 1)
		{
			Mothership[m].bossLocation.X = ConsoleSize.X - 13;
			Mothership[m].bossLocation.Y = 12;
		}

		if (m == 2)
		{
			Mothership[m].bossLocation.X = ConsoleSize.X - 13;
			Mothership[m].bossLocation.Y = 19;
		}

		Mothership[m].health = 500;
		Mothership[m].shield = false;
		Mothership[m].createBoss = 1;
	}

	if (Mothership[m].createBoss == 0 && deathFrame > 0)
	{
		deathFrame++;	

		for ( int k = -2 ; k < 5 ; k++ ) 
		{
			for ( int j = -1 ; j < 10 ; j++ )
			{	
				if ((rand() % 60 + 1) == 5)
				{
					deathLocation.X = Mothership[Mothership[0].index].bossLocation.X + j;
					deathLocation.Y = Mothership[Mothership[0].index].bossLocation.Y + k;
					break;
				}
			}
		}
	}

	if (deathFrame > 80)
	{
		score +=30;
		deathFrame = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		if (Mothership[m].createProj[i] == true && delay == 1)
		{
			Mothership[m].bossProjectile[i].X--;
		}

		if (Mothership[m].bossProjectile[i].X == 0)
		{
			Mothership[m].createProj[i] = false;
		}

		for ( int k = 0; k < 4; k++)
		{
			if (fourMissiles == false && k == 2)
			{
				break;
			}
			if (Mothership[m].createProj[i] == true && missileLocation[k].X >= Mothership[m].bossProjectile[i].X && missileLocation[k].Y == Mothership[m].bossProjectile[i].Y)
			{
				deathLocation = Mothership[m].bossProjectile[i];
				createMissile[k] = false;
				Mothership[m].createProj[i] = false;
				break;
			}
		}
	}
	//Codename Pink's AI
	if (Mothership[m].createBoss == 1 )
	{
		// Death condition
		if (Mothership[m].health <= 0)
		{
			deathFrame++;
			Mothership[0].index = m;
			Mothership[m].createBoss = 0;
		}

		for (int i = 0; i < 5; i++)
		{				
			if (Mothership[m].createProj[i] == false && wait == 21 && Mothership[m].createProj[4] == false)
			{
				Mothership[m].createProj[i] = true;
				Mothership[m].bossProjectile[i].X = Mothership[m].bossLocation.X;
				Mothership[m].bossProjectile[i].Y = Mothership[m].bossLocation.Y + 1;
				break;
			}

			else if (Mothership[m].createProj[i] == false ) 
			{ 
				Mothership[m].bossProjectile[i].X = 1 ;
				Mothership[m].bossProjectile[i].Y = 1 ;
			} 
		}

		for (int i = 0; i < 4; i++)
		{
			if (fourMissiles == false && i == 2)
			{
				break;
			}

			for ( int k = -2 ; k < 5 ; k++ )
			{	
				if (ultiLocation.Y == Mothership[m].bossLocation.Y + k)
				{
					Mothership[m].health -=5;
				}
			}

			for ( int k = -2 ; k < 5 ; k++ )
			{	
				if (missileLocation[i].X >= Mothership[m].bossLocation.X && missileLocation[i].Y == Mothership[m].bossLocation.Y + k)
				{
					Mothership[m].health -=10;
					createMissile[i] = 0;
					break;
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
}

void Pink5()
{
	//Wave 5 - Codename Pink
	if (Pink.createBoss == 0 && deathFrame == 0)
	{
		//initializing Pink
		Pink.bossLocation.X = ConsoleSize.X ;
		Pink.bossLocation.Y = (ConsoleSize.Y / 2) - 2;
		Pink.health = 400;
		Pink.moveDown = false; Pink.moveUp = false;
		Pink.shield = false;
		Pink.createBoss = 1;
	}

	if (deathFrame > 0)
	{
		deathFrame++;
		for ( int k = -1 ; k < 5 ; k++ ) 
		{
			for ( int j = -1 ; j < 10 ; j++ )
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

	if (deathFrame > 80)
	{
		score +=10;
		currentWave++;
		waveDelay = 0;
		deathFrame = 0;
	}

	//Codename Pink's AI
	if (Pink.createBoss == 1 )
	{
		// Death condition
		if (Pink.health <= 0)
		{
			Pink.createBoss = 0;
			deathFrame++;
			fourMissiles = 1;
		}

		if (Pink.bossLocation.X > ConsoleSize.X - 15)//entering the frame
		{
			spawnFrame++;
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

		for (int i = 0; i < 4; i++)
		{
			if (fourMissiles == false && i == 2)
			{
				break;
			}

			for ( int k = 0 ; k < 4 ; k++ ) //Pink's Y hitbox
			{	
				if (Pink.shield == true)
				{
					if (( Pink.bossLocation.X - 8 <= missileLocation[i].X) && (Pink.bossLocation.Y + k == missileLocation[i].Y))
					{
						createMissile[i] = 0;
						break;
					}
				}

				if (Pink.shield == false)
				{
					//Missile Collisions
					if (( Pink.bossLocation.X  <= missileLocation[i].X) && (Pink.bossLocation.Y + k == missileLocation[i].Y))
					{
						Pink.health -=6;
						createMissile[i] = 0;
						break;
					}
				}
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