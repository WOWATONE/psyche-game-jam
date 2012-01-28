#ifndef _TIMER_H_
#define _TIMER_H_


/*The timer to control frame rate*/
typedef struct{
	 /*The clock time when the timer started*/
    int startTicks;
    /*The ticks stored when the timer was paused*/
    int pausedTicks;
    /*The timer status*/
    bool paused;
    bool started;
}Timer;

/*FPS timer*/
Timer startTimer(Timer time);
Timer start(Timer time);
Timer stop(Timer time);
Timer pause(Timer time);
int getTicks(Timer time);



#endif
