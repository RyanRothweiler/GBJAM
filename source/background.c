//includes
#include "graphics\background\BackgroundTiles.h" //the tiles
#include "graphics\background\BackgroundTiles.c"

#include "graphics\background\BackgroundMap.h" //the map
#include "graphics\background\BackgroundMap.c" 

#include "graphics\background\BackgroundMapColliders.h" //the map colilders
#include "graphics\background\BackgroundMapColliders.c" 




//----------------------------------------Variables
int B_BackgroundOffsetX = 0;
int B_BackgroundOffsetY = 0;





//----------------------------------------General Methods
//moves the background up the amount given
void BackgroundMoveUp(int speed, int SpriteNum)
{
	scroll_bkg(0, speed);
	B_BackgroundOffsetY += speed;
	MonsterMoveUp(0, SpriteNum);
}

//move background down the amount given
void BackgroundMoveDown(int speed, int SpriteNum)
{
	scroll_bkg(0, speed * -1);
	B_BackgroundOffsetY += speed * -1;
	MonsterMoveDown(0, SpriteNum);
}

//move background right the amount given
void BackgroundMoveRight(int speed, int SpriteNum)
{
	scroll_bkg(speed * -1, 0);
	B_BackgroundOffsetX += speed * -1;
	MonsterMoveRight(0, SpriteNum);
}

//move background left the amount given
void BackgroundMoveLeft(int speed, int SpriteNum)
{
	scroll_bkg(speed, 0);
	B_BackgroundOffsetX += speed;
	MonsterMoveLeft(0, SpriteNum);
}

//checks if the given position collides with anything
int CheckCollision(int x, int y, int down, int right)
{
	y += B_BackgroundOffsetY;
	x += B_BackgroundOffsetX;

	if (!down && !right) //if either check up or left
	{
		if (BackgroundMapColliders[(((y - 18) / 8)*BackgroundMapCollidersWidth) + ((x - 9) / 8)] == 0x01) //collides
		{
			return 1;
		}
		else //doesn't collide
		{
			return 0;
		}
	}
	else //else checking down or right
	{
		if (BackgroundMapColliders[(((y - 9) / 8)*BackgroundMapCollidersWidth) + ((x) / 8)] == 0x01) //collides
		{
			return 1;
		}
		else //doesn't collide
		{
			return 0;
		}
	}
}





//----------------------------------------Sprite Methods
//laod the background info
void BackgroundLoad()
{
	set_bkg_data(0, 15, BackgroundTiles);
	set_bkg_tiles(0, 0, BackgroundMapWidth, BackgroundMapHeight, BackgroundMap);
}