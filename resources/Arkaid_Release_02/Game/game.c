#include <gb.h>
//#include <sound.h>

#include "..\Music\BkgMusic.h"  //for the bkg music

#include "game.h"
#include "game_t.c"      /* file containing tiles and data */
#include "game_t.h"      /* file containing tiles and data */

#include "back_t.c"
#include "back_t.h"
#include "back_m.c"
#include "back_m.h"
#include "back_p.c"
#include "back_p.h"
#define NUM_BKG_TILES 50

#include "infoW_t.c"
#include "infoW_t.h"
#include "infoW_m.c"
#include "infoW_m.h"
#include "infoW_p.c"
#include "infoW_p.h"
#define INFO_WIN_OFFSET NUM_BKG_TILES
#define NUM_WIN_TILES 59
#define WIN_POS_X 135
unsigned char offsetInfoWinMap[infoWinMapWidth*infoWinMapHeight];


/* The NUM_ANIMALS animals will be the first NUM_ANIMALS things in the gameTiles array */
/* 5x5 grid with an ark in the middle? */
/* NOTE that 5x5 grid will also be the 10-sprite per scan-line max, if necessary */
#define NUM_ANIMALS 12
#define NUM_TILES 22   /* NUM_ANIMALS + 2 pointers + FREE + 5 digit blocks*/

#define POINTER_TILE 0   /* 0 so it's on top of everything else */
#define POINTER_NO_TILE 1

#define CAT_TILE 3
#define FROG_TILE 4
#define DUCK_TILE 5
#define COW_TILE 6
#define PIG_TILE 7
#define ELEPHANT_TILE 8
#define BEAR_TILE 9
#define MONKEY_TILE 10
#define SNAKE_TILE 11
#define ROOSTER_TILE 12
#define DOG_TILE 13
#define SHEEP_TILE 14

#define FIRST_ANIMAL CAT_TILE
#define LAST_ANIMAL SHEEP_TILE

#define FREE_TILE 21
#define X_TILE 2
#define X_COUNT 24 /*there will be a max of 24 X's*/
#define X_SPRITE_START 8
UBYTE numXs;


#define FIRST_DIGIT_TILE 15
#define MATCH_COUNT_DIGITS 2
#define GUESS_COUNT_DIGITS 2 /* if you need more than 2, you're an idiot! */
#define SECOND_COUNT_DIGITS 3

#define MATCH_COUNT_START_X 74 /* if Guess has 2 digits, set to 82 */
#define MATCH_COUNT_START_Y 151

#define GUESS_COUNT_START_X 74
#define GUESS_COUNT_START_Y 141

#define SECOND_COUNT_START_X 105
#define SECOND_COUNT_START_Y 151
void updateTime();

#define DIGIT_SPRITE_START X_SPRITE_START+X_COUNT
#define MATCH_COUNT_SPRITE_START DIGIT_SPRITE_START
#define GUESS_COUNT_SPRITE_START MATCH_COUNT_SPRITE_START+MATCH_COUNT_DIGITS
#define SECOND_COUNT_SPRITE_START GUESS_COUNT_SPRITE_START+GUESS_COUNT_DIGITS


int pointerRow, pointerCol;

unsigned int spriteCount[NUM_TILES];   /* should be 0,1,2  2=both are in game */

/* pointerStartX and Y should be just to the bottom right of gridStartX and Y */
#define gridStartX 24
#define gridStartY 32
#define pointerStartX gridStartX+12
#define pointerStartY gridStartY+12

UBYTE time_counter;  //counter for timer interupt
UBYTE seconds;  //number of seconds that have passed
UBYTE clockOn;
UBYTE firstTimeRun;

#define NUM_ROWS 5
#define NUM_COLS 5
unsigned int grid[NUM_ROWS][NUM_COLS];  /* ROW x COL grid of tiles */

UBYTE winScroll;

int musicClock;

