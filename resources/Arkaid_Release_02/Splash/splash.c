/* Steps
1) Make a (24-bit BMP) graphic
2) Convert the graphic to Tiles with PalRed or GB Color Tiler (www.infinity.nl)
3) Make the Map, block filling it with the tiles from step 2 (in GBMB of course)
4) Optimize the Tiles/Map using GameMan (da Bomb app) with these settings
		Same Palette Redundancy Removal
		Remove Tiles that are Unused in Maps
5) Open the optimized Tiles in GBTD and export the tiles to <name>_t.c
		Include CGB Palette  (necessary?????)
      Export as one unit
      Then, save the Tiles when you're done exporting.
6) Go back into GBMB and open the optimized Map
7) Export the map to <name>_m.c with these options
		1 plane
      Property:  Tile Number
8) Export the map to <name>_p.c with these optione
		1 plane
      Property:  GBC Palette
*/


/****************************************************************/
/*              Display a Splash Screen                         */
/****************************************************************/
#include <gb.h>

#include "splash_t.h"		/*the tiles and palette entries*/
#include "splash_t.c"

#include "splash_m.h"		/*the map (pointers to tiles)*/
#include "splash_m.c"

#include "splash_p.h"		/*the map's palette entries (pointers to palette)*/
#include "splash_p.c"

#include "spl_win.c"

#define NUM_SPLASH_TILES 170

#define WIN_START_X 7
#define WIN_START_Y (8*13-1)

UWORD bkgPalCGB[32];/* used for the fade */

/**************************************************************************/
/* GBTD generates a series of constants which contain the various colors  */
/* used by your tileset. These constants will have to the turned into     */
/* an actual palette-table which can be send to the Gameboy. The          */
/* following array is such a table.                                       */
/*                                                                        */
/* Note that the color-constants are only generated when "Palette         */
/* colors" is checked when exporting from GBTD. They reside in WCTiles.h. */
/**************************************************************************/

UWORD splashPalCGB[] =
{
  splashTilesCGBPal0c0,splashTilesCGBPal0c1,splashTilesCGBPal0c2,splashTilesCGBPal0c3,
  splashTilesCGBPal1c0,splashTilesCGBPal1c1,splashTilesCGBPal1c2,splashTilesCGBPal1c3,
  splashTilesCGBPal2c0,splashTilesCGBPal2c1,splashTilesCGBPal2c2,splashTilesCGBPal2c3,
  splashTilesCGBPal3c0,splashTilesCGBPal3c1,splashTilesCGBPal3c2,splashTilesCGBPal3c3,
  splashTilesCGBPal4c0,splashTilesCGBPal4c1,splashTilesCGBPal4c2,splashTilesCGBPal4c3,
  splashTilesCGBPal5c0,splashTilesCGBPal5c1,splashTilesCGBPal5c2,splashTilesCGBPal5c3,
  splashTilesCGBPal6c0,splashTilesCGBPal6c1,splashTilesCGBPal6c2,splashTilesCGBPal6c3,
  splashTilesCGBPal7c0,splashTilesCGBPal7c1,splashTilesCGBPal7c2,splashTilesCGBPal7c3
};

void fadeSplashIn()
{
	int doneFading;
   int i;
   UBYTE r, g, b;
   UBYTE r2, g2, b2;

   doneFading = 0;

   while(!doneFading)
   {
   	doneFading = 1; /* hope for the best */

	   for(i = 0; i < 32; i++)
   	{
         r = bkgPalCGB[i] & 0x1F;
         g = (bkgPalCGB[i] >> 5) & 0x1F;
         b = (bkgPalCGB[i] >> 10) & 0x1F;

         r2 = splashPalCGB[i] & 0x1F;
         g2 = (splashPalCGB[i] >> 5) & 0x1F;
         b2 = (splashPalCGB[i] >> 10) & 0x1F;

         if(r < r2)
         {
            r++;
            doneFading = 0;
         }
         if(g < g2)
         {
            g++;
            doneFading = 0;
         }
         if(b < b2)
         {
            b++;
            doneFading = 0;
         }

   		bkgPalCGB[i] = RGB(r,g,b);
	   }

   	set_bkg_palette( 7, 1, &bkgPalCGB[28] );
	   set_bkg_palette( 6, 1, &bkgPalCGB[24] );
   	set_bkg_palette( 5, 1, &bkgPalCGB[20] );
	   set_bkg_palette( 4, 1, &bkgPalCGB[16] );
   	set_bkg_palette( 3, 1, &bkgPalCGB[12] );
	   set_bkg_palette( 2, 1, &bkgPalCGB[8] );
   	set_bkg_palette( 1, 1, &bkgPalCGB[4] );
	   set_bkg_palette( 0, 1, &bkgPalCGB[0] );

      delay(35);
   }

   set_bkg_palette(7, 1, &splashPalCGB[28]);
   set_bkg_palette(6, 1, &splashPalCGB[24]);
   set_bkg_palette(5, 1, &splashPalCGB[20]);
   set_bkg_palette(4, 1, &splashPalCGB[16]);
   set_bkg_palette(3, 1, &splashPalCGB[12]);
   set_bkg_palette(2, 1, &splashPalCGB[8]);
   set_bkg_palette(1, 1, &splashPalCGB[4]);
   set_bkg_palette(0, 1, &splashPalCGB[0]);
}


