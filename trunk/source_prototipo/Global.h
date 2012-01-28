#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/*Disable function deprecation*/
#define _CRT_SECURE_NO_WARNINGS

#define ERROR_OCCURRED -1
#define EXIT_SUCCESSFUL 0
#define FRAMES_PER_SECOND 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"


typedef struct{
	int x;
	int y;
	int currentFrame;
	int firstFrame;
	int lastFrame;
	int frameCut;
	int end;

	SDL_Rect *frame;
	SDL_Surface *Srf_image;
}Animation;


/*Graphics*/
SDL_Surface* LoadImage(char *filepath);
void DrawImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
void SetAnimation(Animation *object, int lines, int collumns, int clipWidth, int clipHeight);
void DrawAnimation( int x, int y, Animation *object);


/*States that the program can assume*/
typedef enum {Exit, Menu, Loading, StageSelection, GamePlay, ScoreScreen} MainState;


/*Variables to screen size and resolution*/
extern int Screen_Width;
extern int Screen_Height;
extern int Screen_bpp;
/*File to store any error information the programmer is ready to output*/
extern FILE *error;





#endif
