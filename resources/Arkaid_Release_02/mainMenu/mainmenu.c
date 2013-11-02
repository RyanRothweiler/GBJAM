#include <gb.h>
#include "MainMenu.h"


#include "menu_t.h"		/*the tiles and palette entries*/
#include "menu_t.c"

#include "menu_m.h"		/*the map (pointers to tiles)*/
#include "menu_m.c"

#include "menu_p.h"		/*the map's palette entries (pointers to palette)*/
#include "menu_p.c"

#include "pointer.h"		/*the pointer*/
#include "pointer.c"

unsigned int pointerX = 36;
unsigned int pointerTile;
unsigned int currSelection; /* what the pointer is currently pointing to */
unsigned int pointerYPositions[] =
{
   0,   /*unused*/
   80,  /*MENU_STORYLINE*/
   92,  /*MENU_RECORDSOUNDS*/
   104  /*MENU_STARTGAME*/
};
#define NUM_SELECTIONS 3 /* total number of menu items (not counting the unused) */

UWORD menuPalCGB[] =
{
  menuTilesCGBPal0c0,menuTilesCGBPal0c1,menuTilesCGBPal0c2,menuTilesCGBPal0c3,
  menuTilesCGBPal1c0,menuTilesCGBPal1c1,menuTilesCGBPal1c2,menuTilesCGBPal1c3,
  menuTilesCGBPal2c0,menuTilesCGBPal2c1,menuTilesCGBPal2c2,menuTilesCGBPal2c3,
  menuTilesCGBPal3c0,menuTilesCGBPal3c1,menuTilesCGBPal3c2,menuTilesCGBPal3c3,
  menuTilesCGBPal4c0,menuTilesCGBPal4c1,menuTilesCGBPal4c2,menuTilesCGBPal4c3,
  menuTilesCGBPal5c0,menuTilesCGBPal5c1,menuTilesCGBPal5c2,menuTilesCGBPal5c3,
  menuTilesCGBPal6c0,menuTilesCGBPal6c1,menuTilesCGBPal6c2,menuTilesCGBPal6c3,
  menuTilesCGBPal7c0,menuTilesCGBPal7c1,menuTilesCGBPal7c2,menuTilesCGBPal7c3
};

UWORD pointerPalCGB[] =
{
  pointerTilesCGBPal0c0,pointerTilesCGBPal0c1,pointerTilesCGBPal0c2,pointerTilesCGBPal0c3
};

void setupPointer()
{
   SPRITES_8x8;

   currSelection = MENU_STORYLINE;

   pointerTile = 1; /* the current tile for the pointer */

   set_sprite_palette(0, 1, &pointerPalCGB[0]);

   set_sprite_data(0, 9, pointerTiles);

   set_sprite_tile(0, pointerTile);
   set_sprite_prop(0, pointerTilesCGB[pointerTile]);

   move_sprite(0, pointerX, pointerYPositions[currSelection]);

   SHOW_SPRITES;
}

void updatePointer()
{
   pointerTile++;
   if(pointerTile > 8)
      pointerTile = 1;
   
   set_sprite_tile(0, pointerTile);
   set_sprite_prop(0, pointerTilesCGB[pointerTile]);
}

unsigned int checkButtons()
{
   int joy,doMove;
   static unsigned int lastDir;


   joy = joypad();
   doMove = 0;

   if(!joy)/*nothing was pressed */
   {
      lastDir = 0;
      return 0;
   }
   else if(!(joy & J_DOWN || joy & J_SELECT || joy & J_UP))
      lastDir = 0;

   if(joy & J_A || joy & J_START)
   {
      return currSelection;
   }

   if((joy & J_DOWN || joy & J_SELECT) && (lastDir != J_DOWN))
   {
      currSelection++;
      if(currSelection > NUM_SELECTIONS)
         currSelection = 1;
      doMove = 1;
      lastDir = J_DOWN;
   }
   else if((joy & J_UP) && (lastDir != J_UP))
   {
      currSelection--;
      if(currSelection <= 0)
         currSelection = NUM_SELECTIONS;
      doMove = 1;
      lastDir = J_UP;
   }

   if(doMove)
   {
      move_sprite(0, pointerX, pointerYPositions[currSelection]);
   }

   return 0; /* no final selection was made */
}

void hidePointer()
{
   move_sprite(0, 0, 0);  //take the pointer off of the screen
   HIDE_SPRITES;
}

unsigned int mainMenu()
{
   int selection;
   unsigned long int loopCount;

   DISPLAY_OFF;
   HIDE_BKG;

   move_bkg(0,0);

   set_bkg_palette( 7, 1, &menuPalCGB[28] );
   set_bkg_palette( 6, 1, &menuPalCGB[24] );
   set_bkg_palette( 5, 1, &menuPalCGB[20] );
   set_bkg_palette( 4, 1, &menuPalCGB[16] );
   set_bkg_palette( 3, 1, &menuPalCGB[12] );
   set_bkg_palette( 2, 1, &menuPalCGB[8] );
   set_bkg_palette( 1, 1, &menuPalCGB[4] );
   set_bkg_palette( 0, 1, &menuPalCGB[0] );

   set_bkg_data( 0, 141, menuTiles );

   VBK_REG = 1;
   set_bkg_tiles(0,0,menuMapWidth,menuMapHeight,menuPal);

   VBK_REG = 0;
   set_bkg_tiles(0,0,menuMapWidth,menuMapHeight,menuMap);

   SHOW_BKG;
   DISPLAY_ON;

   setupPointer();

   loopCount = 0;
   do
   {
      loopCount++;
      if((loopCount % 125) == 0)
         updatePointer(); /* animate the pointer */

      selection = checkButtons();

   } while(!selection); /* user hasn't made a selection */
   set_sprite_tile(0, 0); /* set to straight pointer while waiting */
   while(joypad() & (J_A | J_START)); /* wait for the user to let up */

   /* "Shoot" the pointer across the screen */
   loopCount = 0;
   while((pointerX + loopCount) <= 168)
   {
   	move_sprite(0, pointerX + loopCount, pointerYPositions[currSelection]);
      loopCount++;
      delay(4);
   }


   hidePointer();

   return selection;
}
