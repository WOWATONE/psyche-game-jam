#include "../header/Global.h"
#include "../header/Loading.h"


extern SDL_Surface *Srf_Screen;
extern MainState CurrentState;
extern MainState NextState;

SDL_Surface *Srf_loadingBackground = NULL;

Animation loadingText;


void LoadingScreen(void)
{
    int i = 0;

    Srf_loadingBackground = LoadImage("Assets/Background/treasure-screen.png");
    
    loadingText.Srf_image = LoadImage("Assets/loading-text.png");
	loadingText.x = 340;
	loadingText.y = 480;
	loadingText.currentFrame = 0;
	loadingText.firstFrame = 0;
	loadingText.lastFrame = 9;
	loadingText.frameCut = 70;
	loadingText.end = -1;
    SetAnimation(&loadingText, 1, 10, 98, 35);

	for(i = 0; i < 6000; i++)
	{
		DrawImage(0, 0, Srf_loadingBackground, Srf_Screen, NULL);
		DrawAnimation(loadingText.x, loadingText.y, &loadingText); /*FrameCut = depends on how many loops it is going to make*/
		SDL_Flip(Srf_Screen);
	}

    /*After animating goes to the next state*/
	CurrentState = NextState;
	free(loadingText.frame);
}
