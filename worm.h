//Header file wor worm.c

void InitGame_Worm(void);
void HandleGame_Worm(void);
unsigned char HandleWormKeys(unsigned char);
void DrawSnake(void);
void DrawFrame(void);
void DrawFood(void);
void AddJoint(unsigned char, unsigned char);
void RemoveJoint(void);
unsigned char Randomize(unsigned char);
unsigned char CheckFoodCollision(void);
void StartGameWorm(unsigned char);
void PlayWorm(unsigned char);

extern const rom char SmallBall[];
#define _BTN_UP 		0x0B
#define _BTN_DOWN 		0x0E
#define _BTN_ENTER		0x0A
#define _BTN_ESC		0x05
#define _BTN_LEFT		0x0D
#define _BTN_RIGHT		0x07


//BUFFER CONFIG
#define _JOINTBUFFERSIZE 40

//GAME CONFIGURATIONS
#define _INCREMENT 5
#define _STARTINGLENGTH 20

