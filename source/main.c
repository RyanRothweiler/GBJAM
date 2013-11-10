//----------------------------------------includes
#include "stdio.h"
#include "gb.h"
#include "rand.h"
#include "time.h"

#include "monster.c"
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

	BackgroundLoad(); //load background stuff
	SHOW_BKG;

	set_sprite_data(0, 48, SpriteTiles); //load sprites
	PlayerLoad(); //load player stuff
	MonsterLoad(); //loads the monster
	SpriteNum += 4;
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
		SHOW_SPRITES;

		//monster stuff
		MonsterUpdate(SpriteNum);

		//player stuff
		num = PlayerCheckControls(SpriteNum);
		if (num == 1) //then a bullet was instantiated
		{
			SpriteNum++;
			PlayerSlideBack();
			PlayerSlideBack();
			PlayerSlideBack();
			PlayerSlideBack();
			PlayerUpdate(SpriteNum);

			HIDE_SPRITES; //clear unused sprites
		}

		num = PlayerUpdate(SpriteNum); 
		if (num == 1) //then a bullet died
		{
			set_sprite_tile(SpriteNum, 5); //hide the players current sprite
			SpriteNum--;
			move_sprite(SpriteNum, P_PosX, P_PosY); //and show the new 
		}		
		
		//woah there sparky
		delay(20);
	}
}