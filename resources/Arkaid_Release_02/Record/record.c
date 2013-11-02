#include <gb.h>

#include "record_t.h"		/*the tiles and palette entries*/
#include "record_t.c"

#include "record_m.h"		/*the map (pointers to tiles)*/
#include "record_m.c"

#include "record_p.h"		/*the map's palette entries (pointers to palette)*/
#include "record_p.c"

UWORD recordPalCGB[] =
{
  recordTilesCGBPal0c0,recordTilesCGBPal0c1,recordTilesCGBPal0c2,recordTilesCGBPal0c3,
  recordTilesCGBPal1c0,recordTilesCGBPal1c1,recordTilesCGBPal1c2,recordTilesCGBPal1c3,
  recordTilesCGBPal2c0,recordTilesCGBPal2c1,recordTilesCGBPal2c2,recordTilesCGBPal2c3,
  recordTilesCGBPal3c0,recordTilesCGBPal3c1,recordTilesCGBPal3c2,recordTilesCGBPal3c3,
  recordTilesCGBPal4c0,recordTilesCGBPal4c1,recordTilesCGBPal4c2,recordTilesCGBPal4c3,
  recordTilesCGBPal5c0,recordTilesCGBPal5c1,recordTilesCGBPal5c2,recordTilesCGBPal5c3,
  recordTilesCGBPal6c0,recordTilesCGBPal6c1,recordTilesCGBPal6c2,recordTilesCGBPal6c3,
  recordTilesCGBPal7c0,recordTilesCGBPal7c1,recordTilesCGBPal7c2,recordTilesCGBPal7c3
};


/***************************************************/
/*                   Main program                  */
/***************************************************/
void recordSounds()
{
   int joy;

	DISPLAY_OFF;
	HIDE_BKG;

  /*************************************************************************/
  /* the following set of routines loads the palettes into the display.    */
  /* each palette is send (one by one) by using the command:               */
  /*   set_bkg_palette( palette-no, first color in palette, Palette-data ) */
  /*************************************************************************/

  set_bkg_palette( 7, 1, &recordPalCGB[28] );
  set_bkg_palette( 6, 1, &recordPalCGB[24] );
  set_bkg_palette( 5, 1, &recordPalCGB[20] );
  set_bkg_palette( 4, 1, &recordPalCGB[16] );
  set_bkg_palette( 3, 1, &recordPalCGB[12] );
  set_bkg_palette( 2, 1, &recordPalCGB[8] );
  set_bkg_palette( 1, 1, &recordPalCGB[4] );
  set_bkg_palette( 0, 1, &recordPalCGB[0] );


  /*************************************************************************/
  /* Next, the tile-data is send to the display;
  /*************************************************************************/

  set_bkg_data( 0, 235, recordTiles );

  /*************************************************************************/
  /* Now it's time to send the map-data to the display. Again, in two      */
  /* steps, as the tiles and attributes reside in different banks.         */
  /* The data is send to the display by using the command:                 */
  /*   set_bkg_tiles( Left, Top, Width, Height, Map-data )                 */
  /*************************************************************************/

  VBK_REG = 1;
  set_bkg_tiles(0,0,recordMapWidth,recordMapHeight,recordPal);

  VBK_REG = 0;
  set_bkg_tiles(0,0,recordMapWidth,recordMapHeight,recordMap);



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
