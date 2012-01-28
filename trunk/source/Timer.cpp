#include "../header/Global.h"
#include "../header/Timer.h"


/*Initialize the variables to start counting the time*/
Timer startTimer(Timer time)
{
    time.startTicks = 0;
    time.pausedTicks = 0;
    time.paused = false;
    time.started = false;

	return time;
}

/*Start the timer*/
Timer start(Timer time)
{
    time.started = true;
    time.paused = false;
    time.startTicks = SDL_GetTicks();

	return time;
}

/*Stop the timer*/
Timer stop(Timer time)
{
    time.started = false;
    time.paused = false;

	return time;
}

/*Pause the timer if possible*/
Timer pause(Timer time)
{
    /*If the timer is running and isn't already paused*/
    if((time.started == true) && (time.paused == false))
    {
        time.paused = true;

        /*Calculate the paused ticks*/
        time.pausedTicks = SDL_GetTicks() - time.startTicks;
    }
	else if(time.paused == true)	/*If it was already paused -> unpause*/
	{
		time.paused = false;

        /*Reset the starting ticks*/
        time.startTicks = SDL_GetTicks() - time.pausedTicks;
        time.pausedTicks = 0;
	}

	return time;
}

/*Get the current number of ticks that the timer counted*/
int getTicks(Timer time)
{
    if(time.started == true)
    {
        if(time.paused == true)
        {
            /*Return the number of ticks when the timer was paused*/
            return time.pausedTicks;
        }
        else
        {
            /*Return the current time minus the start time*/
            return SDL_GetTicks() - time.startTicks;
        }
    }

    /*If the timer isn't running*/
    return 0;
}