UWORD gamePal[] =
{
  gameTilesCGBPal0c0,gameTilesCGBPal0c1,gameTilesCGBPal0c2,gameTilesCGBPal0c3,
  gameTilesCGBPal1c0,gameTilesCGBPal1c1,gameTilesCGBPal1c2,gameTilesCGBPal1c3,
  gameTilesCGBPal2c0,gameTilesCGBPal2c1,gameTilesCGBPal2c2,gameTilesCGBPal2c3,
  gameTilesCGBPal3c0,gameTilesCGBPal3c1,gameTilesCGBPal3c2,gameTilesCGBPal3c3,
  gameTilesCGBPal4c0,gameTilesCGBPal4c1,gameTilesCGBPal4c2,gameTilesCGBPal4c3,
  gameTilesCGBPal5c0,gameTilesCGBPal5c1,gameTilesCGBPal5c2,gameTilesCGBPal5c3,
  gameTilesCGBPal6c0,gameTilesCGBPal6c1,gameTilesCGBPal6c2,gameTilesCGBPal6c3,
  gameTilesCGBPal7c0,gameTilesCGBPal7c1,gameTilesCGBPal7c2,gameTilesCGBPal7c3,
};

UWORD backPalCGB[] =
{
  backTilesCGBPal0c0,backTilesCGBPal0c1,backTilesCGBPal0c2,backTilesCGBPal0c3,
  backTilesCGBPal1c0,backTilesCGBPal1c1,backTilesCGBPal1c2,backTilesCGBPal1c3,
  backTilesCGBPal2c0,backTilesCGBPal2c1,backTilesCGBPal2c2,backTilesCGBPal2c3,
  backTilesCGBPal3c0,backTilesCGBPal3c1,backTilesCGBPal3c2,backTilesCGBPal3c3,
  backTilesCGBPal4c0,backTilesCGBPal4c1,backTilesCGBPal4c2,backTilesCGBPal4c3,
  backTilesCGBPal5c0,backTilesCGBPal5c1,backTilesCGBPal5c2,backTilesCGBPal5c3,
  backTilesCGBPal6c0,backTilesCGBPal6c1,backTilesCGBPal6c2,backTilesCGBPal6c3,
  backTilesCGBPal7c0,backTilesCGBPal7c1,backTilesCGBPal7c2,backTilesCGBPal7c3
};

void updateBkgMusic()
{
	   /* bkg music */
      if(musicClock >= 2)//7
      	musicClock = 0;
      //wait_vbl_done();
      if (!musicClock)
      {
			SWITCH_ROM_MBC1(7);	// you can choose here the bank where you place your song data in the exemple.bat file
      	music();
			SWITCH_ROM_MBC1(0);
      }
      musicClock++;
	   /* bkg music */
}

void setupInfoWin()
{
   /* This will set up the Info Window that will be used to show off some neat effetcs and
      advertise some personal info. */

   /* Remember that the Window needs to share a palette with the background. */

   /* Does it share tiles, too??? */
   unsigned int i;

   HIDE_WIN;

   /* change the map to an offset that won't interfere with the bkg map */
   for(i = 0; i < infoWinMapWidth*infoWinMapHeight; i++)
   {
   	offsetInfoWinMap[i] = infoWinMap[i] + INFO_WIN_OFFSET;
   }

   set_win_data(INFO_WIN_OFFSET, NUM_WIN_TILES, infoWinTiles);

   VBK_REG = 1;
   set_win_tiles(0,0,infoWinMapWidth,infoWinMapHeight,infoWinPal); /* offsets into the bkg palette */

   VBK_REG = 0;
   set_win_tiles(0,0,infoWinMapWidth,infoWinMapHeight,offsetInfoWinMap);

   move_win(0,0); /* off screen for now */
}

void updateInfoWin()
{
   /* This will update the Info Window that will be used to show off some neat effetcs and
      advertise some personal info. */

   /* this may never happen */

	winScroll++;
   //move_win(135,0-winScroll);
   //scroll_win(0,-1);
	if(winScroll >= 8)
   {
   	//move_win(135,0);
   	//scroll_win(0,8);
		winScroll = 0;
	}
}

