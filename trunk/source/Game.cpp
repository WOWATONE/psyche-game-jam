#include "Global.h"
#include "Game.h"


extern SDL_Surface *Srf_Screen;


/*Font of type ttf*/
TTF_Font *pauseFont = NULL;
TTF_Font *stdfont = NULL;
TTF_Font *stdfont_italic = NULL;

/*Surfaces to draw on*/
SDL_Surface *Srf_pause = NULL;
SDL_Surface *Srf_load = NULL;
SDL_Surface *Srf_preview = NULL;
SDL_Surface *Srf_tilesheet = NULL;
SDL_Surface *Srf_background = NULL;
SDL_Surface *Srf_foreground = NULL;
SDL_Surface *Srf_character = NULL;

/*Sound effects*/
Mix_Chunk *pauseSound = NULL;

/*The map matrix*/
Map **MapMatrix;
/*The levels*/
Stage stage;
/*The Player*/
Character player;

/*The frames that divide the screen*/
SDL_Rect frameTop;
SDL_Rect frameBottom;

/*The tiles clipper*/
SDL_Rect clipper[TILESHEET_T];
/*The camera that controls which area of the map is exhibited*/
SDL_Rect camera;

/*General counters of position*/
int levelRow, levelCol;
int i, j, k;

/*Layers to control movement of background and foreground*/
Layer bg1, bg2, bgtotal, oldbg;
Layer fg1, fg2, fgtotal, oldfg;
int bgWidth = 1024, fgWidth = 1024;	/*total width of the background*/
int bgepoint, fgepoint;	/*endline points of the background*/

char stageTitle[50] = "\0";

int gravity;

/*The collision rectangles for the player and the tiles*/
SDL_Rect playerRect;
SDL_Rect *tileRect;
SDL_Surface *Srf_square;


/*Initialize game stuff*/
void GameStart()
{
	/* Prepare the layout */
	frameTop.x = 0;
	frameTop.y = 0;
	frameTop.w = Screen_Width - 2*frameTop.x;
	frameTop.h = 484;	/* TILE_SZ(24) * N_TILES(22) - filete*/

	frameBottom.x = 4;
	frameBottom.y = 490;
	frameBottom.w = Screen_Width - 2*frameBottom.x;
	frameBottom.h = Screen_Height - frameTop.y;
	/* End of Layout */

	/*Load the fonts that are going to be used*/
	pauseFont = TTF_OpenFont("font/forte.ttf", 50);
	stdfont = TTF_OpenFont("font/calibri.ttf", 35);
	stdfont_italic = TTF_OpenFont("font/calibrii.ttf", 30);

	/*Load the sound effects*/
	pauseSound = Mix_LoadWAV("sound/pause.wav");

	/*Prepare the clipper to the tilesize and sheetsize we are going to use*/
	ClipTiles(24);

	/*Start with no stage loaded*/
	stage = stage0;

	/*Background and Foreground positions*/
	bgtotal.x = fgtotal.x = 0;
	bg1.x = fg1.x = Screen_Width;
	bg2.x = fg2.x = 0;
	oldbg.x = oldfg.x = 0;
	bgepoint = bgWidth - Screen_Width;
	fgepoint = fgWidth - Screen_Width;

	/*Prepare the character*/
	player.Srf_character = LoadImage("Assets/Game/character.png");
	player.w = 59;
	player.h = 81;
	player.x = 10;
	player.y = 60;
	player.yvel = 4;
	player.xvel = 4;
	player.accel = 2;
	//gravity = 2;

	/*Set the animations*/



	/*COLLISION*/
	playerRect.x = player.x;
	playerRect.y = player.y;
	playerRect.w = player.w;
	playerRect.h = player.h;

	Srf_square = LoadImage("Assets/square.png");

}

