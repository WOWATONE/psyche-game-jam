#include "Global.h"
#include "Game.h"
#include "Timer.h"


extern Timer fps;
extern int frame;

extern Layer bg1, bg2, bgtotal, oldbg;
extern Layer fg1, fg2, fgtotal, oldfg;
extern int bgWidth, fgWidth;
extern int bgepoint, fgepoint;

extern SDL_Rect camera;
extern Stage stage;


/*Calculates the results necessary depending on user input*/
void GameLogic(void)
{
	/*If the game is running unpaused -> increment the frame counter*/
	if(!fps.paused)
	{
		/*Reset counter for new cycle*/
		fps = start(fps);
		frame++;
	}

	/*Updates the camera*/
	SetCamera();
	/*Updates the background and foreground*/
	SetBackground();
	/*Updates the player*/
	CharacterUpdate();

    /*If we want to limit the frame rate*/
    if((getTicks(fps) < 1000 / FRAMES_PER_SECOND))
    {
		/*Sleep the remaining frame time*/
		SDL_Delay((1000 / FRAMES_PER_SECOND) - getTicks(fps));
    }
}

/*Updates the background and foreground positions*/
void SetBackground(void)
{
	fg1.x += 16;
	fg2.x += 16;
	fgtotal.x += 16;

	/*Check if the background has been zeroed while the character is still in the middle of the level*/
	if(bg1.x < 0 && bgtotal.x > 0)
		bg1.x = oldbg.x;
	if(bg2.x < 0)
		bg2.x = 0;

	/*Check if it is needed to draw a new background/foreground*/
	if((bgtotal.x - bgepoint) % 2048 == 0)
		bg2.x = 0;
	if(bg2.x % bgWidth == 0 && bg2.x != 0)
	{
		if(bg1.x > oldbg.x)
			oldbg.x = bg1.x;
		bg1.x = 0;
	}
	/****/
	if((fgtotal.x - fgepoint) % 2048 == 0)
		fg2.x = 0;
	if(fg2.x % fgWidth == 0 && fg2.x != 0)
	{
		if(fg1.x > oldfg.x)
			oldfg.x = fg1.x;
		fg1.x = 0;
	}
}

/*Cut the sprite into rectangles and store in teh animation struct*/
void SetAnimation(Animation *object, int lines, int collumns, int clipWidth, int clipHeight)
{
    int nframes = (lines) * (collumns);
    int cut = 0;
    int i, j;

    object->frame = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (nframes+1));

    for(i = 0; i < lines; i++)
    {
        for(j = 0; j < collumns; j++, cut++)
        {
            object->frame[cut].w = clipWidth;
            object->frame[cut].h = clipHeight;
            if(j == 0)
            {
                object->frame[cut].x = 0;
            }
            else
            {
                object->frame[cut].x = object->frame[cut-1].x + object->frame[cut-1].w;
            }
			object->frame[cut].y = i * object->frame[i].h;
        }
    }
}
