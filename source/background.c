//includes
#include "graphics\background\BackgroundTiles.h" //the tile info
#include "graphics\background\BackgroundTiles.c"

#include "graphics\background\BackgroundMap.h" //the map info
#include "graphics\background\BackgroundMap.c" 




//----------------------------------------Variables



//----------------------------------------Sprite Methods
void BackgroundUpdate()
{
	set_bkg_tiles(0, 0, BackgroundMapWidth, BackgroundMapHeight, BackgroundMap);
}

//laod the background info
void BackgroundLoad()
{
	set_bkg_data(0, 20, BackgroundTiles);
}