/*Load map information from file and store it accordingly on a structured matrix*/
int LoadMap(char *filename)
{
	k = 0;

	FILE *mapfile;

	int tmp = 0, *p;
	int currentLayer = 1;
	int tileSize;

	mapfile = fopen(filename, "r");
	if(mapfile == NULL)
	{
		fprintf(error, "Failed loading file %s\n", filename);
		return -1;
	}

	/* Title Line */
	fscanf(mapfile, "%s", stageTitle);
	PreviewScreen(stage);

	/* fscanf needs to store the data read into a pointer */
	p = &tmp;

	/* Read how many tiles we have */
	fscanf(mapfile, "%d", p);
	tileSize = *p;
	fscanf(mapfile, "%d x ", p);
	levelRow = *p;
	fscanf(mapfile, "%d x ", p);
	levelCol = *p;

	camera.x = 0;
	camera.y = 0;
	camera.w = Screen_Width;
	camera.h = 465;

	/*Allocate enough space for the number of tiles on each layer - levelRow * levelCol * layerNumber*/
	tileRect = (SDL_Rect*)malloc((levelRow*levelCol*LAYER_TOTAL)*sizeof(SDL_Rect));

	/* Dynamically reserve enough memory to the matrix */
	MapMatrix = (Map **)malloc(levelRow * sizeof(*MapMatrix));
	/*If successful continue*/
	if(MapMatrix != NULL)
	{
		/*Loop through each row pointer to allocate memory for collumn pointer*/
		for(int cnt = 0; cnt < levelRow; cnt++)
		{
			MapMatrix[cnt] = (Map *)malloc(levelCol * sizeof(**MapMatrix));

			if(MapMatrix[cnt] == NULL)
			{
				fprintf(error, "Memory allocation failed for the map matrix\n");
				return -1;
			}
		}
	}
	else
	{
		fprintf(error, "Memory allocation failed for the map matrix\n");
		return -1;
	}

	for(int n = 1; n <= LAYER_TOTAL; n++)
	{
		for(i = 0; i < levelRow; i++)
		{
			for(j = 0; j < levelCol; j++)
			{
				fscanf(mapfile, "%d", p);
				MapMatrix[i][j].layer.x = *p;

				fscanf(mapfile, "%d", p);
				MapMatrix[i][j].layer.y = *p;

				fscanf(mapfile, "%d", p);
				MapMatrix[i][j].layer.tile = *p;

				fscanf(mapfile, "%d", p);
				MapMatrix[i][j].layer.col = *p;

				if(MapMatrix[i][j].layer.col == 1)
				{
					tileRect[k].x = MapMatrix[i][j].layer.x;
					tileRect[k].y = MapMatrix[i][j].layer.y;
					tileRect[k].w = tileSize;
					tileRect[k].h = tileSize;

					k++;
				}

				switch(n)
				{
					case 1:
						MapMatrix[i][j].layer1 = MapMatrix[i][j].layer;
						/*printf("%d  ", currentLayer);
						printf("%d  ", Matrix[i][j].layer1.x);
						printf("%d  ", Matrix[i][j].layer1.y);
						printf("%d  ", Matrix[i][j].layer1.tile);
						printf("%d\n", Matrix[i][j].layer1.col);*/
						break;
					case 2:
						MapMatrix[i][j].layer2 = MapMatrix[i][j].layer;
						break;
					case 3:
						MapMatrix[i][j].layer3 = MapMatrix[i][j].layer;
						break;
					case 4:
						MapMatrix[i][j].layer4 = MapMatrix[i][j].layer;
						break;
				}
			}
		}
	}

	/*Close the map file when finished*/
	fclose(mapfile);

	return 0;
}

/*Draws the current level - loaded on LoadMap*/
void DrawMap(Stage level, Ground groundlayer)
{
	/*Background image and the 3 first layers*/
	if(groundlayer == background)
	{
		DrawImage(Screen_Width-bg1.x, 0, Srf_background, Srf_Screen, NULL);
		if(bgtotal.x >= bgepoint)
			DrawImage(Screen_Width-bg2.x, 0, Srf_background, Srf_Screen, NULL);

		for(int n = 1; n <= LAYER_TOTAL - 1; n++)
		{
			for(i = 0; i < levelRow; i++)
			{
				for(j = 0; j < levelCol; j++)
				{
					switch(n)
					{
						case 1:
							MapMatrix[i][j].layer = MapMatrix[i][j].layer1;
							break;
						case 2:
							MapMatrix[i][j].layer = MapMatrix[i][j].layer2;
							break;
						case 3:
							MapMatrix[i][j].layer = MapMatrix[i][j].layer3;
							break;
					}

					if((MapMatrix[i][j].layer.x + TILE_SIZE >= camera.x && MapMatrix[i][j].layer.x - 20 <= camera.x + camera.w)
						&& (MapMatrix[i][j].layer.y + TILE_SIZE >= camera.y && MapMatrix[i][j].layer.y - 20 <= camera.y + camera.h))
					{
						DrawImage(MapMatrix[i][j].layer.x - camera.x, MapMatrix[i][j].layer.y - camera.y, Srf_tilesheet, Srf_Screen, &clipper[MapMatrix[i][j].layer.tile]);
					}
				}
			}
		}
	}
	/*Foreground image and the last layer*/
	else if(groundlayer == foreground)
	{
		for(i = 0; i < levelRow; i++)
		{
			for(j = 0; j < levelCol; j++)
			{
				MapMatrix[i][j].layer = MapMatrix[i][j].layer4;

				if((MapMatrix[i][j].layer.x + TILE_SIZE >= camera.x && MapMatrix[i][j].layer.x - 20 <= camera.x + camera.w)
					&& (MapMatrix[i][j].layer.y + TILE_SIZE >= camera.y && MapMatrix[i][j].layer.y - 20 <= camera.y + camera.h))
				{
					DrawImage(MapMatrix[i][j].layer.x - camera.x, MapMatrix[i][j].layer.y - camera.y, Srf_tilesheet, Srf_Screen, &clipper[MapMatrix[i][j].layer.tile]);
				}
			}
		}

		DrawImage(Screen_Width-fg1.x, 0, Srf_foreground, Srf_Screen, NULL);
		if(fgtotal.x >= fgepoint)
			DrawImage(Screen_Width-fg2.x, 0, Srf_foreground, Srf_Screen, NULL);
	}
}

