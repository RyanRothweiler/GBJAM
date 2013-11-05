//----------------------------------------Includes
#include "graphics\bullets\BulletTiles.h"
#include "graphics\bullets\BulletTiles.c"



//----------------------------------------Variables
int B_BulletNum = 0;
int B_BulletSpeed = 1; //the number of pixels to move the bullet each frame

int B1_Using = 0;
int B1_PosX = 0;
int B1_PosY = 0;
int B1_FrameIndex = 0;
int B1_Animating = 0; 
int B1_Dir = 0; //1 - north, 2 - east, 3 - south, 4 - west



//----------------------------------------Methods
//go through and update all the bullets positions and sprites
void BulletsUpdate(int SpriteNum)
{
	if (B1_Using)
	{
		//moving up
		if (B1_Dir = 1)
		{
			B1_PosY -= B_BulletSpeed;
		}
		//moving down
		if (B1_Dir = 3)
		{
			B1_PosY += B_BulletSpeed;
		}
		//moving right
		if (B1_Dir = 2)
		{
			B1_PosX += B_BulletSpeed;
		}
		//moving right
		if (B1_Dir = 3)
		{
			B1_PosX -= B_BulletSpeed;
		}
		move_sprite(1, B1_PosX, B1_PosY);

		SpriteNum = SpriteNum;
	}
}

//create another bullet
void BulletsAdd(int x, int y, int direction)
{
	if (!B1_Using)
	{
		//sprite stuff
		set_sprite_data(1, 5, BulletTiles);
		set_sprite_tile(1, 0);
		move_sprite(1, x, y);

		//data stuff
		B1_Using = 1;
		B1_PosX = x;
		B1_PosY = y;
		B1_Animating = 0;
		B1_Dir = direction;
	}
}




//----------------------------------------Sprite Methods
