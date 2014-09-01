//Declarations

bool keyPressed[K_COUNT];

gameState state = menu;

//Requisite
COORD ConsoleSize = {80,25};
double elapsedTime;
double deltaTime;
//Boss
Boss Pink;
Boss Mothership[3];
//Player
string names;
int heart;
int score;
bool createMissile[4];
COORD missileLocation[4];
bool createUlti;
COORD ultiLocation;
int ultiBar;
COORD charLocation;
//Enemy
int currentWave;
bool spawnenemy[20]; 
COORD enemyLocation[20];
//Tutorial
bool prompt[6];
bool promptCondition[5];
bool spawndummy = 0 ;
COORD dummyLocation; 
//PowerUps
bool laserSight = 0;
bool fourMissiles = 0;
//Misc
bool delay = 0; // 0, 1, 0, 1 ... 
int waveDelay = 0; //blinks the Wave
int deathFrame[3]; //boss death animation
int spawnFrame = 0; //boss spawn animation
COORD explosionLocation;
COORD deathLocation;
COORD nullLocation;
COORD pointerLocation;
bool collide = 0;
bool playerCollide = 0;
//Background
int comets = 1; 
void comet(); 
COORD cometLocation[30]; 
bool spawnComet[30];
