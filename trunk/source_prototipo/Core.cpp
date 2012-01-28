/*
*	Pathfinder is the current name for this game project
*	It features a character that is going to unveil all different kinds of lands and misteries
*	Searching for his idol and artifact
*	This is a 2D sidescroller-game
*	The graphics are still to be done and should contain appearance based on "LEGO:Indiana Jone" and "Boy and his blob"
*
*	Code by Guilherme S. Gibertoni
*	Last modified in July/2010
*/

#include "Global.h"
#include "Core.h"
#include "Timer.h"


/*Surface to render the window and screen*/
SDL_Surface *Srf_Screen = NULL;
/*Capture events*/
SDL_Event event;
/*Window dimensions*/
int Screen_Width = 800;
int Screen_Height = 600;
int Screen_bpp = 32;
/*Frame rate*/
int frame = 0;
Timer fps;
/*Outuput error file*/
FILE *error;
/*Control States*/
MainState CurrentState;
MainState NextState;





/*Initialize the basic variables to run the program*/
void CoreInit(void)
{
	/*Start the timer for fps count*/
	fps = startTimer(fps);
	fps = start(fps);

	/*Start the Program with the Menu state*/
	CurrentState = Menu;
	MenuInit();
}

/*Clear what is needed to keep memory usage efficient*/
void CoreClear(void)
{


}

/*Close SDL*/
void CoreClose(void)
{
	/*Clean the memory from the SDL structures used*/
	SDL_FreeSurface(Srf_Screen);
	/*SDL_FreeSurface(Srf_pause);
	Mix_FreeChunk(pauseSound);
	TTF_CloseFont(pauseFont); */

	/*Quit SDL*/
	//Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

/*The main() function in C - called by the OS*/
int main(int argc, char *argv[])
{
	/*Open file to output any errors the user might have while running the program*/
	error = fopen("error.dat", "w+");

	/*Initialize every standard SDL features*/
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(error, "\nUnable to initialize SDL\n");
		return ERROR_OCCURRED;
	}
	/*Initialize the SDL_ttf font library*/
	if(TTF_Init() < 0)
	{
		fprintf(error, "\nFailed trying to load SDL_ttf library\n");
		return -1;
	}

	/*Create the window with previuosly set sizes // flags: hardware acceleration, double buffering*/
	Srf_Screen = SDL_SetVideoMode(Screen_Width, Screen_Height, Screen_bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);

	/*Check if the window was rendered on the screen surface*/
	if(Srf_Screen == NULL)
	{
		fprintf(error, "\nFailed trying to load window screen on: %d x %d  %d-bit: %s\n", Screen_Width, Screen_Height, Screen_bpp, SDL_GetError());
		return -1;
	}

	/*Set the window Titlebar*/
	SDL_WM_SetCaption("Pathfinder", NULL);

	/*Initialize the basic variables to run the program*/
	CoreInit();

	/*The main program loop*/
	while(CurrentState != Exit)
	{
		switch(CurrentState)
		{
			case Menu:
				MenuInput();
				MenuLogic();
				MenuDraw();
				break;
			case StageSelection:
				CurrentState = Loading;
				NextState = GamePlay;
				GameStart();
				break;
			case GamePlay:
                GameInput();
                GameLogic();
                GameRender();
				break;
			case ScoreScreen:
                NextState = Menu;
				break;
			case Loading:
				LoadingScreen();
				break;
		}
	}

	/*Before terminating the program close SDL*/
	CoreClose();

	return EXIT_SUCCESSFUL;
}
