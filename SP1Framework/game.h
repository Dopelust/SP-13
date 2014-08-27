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
	COORD bossProjectile[12];
	bool createBoss;
	bool createProj[12];
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
void renderMenu();
void gameOver();
void renderWave();
void renderWaveAlt();

void tutorial();
void Pink5();

//Requisite
extern double elapsedTime;
extern double deltaTime;
//Player
extern int heart;
extern int score ;
extern COORD charLocation;
extern COORD missileRLocation[2];
extern bool createMissileR[2];
extern COORD missileLLocation[2];
extern bool createMissileL[2];
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
extern Boss Mothership;
//PowerUps
extern bool laserSight;
extern bool fourMissiles;
//Misc
extern COORD deathLocation;
extern COORD nullLocation;
extern COORD pointerLocation;
extern bool pause;
extern bool menu;
extern int delay;
extern int waveDelay;
extern int frame;
//Background
extern void comet(); 
extern int comets;
extern COORD cometLocation[30]; 
extern bool spawnComet[30];

#endif // _GAME_H