void timeISR()
{
	updateBkgMusic();

	time_counter++;
	if((time_counter%16 == 0) && clockOn) //if it's been exactly 1 sec
  	{
   	seconds++;
      updateTime();
  	}
}

/*void vblISR()
{
	disable_interrupts();
	enable_interrupts();
}*/

void setupIrqs()
{
	time_counter = 0; /* make sure it's cleared */
	seconds = 0; /* start at 0 */

	disable_interrupts();
   clockOn = 0; //don't start the clock yet
   if(firstTimeRun)
		add_TIM(timeISR);
   /* unused for now add_VBL(vblISR); */
	enable_interrupts();
	set_interrupts(VBL_IFLAG);

	//Set clock to 4096hz (4096/256=16hz)
	TAC_REG = 0x04U;
	/* Handle VBL and TIM interrupts */
	set_interrupts(VBL_IFLAG | TIM_IFLAG);
}


/* Each sprite is actually 4 8x8 sprites
 *    or 2 8x16 sprites!?!?
 * This is a bit odd, but we can put it in 8x16 mode and
 *   do some tricks.
 */
void setup_sprite_16x16(UBYTE spriteNum, UBYTE tileNum)
{
   set_sprite_tile(spriteNum*2, tileNum*4);
   set_sprite_prop(spriteNum*2, gameTilesCGB[tileNum]);

   set_sprite_tile(spriteNum*2+1, tileNum*4+2);
   set_sprite_prop(spriteNum*2+1, gameTilesCGB[tileNum]);
}

void move_sprite_16x16(UBYTE spriteNum, int x, int y)
{
  	move_sprite(spriteNum*2,   x, y);
	move_sprite(spriteNum*2+1, x+8, y);
}

void setupSprites()
{
   UBYTE i;

   HIDE_SPRITES;
   SPRITES_8x16;

   set_sprite_palette(0, 1, &gamePal[0]);
   set_sprite_palette(1, 1, &gamePal[4]);
   set_sprite_palette(2, 1, &gamePal[8]);
   set_sprite_palette(3, 1, &gamePal[12]);
   set_sprite_palette(4, 1, &gamePal[16]);
   set_sprite_palette(5, 1, &gamePal[20]);
   set_sprite_palette(6, 1, &gamePal[24]);
   set_sprite_palette(7, 1, &gamePal[28]);

   set_sprite_data(0, NUM_TILES * 4, gameTiles); /*number of 16x16 tiles times 4 */

   /* Set up the pointer tile as sprite 0 */
   setup_sprite_16x16(0, POINTER_TILE);
   move_sprite_16x16(0, 0, 0); /* hide it for now */

   /* So, what we do is set up the pointer tile.
      We won't set up the animal tiles until we need to use them. */
   for(i = 0; i < NUM_TILES; i++)
   {
      spriteCount[i] = 0; /* 0 means that none are in the game (yet) */
   }

   pointerCol = 0;
   pointerRow = 0;

   /* move the pointer */
   move_sprite_16x16(0, pointerStartX+pointerCol*20,
                        pointerStartY+pointerRow*20);


	/* setup the digits */
   for(i = 0; i < MATCH_COUNT_DIGITS; i++)
   {
   	set_sprite_tile(MATCH_COUNT_SPRITE_START+i, FIRST_DIGIT_TILE*4); /*0 is the first one */

      /* all digits use the same palette */
   	set_sprite_prop(MATCH_COUNT_SPRITE_START+i, gameTilesCGB[FIRST_DIGIT_TILE]);

      move_sprite(MATCH_COUNT_SPRITE_START+i, MATCH_COUNT_START_X+(i*8), MATCH_COUNT_START_Y);
   }

	/* setup the digits */
   for(i = 0; i < GUESS_COUNT_DIGITS; i++)
   {
   	set_sprite_tile(GUESS_COUNT_SPRITE_START+i, FIRST_DIGIT_TILE*4); /*0 is the first one */

      /* all digits use the same palette */
   	set_sprite_prop(GUESS_COUNT_SPRITE_START+i, gameTilesCGB[FIRST_DIGIT_TILE]);
      move_sprite(GUESS_COUNT_SPRITE_START+i, GUESS_COUNT_START_X+(i*8), GUESS_COUNT_START_Y);
	}

	/* setup the digits */
   for(i = 0; i < SECOND_COUNT_DIGITS; i++)
   {
   	set_sprite_tile(SECOND_COUNT_SPRITE_START+i, FIRST_DIGIT_TILE*4); /*0 is the first one */

      /* all digits use the same palette */
   	set_sprite_prop(SECOND_COUNT_SPRITE_START+i, gameTilesCGB[FIRST_DIGIT_TILE]);
      move_sprite(SECOND_COUNT_SPRITE_START+i, SECOND_COUNT_START_X+(i*8), SECOND_COUNT_START_Y);
	}

   SHOW_SPRITES;
}