/*The camera that controls the area of the map being exhibited*/
void SetCamera(void)
{
	if(camera.x < 0)
	{
		camera.x = 0;

		bgtotal.x = 0;
		bg1.x = Screen_Width;
		bg2.x = 0;
	}
	if(camera.x + camera.w > (levelRow * TILE_SIZE) - TILE_SIZE)
	{
		camera.x = (levelRow * TILE_SIZE) - TILE_SIZE - camera.w;

		if(bgtotal.x > 0)
		{
			bgtotal.x -= 8;
			bg1.x -= 8;
			bg2.x -= 8;
		}
	}

	if(camera.y < 0)
	{
		camera.y = 0;
	}
	if(camera.y + camera.h > (levelCol*TILE_SIZE) - TILE_SIZE)
	{
		camera.y = (levelCol*TILE_SIZE) - TILE_SIZE - camera.h;
	}
}

/*Pause Screen*/
void PauseScreen(void)
{
	/*Shade*/
	Srf_pause = TTF_RenderText_Blended(pauseFont, "PAUSE", darkgreen);
	DrawImage(Screen_Width/2 - 95, Screen_Height/2 - 45, Srf_pause, Srf_Screen, NULL);
	/*Foreground*/
	Srf_pause = TTF_RenderText_Blended(pauseFont, "PAUSE", red);
	DrawImage(Screen_Width/2 - 98, Screen_Height/2 - 48, Srf_pause, Srf_Screen, NULL);

	SDL_Flip(Srf_Screen);
}

void PreviewScreen(Stage level)
{
	char path[10][50], title[50];

	/*Adapts the stage level to teh filename of teh corresponding asset*/
	strcpy(path[0], "Assets/Background/");
	strcpy(path[1], "Assets/Foreground/");
	strcpy(path[2], "Assets/Preview/");
	strcpy(path[3], "Assets/Sheets/");
	for(int i = 0; i < 4; i++)
	{
		switch(level)
		{
			case 1:
				strcat(path[i], "stage1a");
				strcpy(title, "Stage1-1");
				break;
		}
	}
	strcat(path[0], ".png");
	strcat(path[1], ".png");
	strcat(path[2], ".png");
	strcat(path[3], ".png");

	/*Load each asset at a time*/
	Srf_background = LoadImage(path[0]);
	Srf_foreground = LoadImage(path[1]);
	Srf_preview = LoadImage(path[2]);
	Srf_tilesheet = LoadImage(path[3]);

	/*Fill the background with black color*/
	SDL_FillRect(Srf_Screen, NULL, SDL_MapRGB(Srf_Screen->format, 0, 0, 0));

	/*Draws the tile and the corresponding image*/
	Srf_load = TTF_RenderText_Blended(stdfont, title, white);
	DrawImage(Screen_Width/2 - 70, Screen_Height/2 - 150, Srf_load, Srf_Screen, NULL);
	DrawImage(Screen_Width/2 - 100, Screen_Height/2 - 80, Srf_preview, Srf_Screen, NULL);

	SDL_Flip(Srf_Screen);
	SDL_Delay(5000);
}

void ClipTiles(int tileSize)
{
	int i = 0;
	int j = 0;
	int nl = 1;  //newline constant

	for(int a = 0; a < TILESHEET_T; a++)
	{
		if(a == 13 * nl)	//13 because we have 13 tiles on each row
		{
			i = 0;

			j++;
			nl++;
		}

		clipper[a].w = tileSize;
		clipper[a].h = tileSize;
		clipper[a].x = clipper[a].w * i;
		clipper[a].y = clipper[a].h * j;

		i++;
	}
}

/*Checks for collision between two objects*/
bool CheckCollision(SDL_Rect ObjectA, SDL_Rect ObjectB)
{
	/*The sides of the rectangles*/
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	/*Calculate the sides of both rectangles*/
	leftA = ObjectA.x;
	rightA = ObjectA.x + ObjectA.w;
	topA = ObjectA.y;
	bottomA = ObjectA.y + ObjectA.h;

	leftB = ObjectB.x;
	rightB = ObjectB.x + ObjectB.w;
	topB = ObjectB.y;
	bottomB = ObjectB.y + ObjectB.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB ) { return false; }
	if( topA >= bottomB ) { return false; }
	if( rightA <= leftB ) { return false; }
	if( leftA >= rightB ) { return false; }

	//If none of the sides from A are outside B
	return true;

	/*If neither set of collision boxes touched*/
	//return none;
}

/*Draws the player on screen*/
void DrawCharacter(void)
{
	DrawImage(player.x, player.y, Srf_character, Srf_Screen, NULL);
}

/*Get player movement and check for collision for the tiles arround*/
void CharacterUpdate(void)
{
	int k2 = 0;

	playerRect.x = player.x;
	playerRect.y = player.y;

	for(int cnt = 0; cnt < k; cnt++)
	{
		if(CheckCollision(playerRect, tileRect[k2]) == true)
		{
			player.xvel = 0;
			player.yvel = 0;
			break;
		}

		k2++;
	}

	//printf("player.x:%d     player.y:%d\n", player.x, player.y);
}
