#include "game.h"

extern COORD ConsoleSize;

int enemy = 0 ;
int dummy = 0 ; 
int tutdelay = 0;

int wait = 0;
int counter = 0;

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

	if (spawndummy == 1 && delay == 0) //move dummy
	{
		dummyLocation.X--;
		collisions(dummyLocation);

	if (collide == true)
	{
		playGameSound(S_Collision); 
		deathLocation[0] = dummyLocation;
		promptCondition[2] = true;
		promptCondition[3] = true;
		spawndummy = 0;
	}

	if (playerCollide == true)
	{
		playGameSound(S_playerCollision); 
		promptCondition[2] = true;
		deathLocation[0] = dummyLocation;
		spawndummy = 0;
		dummy = 0;
	}

	collide = false;
	playerCollide = false;

	}
	
}

void createEnemy()
{
	//Tutorial
	if (currentWave == 0)
	{
		tutorial();
	}

	if (tutdelay > 0)
	{
		currentWave = 1;
		tutdelay++;

		if (tutdelay > 45)
		{	
			tutdelay = 0;
			prompt[4] = false;
		}
	}

	for ( int i = 0; i != currentWave; i++) //Collision - After Movement
	{
		if (spawnenemy[i] == true)
		{
			collisions(enemyLocation[i]);

			if (collide == true || playerCollide == true)
			{
				deathLocation[i] = enemyLocation[i]; //death animation
				spawnenemy[i] = 0 ; 

				if (collide == true)
				{
					playGameSound(S_Collision); 
					score++;
				}

				if (playerCollide == true)
				{
					playGameSound(S_playerCollision); 
					heart--;
				}		

				collide = false;
				playerCollide = false;
			}

		}

	}

	//Waves
	for ( int i = 0; i != currentWave; i++)
	{
		if (currentWave % 5 != 0)
		{
			if (currentWave < 10)
			{
				enemy = rand() % (5*currentWave); //RNG
			}

			else
			{
				enemy = rand() % (10*currentWave); //RNG
			}
			
			if ( enemy == 1 && spawnenemy[i] == 0 ) 
			{ 
				spawnenemy[i] = 1 ; 
				enemyLocation[i].X = ConsoleSize.X - 3; // Spawn Location
				enemyLocation[i].Y = rand() % 20 + 3 ; 
			} 
		}

		if (spawnenemy[i] == 1)
		{
			if (i%2 == 0 && currentWave > 5) //Red Meteor (Appears Wave 5 and above)
			{
				enemyLocation[i].X--;
			}

			else if (currentWave > 10) //Unstable Meteor (Appears Wave 10 and above)
			{
				enemyLocation[i].X--;

				for (int k = 0; k < 4; k++)
				{
					if (delay == 0 && rand() % 30 == 1 && enemyLocation[i].Y < 20 && missileLocation[k].Y != enemyLocation[i].Y + 1 && ultiLocation.Y != enemyLocation[i].Y + 1)
					{
						enemyLocation[i].Y++;
					}

					else if (delay == 1 && rand() % 30 == 1 && enemyLocation[i].Y > 3 && missileLocation[k].Y != enemyLocation[i].Y - 1 && ultiLocation.Y != enemyLocation[i].Y - 1)
					{
						enemyLocation[i].Y--;
					}
				}
			}

			else if (currentWave <= 10 && delay == 0) //Blue Meteor (Appears Waves 1 - 9)
			{
				enemyLocation[i].X--;
			}
		}

		if ( spawnenemy[i] != 1 ) 
		{ 
			enemyLocation[i].X = 1 ;
			enemyLocation[i].Y = 1 ;
		} 
	}

	for ( int i = 0; i != currentWave; i++) //Collision - After Movement
	{
		if (spawnenemy[i] == true)
		{
			collisions(enemyLocation[i]);

			if (collide == true || playerCollide == true)
			{
				deathLocation[i] = enemyLocation[i]; //death animation
				spawnenemy[i] = 0 ; 

				if (collide == true)
				{
					playGameSound(S_Collision); 
					score++;
				}

				if (playerCollide == true)
				{
					playGameSound(S_playerCollision); 
					heart--;
				}		

				collide = false;
				playerCollide = false;
			}

		}

	}
}

