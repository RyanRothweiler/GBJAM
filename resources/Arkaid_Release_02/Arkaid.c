/*
 *  The main file for the game of Noah's Arkaid!
 */
#include <gb.h>

#include "BungBkg\bungbkg.h"
#include "Splash\Splash.h"
#include "MainMenu\MainMenu.h"
#include "Story\Story.h"
#include "Game\Game.h"
#include "Record\Record.h"

void main(void)
{
	UWORD randSeed;
   unsigned int menuChoice;
   UBYTE firstRun;

   firstRun = 1;

   DISPLAY_ON;

   /* This function will show the Bung Background and wait for a keypress
    * It will also return a number based on how long it took before a key was pressed */
   SWITCH_ROM_MBC1((UWORD)2); /* showBungBkg is in ROM bank 2 */
	randSeed += showBungBkg();
   SWITCH_ROM_MBC1((UWORD)0); /* showBungBkg is in ROM bank 2 */

   /* This function will show the Noah's Arkaid background (intro) and wait for a keypress
    * It will also return a number based on how long it took before a key was pressed */
   SWITCH_ROM_MBC1((UWORD)3); /* showSplash is in ROM bank 3 */
   randSeed += showSplash();
   SWITCH_ROM_MBC1((UWORD)0); /* showSplash is in ROM bank 3 */

   initrand(randSeed);  /* Init the random number generator */

   while(1)  /* infinite loop */
   {
	   /* This function will display a main menu and allow the user to choose settings or whatever
   	 * some constant (like MENU_STARTGAME) should be returned */
      SWITCH_ROM_MBC1((UWORD)4); /* mainMenu is in ROM bank 4 */
		menuChoice = mainMenu();
      SWITCH_ROM_MBC1((UWORD)0); /* mainMenu is in ROM bank 4 */

   	switch(menuChoice)
	   {
      	case MENU_STORYLINE:
            SWITCH_ROM_MBC1((UWORD)5); /* displayStoryline is in ROM bank 5 */
         	displayStoryline();
            SWITCH_ROM_MBC1((UWORD)0); /* displayStoryline is in ROM bank 5 */
            break;

      	case MENU_STARTGAME: /* Start the game */
         	playGame(firstRun);       /* This function will be responsible for all of the in-game functionality */
            firstRun = 0;
            break;

      	case MENU_RECORDSOUNDS: /* Start the game */
            SWITCH_ROM_MBC1((UWORD)6); /* recordSounds is in ROM bank 6 */
         	recordSounds();      /* This function will be responsible for recording the user sounds with the PocketVoice */
            SWITCH_ROM_MBC1((UWORD)0); /* recordSounds is in ROM bank 6 */
            break;

   		default:
      		break; /* Shouldn't happen */
	   }
   }
}