unsigned int movePointer()
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
   else if(!(joy & J_DOWN || joy & J_LEFT || joy & J_UP || joy & J_RIGHT))
      lastDir = 0;

   if(joy & J_A)
   {
   	if((grid[pointerRow][pointerCol] == FREE_TILE)
         || (spriteCount[grid[pointerRow][pointerCol]] == 0)
        )
      	return 0;  /* not a valid selection */

      return 1;  /* set pointerRow and pointerCol and return true */
   }

   if(joy & lastDir)
   	return 0;

   if(joy & J_DOWN)
   {
      pointerRow++;
      if(pointerRow >= NUM_ROWS)
         pointerRow = 0;
      doMove = 1;
      lastDir = J_DOWN;
   }
   else if(joy & J_UP)
   {
      pointerRow--;
      if(pointerRow < 0)
         pointerRow = NUM_ROWS-1;
      doMove = 1;
      lastDir = J_UP;
   }
   else if(joy & J_RIGHT)
   {
      pointerCol++;
      if(pointerCol >= NUM_COLS)
         pointerCol = 0;
      doMove = 1;
      lastDir = J_RIGHT;
   }
   else if(joy & J_LEFT)
   {
      pointerCol--;
      if(pointerCol < 0)
         pointerCol = NUM_COLS-1;
      doMove = 1;
      lastDir = J_LEFT;
   }

   if(doMove)
   {
		if(spriteCount[grid[pointerRow][pointerCol]] == 0)
		   setup_sprite_16x16(0, POINTER_NO_TILE);
		else
		   setup_sprite_16x16(0, POINTER_TILE);

      move_sprite_16x16(0, pointerStartX+pointerCol*20,
                        pointerStartY+pointerRow*20);
   }

   return 0; /* no final selection was made */
}

void setupBkg()
{
   HIDE_BKG;

   move_bkg(0,0);

   set_bkg_palette( 7, 1, &backPalCGB[28]);
   set_bkg_palette( 6, 1, &backPalCGB[24]);
   set_bkg_palette( 5, 1, &backPalCGB[20]);
   set_bkg_palette( 4, 1, &backPalCGB[16]);
   set_bkg_palette( 3, 1, &backPalCGB[12]);
   set_bkg_palette( 2, 1, &backPalCGB[8]);
   set_bkg_palette( 1, 1, &backPalCGB[4]);
   set_bkg_palette( 0, 1, &backPalCGB[0]);

   set_bkg_data(0, NUM_BKG_TILES, backTiles);

   VBK_REG = 1;
   set_bkg_tiles(0,0,backMapWidth,backMapHeight,backPal);

   VBK_REG = 0;
   set_bkg_tiles(0,0,backMapWidth,backMapHeight,backMap);


   SHOW_BKG;
}

void showTile(UBYTE spriteNum, int row, int col)
{
   if(grid[row][col] < FIRST_ANIMAL)
      return; /* not an animal tile */

   setup_sprite_16x16(spriteNum, grid[row][col]);
   move_sprite_16x16(spriteNum, gridStartX+col*20, gridStartY+row*20);
}

void hideTile(UBYTE spriteNum, int row, int col)
{
   if(grid[row][col] < FIRST_ANIMAL)
      return; /* not an animal tile */

   move_sprite_16x16(spriteNum, 0, 0);
}

