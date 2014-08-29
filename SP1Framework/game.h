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
    K_ESCAPE,
    K_COUNT,
	K_SPACE,
	K_X,
	K_Z
};

enum gameState
{
	menu,
	play,
	rule,
	leaderboard,
	credits,
	pause
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

//update
void missile();
void ulti();
void createEnemy();
void collisions();
void updateScore();

//render
void renderUI();
void renderPlayer();
void renderBack();
void gameOver();
void renderWave();
void renderWaveAlt();
void renderPink();

void renderMenu();
void renderInstruction();
void renderHighscore();
void renderCredit(); 

void menuBgm();
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
extern bool spawnenemy[20]; 
extern COORD enemyLocation[20];
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
extern COORD deathLocation;
extern COORD nullLocation;
extern COORD pointerLocation;
extern bool delay;
extern int waveDelay;
extern int deathFrame[3];
extern int spawnFrame;
//Background
extern void comet(); 
extern int comets;
extern COORD cometLocation[30]; 
extern bool spawnComet[30];
extern int musicFrame;
#endif // _GAME_H