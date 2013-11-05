//includes
#include "graphics\background\BackgroundTiles.h" //the tiles
#include "graphics\background\BackgroundTiles.c"

#include "graphics\background\BackgroundMap.h" //the map
#include "graphics\background\BackgroundMap.c" 

#include "graphics\background\BackgroundMapColliders.h" //the map colilders
#include "graphics\background\BackgroundMapColliders.c" 




//----------------------------------------Variables





//----------------------------------------General Methods
int CheckCollision(int x, int y, int down, int right)
{
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