void flyTiles(UBYTE spriteNum1, int row1, int col1, UBYTE spriteNum2, int row2, int col2)
{
   int done;
   int stopClock;
   int x1,y1,x2,y2;

   stopClock = clockOn;
   if(stopClock) /* if it was on */
      clockOn = 0; /* stop the clock while flying */

   done = 0;

   x1 = gridStartX+col1*20;
   y1 = gridStartY+row1*20;
   x2 = gridStartX+col2*20;
   y2 = gridStartY+row2*20;

   if((grid[row1][col1] < FIRST_ANIMAL) || (grid[row2][col2] < FIRST_ANIMAL))
      return; /* not an animal tile */

   while(!done)
   {
      done = 1; /* hope for the best */
      if(y1 > 0)
      {
      	done = 0; /* not the best :) */
         y1--;
         x1++;
      }

      if(y2 > 0)
      {
      	done = 0; /* not the best :) */
         y2--;
         x2++;
      }

      move_sprite_16x16(spriteNum1, x1, y1);
      move_sprite_16x16(spriteNum2, x2, y2);
      delay(15);
   }

   if(stopClock)
      clockOn = 1; /* re-start the clock */
}


UBYTE getRandAnimal()
{
	/* returns a random number that is between the first and last animal *_TILE defs */
   UBYTE retVal;

   retVal = rand(); /* rand returns [0,2^8-1] 0-255 */

   retVal = retVal % NUM_ANIMALS;

   retVal += FIRST_ANIMAL;

   if((retVal < FIRST_ANIMAL) || (retVal > LAST_ANIMAL))
   {
   	printf("\nError!!!\n");
      return FIRST_ANIMAL;
   }

   return retVal;
}

void randomizeGrid()
{
   int row, col;
   UBYTE animalNum;
   unsigned int loopCount;

   for(row = 0; row < NUM_ROWS; row++)
   {
      for(col = 0; col < NUM_COLS; col++)
      {
        	animalNum = getRandAnimal();
         loopCount = FIRST_ANIMAL;
         while(spriteCount[animalNum] >= 2)
         {
            if(loopCount > LAST_ANIMAL)
            	break;
				loopCount++;

           	animalNum++;
           	if(animalNum > LAST_ANIMAL)
            	animalNum = FIRST_ANIMAL;
         }

         if(spriteCount[animalNum] < 2)
         {
	         grid[row][col] = animalNum;
            spriteCount[animalNum]++;
         }
         else
         {
            /* the free-space will get here */
            if((row == NUM_ROWS-1) && (col == NUM_COLS-1))
            {
	            grid[row][col] = grid[NUM_ROWS/2][NUM_COLS/2];
               grid[NUM_ROWS/2][NUM_COLS/2] = FREE_TILE; /* free goes in middle */
               setup_sprite_16x16(3, FREE_TILE);
               showTile(3, NUM_ROWS/2, NUM_COLS/2);
            }
            else
            {
            	/*printf("ERROR in randomizeGrid\n");*/
               return;
            }
         }
      }
   }
}

void hideSprites()
{
	unsigned int i;

   /* only use 4 16x16 sprites   Pointer + 2 animals + FREE_TILE */
   for(i = 0; i < 4; i++)
   {
   	move_sprite_16x16(i, 0, 0);
   }

   /* Hide the X sprites */
   for(i = 0; i < X_COUNT; i++)
   {
   	move_sprite(X_SPRITE_START+i, 0, 0);
   }

   /* Hide the match count sprites */
   for(i = 0; i < MATCH_COUNT_DIGITS; i++)
   {
   	move_sprite(MATCH_COUNT_SPRITE_START+i, 0, 0);
   }

   for(i = 0; i < GUESS_COUNT_DIGITS; i++)
   {
   	move_sprite(GUESS_COUNT_SPRITE_START+i, 0, 0);
   }

   for(i = 0; i < SECOND_COUNT_DIGITS; i++)
   {
   	move_sprite(SECOND_COUNT_SPRITE_START+i, 0, 0);
   }

	HIDE_SPRITES;
}

