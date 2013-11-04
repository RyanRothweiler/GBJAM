//includes
#include "stdio.h"
#include "gb.h"

#include "player.c"
#include "background.c"


//some general global game settings
void SetupGame()
{
	DISPLAY_OFF;
	SPRITES_8x8; //set sprite size

	BackgroundLoad(); //load background stuff
	PlayerLoad(); //load player stuff

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
}

int main()
{
	SetupGame();
	
	//this is the game loop. this loops forever.
	while (1)
	{
		//background stuff
		BackgroundUpdate();

		//player stuff
		PlayerCheckControls();
		PlayerUpdate();
		
		//woah there sparky
		delay(20);
	}
}