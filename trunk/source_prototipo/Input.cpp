#include "Global.h"
#include "Game.h"
#include "Timer.h"


extern SDL_Event event;
extern MainState CurrentState;
extern MainState NextState;

extern Timer fps;

//extern Mix_Chunk *pauseSound;
extern Stage stage;
extern SDL_Surface *Srf_tilesheet;
extern char stageTitle[50];
extern Layer bg1, bg2, bgtotal, oldbg;

extern Layer fg1, fg2, fgtotal, oldfg;

extern SDL_Rect camera;
extern Movement move;
extern Character player;

Uint8 *keyboardHold;




/*Control the input user is sending - mouse or keyboard*/
void GameInput(void)
{
	/*Run the loop if an input is on the poll of events*/
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			CurrentState = Exit;
		}

		if(event.type == SDL_KEYDOWN)
		{
			/*Pause the game or, unpause if it is already paused*/
			if(event.key.keysym.sym == SDLK_p)
			{
				fps = pause(fps);

				/*Play the sound*/
				//Mix_PlayChannel(-1, pauseSound, 0);
			}

			/* Load Map file */
			if(event.key.keysym.sym == SDLK_F3)
			{
				stage = stage1a;
				if(LoadMap("Maps/stage1-1.map") == 0)
				{
					//Success
				}
			}

		}
	}
	keyboardHold = SDL_GetKeyState(NULL);
	if(keyboardHold[SDLK_RIGHT])
	{
		camera.x += 10;
		bgtotal.x += 8;
		bg1.x += 8;
		bg2.x += 8;

		player.x += player.xvel;
	}
	else if(keyboardHold[SDLK_LEFT])
	{
		camera.x -= 10;
		bgtotal.x -= 8;
		bg1.x -= 8;
		bg2.x -= 8;

		player.x -= player.xvel;
	}
	else if(keyboardHold[SDLK_UP])
	{
		camera.y -= 10;

		player.y -= player.yvel;
	}
	else if(keyboardHold[SDLK_DOWN])
	{
		camera.y += 10;

		player.y += player.yvel;
	}
}