void updateScore(unsigned int guessCount, unsigned int matchCount)
{
	/* This function will show the score on the screen. */
   int i;
   unsigned int tens, hundreds, ones;

   hundreds = matchCount / 100;
   tens = matchCount / 10;
   ones = matchCount;

   if(hundreds > 0)
   {
   	tens = tens - hundreds*100;
      ones = ones - hundreds*100;
   }

   if(tens > 0)
   {
   	ones = ones - tens*10;
   }

   for(i = 0; i < MATCH_COUNT_DIGITS; i++)
   {
   	switch(MATCH_COUNT_DIGITS-i)
      {
      	case 3: /* hundreds */
		   	set_sprite_tile(MATCH_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(hundreds*2)); /*0 is the first one */
            break;

      	case 2: /* tens */
		   	set_sprite_tile(MATCH_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(tens*2)); /*0 is the first one */
            break;

      	case 1: /* ones */
		   	set_sprite_tile(MATCH_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(ones*2)); /*0 is the first one */
            break;

         default:
         	break;
      }
   }


   hundreds = guessCount / 100;
   tens = guessCount / 10;
   ones = guessCount;

   if(hundreds > 0)
   {
   	tens = tens - hundreds*100;
      ones = ones - hundreds*100;
   }

   if(tens > 0)
   {
   	ones = ones - tens*10;
   }

   for(i = 0; i < GUESS_COUNT_DIGITS; i++)
   {
   	switch(GUESS_COUNT_DIGITS-i)
      {
      	case 3: /* hundreds */
		   	set_sprite_tile(GUESS_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(hundreds*2)); /*0 is the first one */
            break;

      	case 2: /* tens */
		   	set_sprite_tile(GUESS_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(tens*2)); /*0 is the first one */
            break;

      	case 1: /* ones */
		   	set_sprite_tile(GUESS_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(ones*2)); /*0 is the first one */
            break;

         default:
         	break;
      }
   }
}

void updateTime()
{
	/* This function will show the time on the screen. */
   int i;
   unsigned int tens, hundreds, ones;

   hundreds = seconds / 100;
   tens = seconds / 10;
   ones = seconds;

   if(hundreds > 0)
   {
   	tens = tens - hundreds*10;
      ones = ones - hundreds*100;
   }

   if(tens > 0)
   {
   	ones = ones - tens*10;
   }

   for(i = 0; i < SECOND_COUNT_DIGITS; i++)
   {
   	switch(SECOND_COUNT_DIGITS-i)
      {
      	case 3: /* hundreds */
		   	set_sprite_tile(SECOND_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(hundreds*2)); /*0 is the first one */
            break;

      	case 2: /* tens */
		   	set_sprite_tile(SECOND_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(tens*2)); /*0 is the first one */
            break;

      	case 1: /* ones */
		   	set_sprite_tile(SECOND_COUNT_SPRITE_START+i, (FIRST_DIGIT_TILE*4)+(ones*2)); /*0 is the first one */
            break;

         default:
         	break;
      }
   }
}

char showStats(unsigned int guessCount, unsigned int matchCount)
{
	int joy;
   int stopClock;
   unsigned int winPosX;

   stopClock = clockOn;
   if(stopClock)
      clockOn = 0; /* Stop the clock */

   waitpadup();

	/* This function will show the user some info and let them quit the game */
	SHOW_WIN;

   /* scroll win in from side */
   winPosX = 168;
   while(winPosX >= WIN_POS_X)
   {
   	move_win(winPosX, 0);
      delay(3);
      winPosX--;
   }



   do
   {
   	joy = joypad();
   } while(!joy);
   waitpadup();

   /* scroll win out to side */
   winPosX = WIN_POS_X;
   while(winPosX < 168)
   {
   	move_win(winPosX, 0);
      delay(3);
      winPosX++;
   }

   HIDE_WIN;
   move_win(0,0);

   if(stopClock)
      clockOn = 1; /* Re-Start the clock */

	if(joy & J_START)
   	return 1;

   return 0;
}