void collisions(COORD targetLocation)
{	
	//With Missiles
	for (int j = 0; j < 4; j++)
	{
		if (fourMissiles == false && j == 2)
		{
			break;
		}
		
		if (createMissile[j] == 1)
		{
			if ( (targetLocation.X <= missileLocation[j].X + 10 && targetLocation.Y == missileLocation[j].Y) ) //if collide
			{ 
				collide = true;

				createMissile[j] = 0; //reset missile position

				if (currentWave <= 10 && ultiBar < 50)
				{
					ultiBar +=2; //charge up laser
				}

				else if (currentWave > 10 && ultiBar < 100)
				{
					ultiBar +=4; //charge up laser

					if (ultiBar > 100)
					{
						ultiBar = 100;
					}
				}
			}
		} 
	}

	//With Ulti
	if (targetLocation.Y == ultiLocation.Y) 
	{ 
		collide = true;
	}

	if (targetLocation.X < 1 )
	{
		playerCollide = true;
	}

	//With Player
	else if (targetLocation.X < 16 ) //x dimension of player hitbox
	{
		for ( int k = 0 ; k < 4 ; k++ ) //y dimension of player hitbox
		{ 
			if ( targetLocation.X >= charLocation.X  && targetLocation.Y == charLocation.Y + k ) //if collide
			{ 
				playerCollide = true;
				break;
			} 
		} 
	}

}

void Mothership10()
{
	wait ++; //Spawn projectiles delay

	if (wait > 18)
	{
		wait = 0;
	}

	for (int m = 0; m < 3; m++)
	{

	if (Mothership[m].createBoss == 0 && deathFrame[m] == 0 && Mothership[m].health > 0)
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

		if (currentWave == 10)
		{
			Mothership[m].health = 500;
		}

		else if (currentWave == 15)
		{
			Mothership[m].health = 700;
		}

		Mothership[m].createBoss = 1;
	}

	if (Mothership[m].createBoss == 0 && deathFrame[m] > 0) //Death Animation
	{
		deathFrame[m]++;	

		if (counter == 2 && delay == 1)
		{
			if (rand() % 2 == 1)
			{
				playGameSound(S_Collision);
			}
		}

		for ( int k = -2 ; k < 5 ; k++ ) 
		{
			for ( int j = -1 ; j < 10 ; j++ )
			{	
				if ((rand() % 60 + 1) == 5)
				{
					explosionLocation.X = Mothership[m].bossLocation.X + j;
					explosionLocation.Y = Mothership[m].bossLocation.Y + k;
					break;
				}
			}
		}
	}

	if (deathFrame[m] > 60) //End Death Animation
	{
		score +=11;
		deathFrame[m] = -1;
	}

	if (deathFrame[m] == -1) //Terminate Death Animation
	{
		if (Mothership[m].createProj[0] == false && Mothership[m].createProj[1] == false && Mothership[m].createProj[2] == false && Mothership[m].createProj[3] == false && Mothership[m].createProj[4] == false && Mothership[m].createProj[5] == false)
		{
			counter++;
			deathFrame[m] = 0;
		}

		if (counter == 3)
		{
			Mothership[0].health = 1;
			Mothership[1].health = 1;
			Mothership[2].health = 1;
			counter = 0;
			waveDelay = 0;
			currentWave++;
		}
	}

	if (Mothership[m].createBoss == 1) //If alive
	{
		// Death condition
		if (Mothership[m].health <= 0)
		{	
			deathFrame[m]++;
			Mothership[m].createBoss = 0;
		}

		for (int i = 0; i < 4; i++) //Collision with Mothership
		{
			if (fourMissiles == false && i == 2)
			{
				break;
			}

			for ( int k = -2 ; k < 5 ; k++ )
			{	
				if (ultiLocation.Y == Mothership[m].bossLocation.Y + k) //Ulti Damage
				{
					explosionLocation.X = Mothership[m].bossLocation.X + 1;
					explosionLocation.Y = Mothership[m].bossLocation.Y + k;
					Mothership[m].health --;
				}
			}

			for ( int k = -2 ; k < 5 ; k++ )
			{	
				if (missileLocation[i].X + 6 >= Mothership[m].bossLocation.X && missileLocation[i].Y == Mothership[m].bossLocation.Y + k) //Missile Damage
				{
					playGameSound(S_Collision); 
					explosionLocation.X = Mothership[m].bossLocation.X + 1;
					explosionLocation.Y = Mothership[m].bossLocation.Y + k;
					Mothership[m].health -=5;
					createMissile[i] = 0;
					break;
				}
			}
		}
	}

	//Projectiles
	for (int i = 0; i < 6; i++) //Projectiles - Initialization
	{				
		if (Mothership[m].createBoss == true && Mothership[m].createProj[i] == false && wait == 18 && Mothership[m].createProj[5] == false) //Initializing Projectiles
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

	for (int i = 0; i < 6; i++) //Projectiles - Movement, Collisions
	{
		if (Mothership[m].createProj[i] == true)
		{
			if (currentWave == 10 && delay == 0)
			{
				Mothership[m].bossProjectile[i].X--;
			}

			else if (currentWave == 15)
			{
				Mothership[m].bossProjectile[i].X--;
			}
		}

		collisions (Mothership[m].bossProjectile[i]);

		if (collide == true || playerCollide == true)
		{
			Mothership[m].createProj[i] = false;
			deathLocation[i] = Mothership[m].bossProjectile[i]; //death animation

			if (collide == true)
			{
				playGameSound(S_Collision); 
			}

			if (playerCollide == true)
			{
				playGameSound(S_playerCollision);
				heart--;
			}

			collide = false;
			playerCollide = false;
		}

	}
	}
}

