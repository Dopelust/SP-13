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
	COORD bossProjectile[10];
	bool createBoss;
	bool createProj[10];
	int index;
	bool moveUp;
	bool moveDown;
	int health;
};

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_COUNT,
	K_SPACE,
	K_Z
};

enum Option
{
	blank,
	Start,
	Options,
	Rules,
	HighScore,
	Credits,
	Exit,
};

void menu();
void gameMenu(int x);
void pause();

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

#endif // _GAME_H