//----------------------------------------includes
#include "stdio.h"
#include "gb.h"
#include "rand.h"
#include "time.h"

#include "background.c"
#include "player.c"

#include "graphics\sprites.h"
#include "graphics\sprites.c"




//----------------------------------------Variables
int SpriteNum = 0; //this holds the number of sprites and is used to identify which sprite
int num = 0; //general number




//----------------------------------------Methods
void SetupGame()
{
	DISPLAY_OFF;
	SPRITES_8x8; //set sprite size

	set_sprite_data(0, 27, SpriteTiles); //load sprites

	BackgroundLoad(); //load background stuff
	PlayerLoad(SpriteNum); //load player stuff

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
}





//----------------------------------------Game Loop
int main()
{
	SetupGame();
	
	//this is the game loop. this loops forever.
	while (1)
	{
		//player stuff
		num = PlayerCheckControls(SpriteNum);
		if (num == 1) //then a bullet was instantiated
		{
			SpriteNum++;
			PlayerSlideBack(SpriteNum);
			PlayerSlideBack(SpriteNum);
			PlayerSlideBack(SpriteNum);
			PlayerSlideBack(SpriteNum);
		}

		num = PlayerUpdate(SpriteNum); //then a bullet died
		if (num == 1)
		{
			set_sprite_tile(SpriteNum, 4);
			SpriteNum--;
			PlayerSlideBack(SpriteNum);
			PlayerSlideForward(SpriteNum);
		}
		
		
		//woah there sparky
		delay(20);
	}
}