void Pink5()
{
	//Wave 5 - Codename Pink
	if (Pink.createBoss == 0 && deathFrame[0] == 0)
	{
		//initializing Pink
		Pink.bossLocation.X = ConsoleSize.X ;
		Pink.bossLocation.Y = (ConsoleSize.Y / 2) - 2;
		Pink.health = 400;
		Pink.moveDown = false; Pink.moveUp = false;
		Pink.shield = false;
		Pink.createBoss = 1;
	}

	if (deathFrame[0] > 0)
	{
		deathFrame[0]++;
		for ( int k = -1 ; k < 5 ; k++ ) 
		{
			for ( int j = -1 ; j < 10 ; j++ )
			{	
				if ((rand() % 60 + 1) == 5)
				{
					explosionLocation.X = Pink.bossLocation.X + j;
					explosionLocation.Y = Pink.bossLocation.Y + k;
					break;
				}
			}
		}
		if (delay == 1)
		{
			if (rand() % 2 == 1)
			{
				playGameSound(S_Collision);
			}
		}
	}

	if (deathFrame[0] > 80)
	{
		score +=10;
		currentWave++;
		waveDelay = 0;
		deathFrame[0] = 0;
	}

	//Codename Pink's AI
	if (Pink.createBoss == 1 )
	{
		// Death condition
		if (Pink.health <= 0)
		{
			Pink.createBoss = 0;
			deathFrame[0]++;
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
				if (delay == 1)
				{
					playGameSound(S_Pink);
				}
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
					if (( ConsoleSize.X - 23 <= missileLocation[i].X + 8) && (Pink.bossLocation.Y + k == missileLocation[i].Y))
					{
						createMissile[i] = 0;
						break;
					}
				}

				if (Pink.shield == false)
				{
					if (( Pink.bossLocation.X <= missileLocation[i].X + 8) && (Pink.bossLocation.Y + k == missileLocation[i].Y))
					{
						playGameSound(S_Collision); 
						explosionLocation.X = Pink.bossLocation.X;
						explosionLocation.Y = Pink.bossLocation.Y + k;
						Pink.health -=10;
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
			Pink.bossProjectile[i].X-=2;
		}
	} 

	for (int i = 0; i < 9; i++) //moving the projectile
	{

		if (Pink.bossProjectile[i].X < 0)
		{
			Pink.createProj[i] = false;
		}

		else if (Pink.bossProjectile[i].X < 16)
		{
			//Player's Hitbox
			for ( int k = 0 ; k < 4 ; k++ ) 
			{ 
				if (Pink.bossProjectile[i].X >= charLocation.X && Pink.bossProjectile[i].Y == charLocation.Y + k )
				{	
					playGameSound(S_playerCollision); 
					Pink.createProj[i] = false;
					Pink.bossProjectile[i] = nullLocation;
					heart--;
				}
			}
		}
	}
}