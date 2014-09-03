#ifndef _GAME_H
#define _GAME_H

#include <fstream>
#include <sstream>
#include <string> 
#include <algorithm>
#include "Framework\timer.h"

using namespace::std;

extern StopWatch g_timer;
extern bool g_quitGame;

struct Boss
{
	COORD bossLocation;
	COORD bossProjectile[24];
	bool createBoss;
	bool createProj[24];
	int index;
	bool moveUp;
	bool moveDown;
	bool shield;
	int health;
};

enum Keys
{
    K_UP,
    K_DOWN,
	K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,
	K_ENTER,
	K_Z,
	K_COUNT
};

enum gameState
{
	menu,
	play,
	rule,
	info,
	leaderboard,
	credits,
	pause,
	over
};

enum SoundType
{
	S_Intro ,
	S_Moving,
	S_playerCollision,
	S_Collision,
	S_Lazer, 
	S_Bullet,
	S_Pink,
	S_Death 
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

//update
void playerProjectile();
void createEnemy();
void collisions(COORD targetLocation);
void updateScore();

//render
void renderUI();
void renderPlayer();
void renderBack();
void gameOver();
void renderWave();
void renderWaveAlt();
void renderPink();
void renderMothership();

void renderMenu();
void renderInstruction();
void renderInfo();
void renderHighscore();
void renderCredit(); 

void tutorial();
void Pink5();
void Mothership10();

extern gameState state;

//Requisite
extern double elapsedTime;
extern double deltaTime;
//Player
extern int heart;
extern int score ;
extern COORD charLocation;
extern COORD missileLocation[4];
extern bool createMissile[4];
extern COORD ultiLocation;
extern bool createUlti;
extern int ultiBar;
//Enemy
extern int currentWave;
extern bool spawnenemy[16]; 
extern COORD enemyLocation[16];
//Tutorial
extern bool promptCondition[5];
extern bool prompt[6];
extern bool spawndummy;
extern COORD dummyLocation; 
//Boss
extern Boss Pink;
extern Boss Mothership[3];
//PowerUps
extern bool laserSight;
extern bool fourMissiles;
//Misc
extern COORD deathLocation[16];
extern COORD explosionLocation;
extern COORD pointerLocation;
extern COORD nullLocation;
extern bool delay;
extern int waveDelay;
extern int deathFrame[3];
extern int spawnFrame;
void playGameSound(SoundType sound);
//Background
extern void comet(); 
extern int comets;
extern COORD cometLocation[30]; 
extern bool spawnComet[30];
extern bool collide;
extern bool playerCollide;
extern string input;

#endif // _GAME_H