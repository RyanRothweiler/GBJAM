#include <gb.h>

#include "bung_t.h"		/*the tiles and palette entries*/
#include "bung_t.c"

#include "bung_m.h"		/*the map (pointers to tiles)*/
#include "bung_m.c"

#include "bung_p.h"		/*the map's palette entries (pointers to palette)*/
#include "bung_p.c"

#include "bungURL.h"		/* Scrolling URL for Bung WWW site */
#include "bungURL.c"

unsigned int urlX;
unsigned int urlY = 151;

UWORD bkgPalCGB[32];/* used for the fade */
UWORD bungPalCGB[] =
{
  bungTilesCGBPal0c0,bungTilesCGBPal0c1,bungTilesCGBPal0c2,bungTilesCGBPal0c3,
  bungTilesCGBPal1c0,bungTilesCGBPal1c1,bungTilesCGBPal1c2,bungTilesCGBPal1c3,
  bungTilesCGBPal2c0,bungTilesCGBPal2c1,bungTilesCGBPal2c2,bungTilesCGBPal2c3,
  bungTilesCGBPal3c0,bungTilesCGBPal3c1,bungTilesCGBPal3c2,bungTilesCGBPal3c3,
  bungTilesCGBPal4c0,bungTilesCGBPal4c1,bungTilesCGBPal4c2,bungTilesCGBPal4c3,
  bungTilesCGBPal5c0,bungTilesCGBPal5c1,bungTilesCGBPal5c2,bungTilesCGBPal5c3,
  bungTilesCGBPal6c0,bungTilesCGBPal6c1,bungTilesCGBPal6c2,bungTilesCGBPal6c3,
  bungTilesCGBPal7c0,bungTilesCGBPal7c1,bungTilesCGBPal7c2,bungTilesCGBPal7c3
};

UWORD bungURLPalCGB[] =
{
  bungURLTilesCGBPal0c0,bungURLTilesCGBPal0c1,bungURLTilesCGBPal0c2,bungURLTilesCGBPal0c3
};

void setupURL()
{
   unsigned int i;
   SPRITES_8x8;

   set_sprite_palette(0, 1, &bungURLPalCGB[0]);
   set_sprite_palette(1, 1, &bungURLPalCGB[4]);
   set_sprite_palette(2, 1, &bungURLPalCGB[8]);
   set_sprite_palette(3, 1, &bungURLPalCGB[12]);
   set_sprite_palette(4, 1, &bungURLPalCGB[16]);
   set_sprite_palette(5, 1, &bungURLPalCGB[20]);
   set_sprite_palette(6, 1, &bungURLPalCGB[24]);
   set_sprite_palette(7, 1, &bungURLPalCGB[28]);

   set_sprite_data(0, 16, bungURLTiles);

   urlX = 168;

   for(i = 0; i < 16; i++)
   {
      set_sprite_tile(i, i);
      set_sprite_prop(i, bungURLTilesCGB[i]);

      if((urlX + (i*8)) <= 100)
         move_sprite(i, urlX + (i*8), 0);  //take it off the screen
      else
         move_sprite(i, urlX + (i*8), urlY);
   }

   SHOW_SPRITES;
}

void moveURL()
{
   int i;

   urlX--;
   if(urlX > 168 && urlX < 220) /* if the whole URL is off the screen */
      urlX = 168; /* reset it */

   for(i = 15; i >= 0; i--)
   {
      if((urlX + (i*8)) <= 100)
      {
         move_sprite(i, urlX + (i*8), 0);  //take it off the screen
      }
      else
      {
         move_sprite(i, urlX + (i*8), urlY);
      }
   }
}

void fadeBkgIn()
{
	int doneFading;
   int fadeVal;
   int i;

   doneFading = 0;
   fadeVal = 0;

   while(!doneFading && (fadeVal <= 31))
   {
   	fadeVal++;

   	doneFading = 1; /* hope for the best */
	   for(i = 0; i < 32; i++)
   	{
   		if(bkgPalCGB[i] < bungPalCGB[i])
         {
	   		bkgPalCGB[i] = RGB(fadeVal,fadeVal,fadeVal);
            doneFading = 0; /* not done fading */
         }
         else
         	bkgPalCGB[i] = bungPalCGB[i];
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

   /* Make sure that we're using the correct palette */
  	set_bkg_palette( 7, 1, &bungPalCGB[28] );
   set_bkg_palette( 6, 1, &bungPalCGB[24] );
  	set_bkg_palette( 5, 1, &bungPalCGB[20] );
   set_bkg_palette( 4, 1, &bungPalCGB[16] );
  	set_bkg_palette( 3, 1, &bungPalCGB[12] );
   set_bkg_palette( 2, 1, &bungPalCGB[8] );
  	set_bkg_palette( 1, 1, &bungPalCGB[4] );
   set_bkg_palette( 0, 1, &bungPalCGB[0] );
}

void fadeBkgOut()
{
	int doneFading;
   int i;
   UBYTE r, g, b;

   doneFading = 0;

   for(i = 0; i < 32; i++)
  		bkgPalCGB[i] = bungPalCGB[i];

   while(!doneFading)
   {
   	doneFading = 1; /* hope for the best */
	   for(i = 0; i < 32; i++)
   	{
         r = bkgPalCGB[i] & 0x1F;
         g = (bkgPalCGB[i] >> 5) & 0x1F;
         b = (bkgPalCGB[i] >> 10) & 0x1F;

   		if(bkgPalCGB[i] > 0)
         {
            if(r)
               r--;
            if(g)
               g--;
            if(b)
               b--;

	   		bkgPalCGB[i] = RGB(r,g,b);
            doneFading = 0; /* not done fading */
         }
         else
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

      delay(35);
   }
}


void hideURL()
{
   int i;
   for(i = 0; i < 16; i++)
      move_sprite(i, 0, 0);  //take the tile off of the screen
   HIDE_SPRITES;
}

UWORD showBungBkg()
{
	UWORD loopCount;
   int joy;
   int i;

	DISPLAY_OFF;
	HIDE_BKG;

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

   set_bkg_data( 0, 247, bungTiles );

   VBK_REG = 1;
   set_bkg_tiles(0,0,bungMapWidth,bungMapHeight,bungPal);

   VBK_REG = 0;
   set_bkg_tiles(0,0,bungMapWidth,bungMapHeight,bungMap);

   move_bkg(0,0);

   SHOW_BKG;
   DISPLAY_ON;

	fadeBkgIn();

   setupURL();

   do
   {
      loopCount++;

      if((loopCount % 75) == 0)
	   	moveURL();

   	joy = joypad();
   } while (!joy);
	while(joypad())
   	loopCount++;

   hideURL();
   
 	fadeBkgOut();

  	//HIDE_BKG;


   return loopCount;
}
