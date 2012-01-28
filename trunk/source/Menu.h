#ifndef _MENU_H_
#define _MENU_H_

typedef struct{
	int top;
	int left;
	int right;
	int bottom;

	int width;
	int height;

	SDL_Surface *Srf_button;

	SDL_Rect buttonClip[5];
	int frame;
}Button;

typedef enum {CursorOff, CursorClick, CursorOver} ButtonState;
typedef enum {none, button1, button2, button3, button4, button5, button6} ButtonSelect;

/*void MenuInit(void);
void MenuInput(void);
void MenuLogic(void);
void MenuDraw(void);*/
void SetButton(Button *button, int left, int top, int clipwidth, int clipheight);
int GetButton(Button *button);
void DrawButton(Button *button);




#endif
