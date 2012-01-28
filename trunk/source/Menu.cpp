#include "Global.h"
#include "Menu.h"


extern SDL_Surface *Srf_Screen;
extern SDL_Event event;
extern MainState CurrentState;
extern MainState NextState;

ButtonState MouseButton;
ButtonSelect Selection;
SDL_Surface *Srf_menuBackground = NULL;

Button playButton;
Button instructionsButton;
Button optionsButton;
Button exitButton;

int mouseX, mouseY;


void MenuInit(void)
{
	Srf_menuBackground = LoadImage("Assets/Menu/menu-forest.png");

	playButton.Srf_button = LoadImage("Assets/Menu/button_play_s.png");
	instructionsButton.Srf_button = LoadImage("Assets/Menu/button_instructions_s.png");
	optionsButton.Srf_button = LoadImage("Assets/Menu/button_options_s.png");
	exitButton.Srf_button = LoadImage("Assets/Menu/button_exit_s.png");


	SetButton(&playButton, 320, 100, 165, 75);
	SetButton(&instructionsButton, 188, 195, 433, 75);
	SetButton(&optionsButton, 265, 290, 278, 75);
	SetButton(&exitButton, 328, 385, 155, 75);

	mouseX = mouseY = 0;
}

/*Control the input user is sending - mouse or keyboard*/
void MenuInput(void)
{
	/*Run the loop if an input is on the poll of events*/
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			CurrentState = Exit;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(MouseButton == CursorOver)
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					MouseButton = CursorClick;
					switch(Selection)
					{
						case button1:
							playButton.frame = 2;
							CurrentState = StageSelection;
							break;
						case button2:
							instructionsButton.frame = 2;
							break;
						case button3:
							optionsButton.frame = 2;
							break;
						case button4:
							exitButton.frame = 2;
							CurrentState = Exit;
							break;
					}
				}
			}
		}
		if(event.type == SDL_MOUSEBUTTONUP)
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				MouseButton = CursorOff;
				Selection = none;
				playButton.frame = 0;
				instructionsButton.frame = 0;
				optionsButton.frame = 0;
				exitButton.frame = 0;
			}
		}

	}

}

void MenuLogic(void)
{
	/*Check with mouse cursor is hovering the button*/
	if(MouseButton != CursorClick)
	{
		if(GetButton(&playButton))
		{
			MouseButton = CursorOver;
			Selection = button1;
			playButton.frame = 1;
		}
		else if(GetButton(&instructionsButton))
		{
			MouseButton = CursorOver;
			Selection = button2;
			instructionsButton.frame = 1;
		}
		else if(GetButton(&optionsButton))
		{
			MouseButton = CursorOver;
			Selection = button3;
			optionsButton.frame = 1;
		}
		else if(GetButton(&exitButton))
		{
			MouseButton = CursorOver;
			Selection = button4;
			exitButton.frame = 1;
		}
		else
		{
			MouseButton = CursorOff;
			Selection = none;
			playButton.frame = 0;
			instructionsButton.frame = 0;
			optionsButton.frame = 0;
			exitButton.frame = 0;
		}
	}
}

void MenuDraw(void)
{
	/*Menu Background*/
	DrawImage(0, 0, Srf_menuBackground, Srf_Screen, NULL);

	/*Menu buttons*/
	DrawButton(&playButton);
	DrawButton(&instructionsButton);
	DrawButton(&optionsButton);
	DrawButton(&exitButton);

	SDL_Flip(Srf_Screen);
}


void SetButton(Button *button, int left, int top, int clipwidth, int clipheight)
{
	button->top = top;
	button->left = left;
	button->width = clipwidth;
	button->height = clipheight;

	button->right = button->left + button->width;
	button->bottom = button->top + button->height;

	button->buttonClip[0].w = button->width;
	button->buttonClip[0].h = button->height;
	button->buttonClip[0].x = 0;
	button->buttonClip[0].y = 0;

	button->buttonClip[1].w = button->width;
	button->buttonClip[1].h = button->height;
	button->buttonClip[1].x = 1*button->width;
	button->buttonClip[1].y = 0;

	button->buttonClip[2].w = button->width;
	button->buttonClip[2].h = button->height;
	button->buttonClip[2].x = 2*button->width;
	button->buttonClip[2].y = 0;

	button->frame = 0;
}

int GetButton(Button *button)
{
	/*Get mouse position and set the current state*/
	SDL_GetMouseState(&mouseX, &mouseY);

	if( (mouseX >= button->left && mouseX <= button->left + button->width) && (mouseY >= button->top && mouseY <= button->top + button->height) )
		return 1;

	return 0;
}

void DrawButton(Button *button)
{
	DrawImage(button->left, button->top, button->Srf_button, Srf_Screen, &button->buttonClip[button->frame]);

}
