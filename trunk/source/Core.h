#ifndef _CORE_H_
#define _CORE_H_

/*Disable function deprecation*/
#define _CRT_SECURE_NO_WARNINGS


/*Basic Manager Initiation*/
void CoreInit(void);
void CoreClear(void);
void CoreClose(void);

/*State Controllers*/
void MenuInit(void);
void MenuInput(void);
void MenuLogic(void);
void MenuDraw(void);

void LoadingScreen(void);

void GameStart(void);
void GameInput(void);
void GameLogic(void);
void GameRender(void);



#endif
