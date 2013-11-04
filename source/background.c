//includes
#include "graphics\background\background.h"
#include "graphics\background\background.c"




//----------------------------------------Variables
//int B_Posx = 0;
//int




//----------------------------------------Sprite Methods
void BackgroundUpdate()
{
	set_bkg_tiles(0, 0, 1, 1, BackgroundTiles);

	//scroll_bkg(10, 10);
}

//laod the background info
void BackgroundLoad()
{
	set_bkg_data(0, 2, BackgroundTiles);
}
