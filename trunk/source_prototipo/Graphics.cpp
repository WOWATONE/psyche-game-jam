#include "Global.h"
#include "Game.h"
#include "Timer.h"


extern SDL_Surface *Srf_Screen;
extern int frame;
extern Timer fps;

extern TTF_Font *pauseFont;
extern Stage stage;
extern SDL_Rect playerRect, *tileRect;
extern SDL_Rect camera;
extern SDL_Surface *Srf_square;
extern int k;

SDL_Color backgroundColor = {0, 0, 0};
SDL_Color white = {255, 255, 255};
SDL_Color darkgreen = {2, 87, 50};
SDL_Color red = {255, 0, 0};
SDL_Color blue = {25, 0, 255};
SDL_Color yellow = {245, 255, 0};


/*Manages the graphics that are to be drawn on screen*/
void GameRender(void)
{
	/*Fill the background*/
	SDL_FillRect(Srf_Screen, NULL, SDL_MapRGB(Srf_Screen->format, 0, 0, 0));

	/* Frames */
	SDL_FillRect(Srf_Screen, &frameTop, SDL_MapRGB(Srf_Screen->format, 0, 0, 0));

	/*Draws the current stage background - then character - then foreground*/
	DrawMap(stage, background);
	DrawCharacter();
	DrawMap(stage, foreground);

	/*Draw Red rectangles where it is collideable*/
	DrawImage(playerRect.x, playerRect.y, Srf_square, Srf_Screen, NULL);
	for(int n = 0; n < k; n++)
	{
		DrawImage(tileRect[n].x - camera.x, tileRect[n].y - camera.y, Srf_square, Srf_Screen, NULL);
	}

	SDL_FillRect(Srf_Screen, &frameBottom, SDL_MapRGB(Srf_Screen->format, 7, 54, 31));

	/*Draws the pause screen (if necessary)*/
	if(fps.paused)
		PauseScreen();

	/*Update Screen Surface after it has been changed*/
	SDL_Flip(Srf_Screen);
}


/*Function to optmize loading an image from file*/
SDL_Surface* LoadImage(char *filepath)
{
	SDL_Surface *loaded = NULL;
	SDL_Surface *optmized = NULL;

	loaded = IMG_Load(filepath);

	/*If loading failed*/
	if(loaded == NULL)
	{
		fprintf(error, "\nCouldn't load the image from file '%s' to the surface", filepath);
		return NULL;
	}

	/*Note that the alpha layer is preserved*/
	optmized = SDL_DisplayFormatAlpha(loaded);
	SDL_FreeSurface(loaded);

	return optmized;
}

/*Function used to blit to a surface an object loaded previously on a surface*/
void DrawImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	/*Draw on destination surface on position delimited by 'offset', the source surface clipped by the 'clip rect'*/
	SDL_BlitSurface(source, clip, destination, &offset);
}


void DrawAnimation(int x, int y, Animation *object)
{
	/*Reset animation to start*/
	if(object->currentFrame == 0)
	{
		object->currentFrame = object->firstFrame;
		if(object->end == 1)
			object->end = 0;
	}

	/*If necessary restart the animation - ex.rest pose*/
    if((object->currentFrame >= (object->lastFrame+1)*object->frameCut) && (object->end == -1))
        object->currentFrame = object->firstFrame;
	else if((object->currentFrame >= (object->lastFrame+1)*object->frameCut) && (object->end == 0))
	{
		object->end++;
		return;
	}


    DrawImage(x, y, object->Srf_image, Srf_Screen, &object->frame[object->currentFrame/object->frameCut]);
    object->currentFrame++;

    return;
}
