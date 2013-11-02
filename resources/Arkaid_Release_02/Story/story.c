#include <gb.h>

#include "story_t.h"		/*the tiles and palette entries*/
#include "story_t.c"

#include "story_m.h"		/*the map (pointers to tiles)*/
#include "story_m.c"

#include "story_p.h"		/*the map's palette entries (pointers to palette)*/
#include "story_p.c"



/**************************************************************************/
/* GBTD generates a series of constants which contain the various colors  */
/* used by your tileset. These constants will have to the turned into     */
/* an actual palette-table which can be send to the Gameboy. The          */
/* following array is such a table.                                       */
/*                                                                        */
/* Note that the color-constants are only generated when "Palette         */
/* colors" is checked when exporting from GBTD. They reside in WCTiles.h. */
/**************************************************************************/

UWORD storyPalCGB[] =
{
  storyTilesCGBPal0c0,storyTilesCGBPal0c1,storyTilesCGBPal0c2,storyTilesCGBPal0c3,
  storyTilesCGBPal1c0,storyTilesCGBPal1c1,storyTilesCGBPal1c2,storyTilesCGBPal1c3,
  storyTilesCGBPal2c0,storyTilesCGBPal2c1,storyTilesCGBPal2c2,storyTilesCGBPal2c3,
  storyTilesCGBPal3c0,storyTilesCGBPal3c1,storyTilesCGBPal3c2,storyTilesCGBPal3c3,
  storyTilesCGBPal4c0,storyTilesCGBPal4c1,storyTilesCGBPal4c2,storyTilesCGBPal4c3,
  storyTilesCGBPal5c0,storyTilesCGBPal5c1,storyTilesCGBPal5c2,storyTilesCGBPal5c3,
  storyTilesCGBPal6c0,storyTilesCGBPal6c1,storyTilesCGBPal6c2,storyTilesCGBPal6c3,
  storyTilesCGBPal7c0,storyTilesCGBPal7c1,storyTilesCGBPal7c2,storyTilesCGBPal7c3
};


/***************************************************/
/*                   Main program                  */
/***************************************************/
void displayStoryline()
{
   int joy;

	DISPLAY_OFF;
	HIDE_BKG;

  /*************************************************************************/
  /* the following set of routines loads the palettes into the display.    */
  /* each palette is send (one by one) by using the command:               */
  /*   set_bkg_palette( palette-no, first color in palette, Palette-data ) */
  /*************************************************************************/

  set_bkg_palette( 7, 1, &storyPalCGB[28] );
  set_bkg_palette( 6, 1, &storyPalCGB[24] );
  set_bkg_palette( 5, 1, &storyPalCGB[20] );
  set_bkg_palette( 4, 1, &storyPalCGB[16] );
  set_bkg_palette( 3, 1, &storyPalCGB[12] );
  set_bkg_palette( 2, 1, &storyPalCGB[8] );
  set_bkg_palette( 1, 1, &storyPalCGB[4] );
  set_bkg_palette( 0, 1, &storyPalCGB[0] );


  /*************************************************************************/
  /* Next, the tile-data is send to the display;
  /*************************************************************************/

  set_bkg_data( 0, 235, storyTiles );

  /*************************************************************************/
  /* Now it's time to send the map-data to the display. Again, in two      */
  /* steps, as the tiles and attributes reside in different banks.         */
  /* The data is send to the display by using the command:                 */
  /*   set_bkg_tiles( Left, Top, Width, Height, Map-data )                 */
  /*************************************************************************/

  VBK_REG = 1;
  set_bkg_tiles(0,0,storyMapWidth,storyMapHeight,storyPal);

  VBK_REG = 0;
  set_bkg_tiles(0,0,storyMapWidth,storyMapHeight,storyMap);



  /*************************************************************************/
  /* the remaining code init the Gameboy and makes it wait untill you turn */
  /* it off..                                                              */
  /*************************************************************************/

  SHOW_BKG;
  DISPLAY_ON;

   do
   {
   	joy = joypad();
   } while (!joy);
	waitpadup();

  	HIDE_BKG;

   return;
}