/***************************************************/
/*                   Main program                  */
/***************************************************/
UWORD showSplash()
{
	UWORD winCount, bkgCount, loopCount;
   int joy;
   int upDown;
   int leftRight;
   char winPos;
   long i;

   winCount = 0;
   bkgCount = 0;
   winPos = 0;

	//DISPLAY_OFF;
	//HIDE_BKG;
   HIDE_WIN;
   HIDE_SPRITES;  /* Just in case */

  /*************************************************************************/
  /* the following set of routines loads the palettes into the display.    */
  /* each palette is send (one by one) by using the command:               */
  /*   set_bkg_palette( palette-no, first color in palette, Palette-data ) */
  /*************************************************************************/

  /*
  set_bkg_palette( 7, 1, &splashPalCGB[28] );
  set_bkg_palette( 6, 1, &splashPalCGB[24] );
  set_bkg_palette( 5, 1, &splashPalCGB[20] );
  set_bkg_palette( 4, 1, &splashPalCGB[16] );
  set_bkg_palette( 3, 1, &splashPalCGB[12] );
  set_bkg_palette( 2, 1, &splashPalCGB[8] );
  set_bkg_palette( 1, 1, &splashPalCGB[4] );
  set_bkg_palette( 0, 1, &splashPalCGB[0] );
  */

   for(i = 0; i < 32; i++)
   {
   	bkgPalCGB[i] = 0;
   }

   set_bkg_palette( 7, 1, &bkgPalCGB[28] );
   set_bkg_palette( 6, 1, &bkgPalCGB[24] );
   set_bkg_palette( 5, 1, &bkgPalCGB[20] );
   set_bkg_palette( 4, 1, &bkgPalCGB[16] );
   set_bkg_palette( 3, 1, &bkgPalCGB[12] );
   set_bkg_palette( 2, 1, &bkgPalCGB[8] );
   set_bkg_palette( 1, 1, &bkgPalCGB[4] );
   set_bkg_palette( 0, 1, &bkgPalCGB[0] );

  /*************************************************************************/
  /* Next, the tile-data is send to the display;
  /*************************************************************************/

  set_bkg_data( 0, NUM_SPLASH_TILES, splashTiles );

  /*************************************************************************/
  /* Now it's time to send the map-data to the display. Again, in two      */
  /* steps, as the tiles and attributes reside in different banks.         */
  /* The data is send to the display by using the command:                 */
  /*   set_bkg_tiles( Left, Top, Width, Height, Map-data )                 */
  /*************************************************************************/

  VBK_REG = 1;
  set_bkg_tiles(0,0,splashMapWidth,splashMapHeight,splashPal);

  VBK_REG = 0;
  set_bkg_tiles(0,0,splashMapWidth,splashMapHeight,splashMap);

  //SHOW_BKG;
  //DISPLAY_ON;

  /* Here, we're going to make part of the map a Window so we can have motion
   * Note that it looks a lot like the _bkg_ calls */

  /* set_win_data(0, NUM_SPLASH_TILES, splashTiles); */

  VBK_REG = 1;
  set_win_tiles(0,0,21,6,splashWinPal);

  VBK_REG = 0;
  set_win_tiles(0,0,21,6,splashWinMap);

  move_win(WIN_START_X,WIN_START_Y);

  fadeSplashIn();

  SHOW_WIN;

  upDown = -1;  /* start going up */
  leftRight = -1; /* left */

   do
   {
      joy = joypad();
      bkgCount++;
      winCount++;
      loopCount++;
      if(bkgCount >= 1300)
      {
      	scroll_bkg(0,upDown);
         upDown *= -1;
         bkgCount = 0;
      }

      if(winCount >= 1200)
      {
      	/* move the Window */
         if(winPos >= 6)
         	winPos = 0;

         switch(winPos)
         {
         	case 0:
            case 4:
				  move_win(WIN_START_X-1,WIN_START_Y); /* to pos 1 */
              break;

         	case 1:
            case 3:
				  move_win(WIN_START_X-1,WIN_START_Y+1); /* to pos 2 */
              break;

         	case 2:
				  move_win(WIN_START_X,WIN_START_Y+1);  /* to pos 3 */
              break;

            case 5:
				  move_win(WIN_START_X,WIN_START_Y);  /* to pos 0 */
              break;
         }
         winCount = 0;

         winPos++;
      }

   } while (!joy);
	while(joypad())
   	loopCount++;

   move_bkg(0,0);
   move_win(WIN_START_X,WIN_START_Y);

   i = WIN_START_Y;
   while(i > 0)
   {
      i--;
      move_win(WIN_START_X,i);
      delay(10);
   }

   move_bkg(0, 144);

   i = 0;
   while(i < WIN_START_Y)
   {
      i++;
      move_win(WIN_START_X,i);
      delay(10);
   }

   DISPLAY_OFF;
   HIDE_BKG;
   HIDE_WIN;

   return loopCount;
}