void showX(row, col)/*put an X over the removed tile*/
{
	if(numXs >= X_COUNT)
   	return;  //can't put any more

	/* setup the x */
  	set_sprite_tile(X_SPRITE_START+numXs, X_TILE*4);

	set_sprite_prop(X_SPRITE_START+numXs, gameTilesCGB[X_TILE]);

   move_sprite(X_SPRITE_START+numXs, (gridStartX+col*20)+4, gridStartY+row*20);

   numXs++;
}

void playGame(UBYTE firstRun)
{
   int quit, firstRow, firstCol, secondRow, secondCol, win;
   unsigned int guessCount; /* The number of times the player has flipped a pair of cards (made a guess) */
   unsigned int matchCount; /* The number of matches */

   musicClock = 0;
	SWITCH_ROM_MBC1(7);	// you can choose here the bank where you place your song data in the exemple.bat file
   initBkgMusic();
	SWITCH_ROM_MBC1(0);

   if(firstRun)
   	firstTimeRun = 1;
   else
   	firstTimeRun = 0;


   quit = 0;
   guessCount = 0;
   matchCount = 0;
   win = 0;
   numXs = 0;  /* no Xs are used, yet */

   DISPLAY_OFF;

   setupBkg();
   setupInfoWin();
   setupSprites();

   DISPLAY_ON;

   randomizeGrid();

   //sound_init();
/*	update_value(0,2,0);
	update_value(0,3,7);*/
   /*<VOLUME; 1-7 (7 is muted, although consumes power.
     Anything below 4 causes a 'buzz'>);*/

   setupIrqs();

   while(!quit && !win)
   {
    	//updateBkgMusic();  //Make sure we keep playin' the hits

      if(movePointer())
      {
         waitpadup();  /* wait for it to be released */

         clockOn = 1; /* start the clock */

         hideTile(1, firstRow, firstCol);
         hideTile(2, secondRow, secondCol);

         /* do something about the selection */
         firstRow = pointerRow;
         firstCol = pointerCol;
         showTile(1, firstRow, firstCol);

         /* wait for the 2nd selection */
         while(1)
         {
            //updateBkgMusic(); //Make sure we keep playin' the hits

         	if(movePointer()) /* made a selection */
            {
            	if((pointerRow != firstRow) || (pointerCol != firstCol))
               	break;
            }
         }
         waitpadup();  /* wait for it to be released */

         secondRow = pointerRow;
         secondCol = pointerCol;
         showTile(2, secondRow, secondCol);
         guessCount++;

         if(grid[firstRow][firstCol] == grid[secondRow][secondCol])
         {
         	matchCount++;

            /* "Ding" courtesy David Pfeffer */
			   /*play_note(1,F4);
				play_note(2,F4);
				delay(15);
			   play_note(1,F4);
				play_note(2,F4);*/

            spriteCount[grid[firstRow][firstCol]] = 0;  //done with that pair
			   setup_sprite_16x16(0, POINTER_NO_TILE);  //closed fist

            showX(firstRow, firstCol);
            showX(secondRow, secondCol);

            flyTiles(1, firstRow, firstCol, 2, secondRow, secondCol);

            if(matchCount >= NUM_ANIMALS)
            {
               win = 1;
               clockOn = 0; /* Stop the clock */
            }
         }

         updateScore(guessCount, matchCount); /* update the scores */
      }

      if(joypad() & J_START)
      {
      	waitpadup();

      	/* give a 2nd chance */
         if(!showStats(guessCount, matchCount)) /* showStats will return TRUE on J_START */
         	quit = 0;  /* whew, don't REALLY quit */
         else
      		quit = 1;
      }
   }//main while

   if(win)
   	showStats(guessCount, matchCount);

   hideSprites();
   //sound_off();

   //stop sound
   musicClock = 0;
	SWITCH_ROM_MBC1(7);	// you can choose here the bank where you place your song data in the exemple.bat file
   initBkgMusic();
	SWITCH_ROM_MBC1(0);

	set_interrupts(VBL_IFLAG);
   HIDE_WIN;
}
