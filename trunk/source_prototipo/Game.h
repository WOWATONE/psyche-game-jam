#ifndef _GAME_H_
#define _GAME_H_

/*Disable function deprecation*/
#define _CRT_SECURE_NO_WARNINGS

/*Constant Definitions*/
#define TILESHEET_T 200
#define LAYER_TOTAL 4
#define TILE_SIZE 24

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Global.h"

/*Structure that defines each element for each layer*/
typedef struct{
	/*Tile type code*/
	int tile;
	/*x and y position*/
	int x;
	int y;
	/*Determines collision*/
	int col;
}Layer;

/*Struct to create the map matrix*/
typedef struct{
	Layer layer;
	Layer layer1;
	Layer layer2;
	Layer layer3;
	Layer layer4;
}Map;

/*Struct to create any object with position(x, y) and size(width, height)*/
typedef struct{
	int w;
	int h;
	int x;
	int y;
	int yvel;
	int xvel;
	int accel;

	Animation anim_rest;
	Animation anim_alert;
	Animation anim_walk;
	Animation anim_stab01;
	Animation anim_swing01;
	Animation anim_swing02;

	SDL_Surface *Srf_character;
	SDL_Surface *Srf_weapon;
	SDL_Surface *Srf_helmet;
	SDL_Surface *Srf_armor;
	SDL_Surface *Srf_gloves;
	SDL_Surface *Srf_boots;
}Character;

/*The states that the game can assume*/
typedef enum {Stop, Pause, Play} GameState;

/*A general move state*/
typedef enum Movement{stood, right, down, left, up} Movement;

/*The stages and levels*/
typedef enum Stage{stage0, stage1a, stage1b, stage1c, stage1d, stage2a, stage2b, stage2c} Stage;
typedef enum Ground{background, foreground} Ground;

/*The frames that divide the screen*/
extern SDL_Rect frameBottom;
extern SDL_Rect frameTop;


/*Game routines*/
/*void GameStart(void);
void GameInput(void);
void GameLogic(void);
void GameRender(void);*/
void PreviewScreen(Stage level);
void PauseScreen(void);
int LoadMap(char *filename);
void DrawMap(Stage level, Ground groundlayer);
void ClipTiles(int tileSize);
bool CheckCollision(SDL_Rect ObjectA, SDL_Rect ObjectB);
void SetCamera(void);
void SetBackground(void);
void DrawCharacter(void);
void CharacterUpdate(void);


/*Some colors*/
extern SDL_Color backgroundColor;
extern SDL_Color white;
extern SDL_Color darkgreen;
extern SDL_Color red;
extern SDL_Color blue;
extern SDL_Color yellow;




#endif
