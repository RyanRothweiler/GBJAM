////include a bunch of defines
//#include "stdio.h"
//#include "base.h" 
//#include "gba.h"
////#include "screenmode.h"
//
////include graphics
//#include "graphics\dude.c" //the player
//
////define some more things
//u16* FrontBuffer = (u16*)0x6000000;
//u16* BackBuffer = (u16*)0x600A000;
//USHORT* ScreenBuffer = (USHORT*)0x6000000;
//
//u16* videoBuffer = (u16*)0x6000000; // video memory
//u16* paletteMem = (u16*)0x5000000;	// Pal is 256 16 bit BGR 
//
//volatile u16* ScanlineCounter = (volatile u16*)0x4000006;
//
////plot a pixel
//void PlotPixel(int x, int y, unsigned short int c)
//{
//	videoBuffer[(y)* 120 + (x)] = (c);
//}
//
////declare methods
//void DrawDude(); 
//void Flip();
//void WaitForVblank();
//
////the main stuff
//int main(void)
//{
//	int loop;
//
//	for (loop = 0; loop < 256; loop++)	// put pal in memory
//		paletteMem[loop] = dudepal[loop];
//
//	SetMode(MODE4 | BG2_ENABLE);
//
//	while (1)
//	{
//		DrawDude();
//	}
//}
//
////draw the dude to the screen
//void DrawDude()
//{
//	int x, y;
//	for (y = 0; y < 160; y++)
//	{
//		for (x = 0; x < 120; x++)
//		{
//			PlotPixel(x, y, dudedata[y*120+x]);
//		}
//	}
//}
//
////flips the two buffers
//void Flip(void)			// flips between the back/front buffer
//{
//	if (REG_DISPCNT & BACKBUFFER) //back buffer is the current buffer so we need to switch it to the font buffer
//	{
//		REG_DISPCNT &= ~BACKBUFFER; //flip active buffer to front buffer by clearing back buffer bit
//		videoBuffer = BackBuffer; //now we point our drawing buffer to the back buffer
//	}
//	else //front buffer is active so switch it to backbuffer
//	{
//		REG_DISPCNT |= BACKBUFFER; //flip active buffer to back buffer by setting back buffer bit
//		videoBuffer = FrontBuffer; //now we point our drawing buffer to the front buffer
//	}
//}
//
////wait for the scanline to finish
//void WaitForVblank(void)	// waits for the drawer to get to end before flip
//{
//	while (*ScanlineCounter < 160) {	// do nothing
//	}//now we are in the vblank period
//}





/* hello.c - Gameboy Advance Tutorial - Loirak Development */
#define RGB16(r,g,b)  ((r)+(g<<5)+(b<<10)) 
#include "stdio.h"
#include "gb.h"

int main()
{
	char x, y;
	unsigned short* Screen = (unsigned short*)0x6000000;
	*(unsigned long*)0x4000000 = 0x403; // mode3, bg2 on 

	printf("derp");

	// clear screen, and draw a blue back ground
	for (x = 0; x<240; x++)   //loop through all x
	{
		for (y = 0; y<160; y++)  //loop through all y
		{
			Screen[x + y * 240] = RGB16(0, 0, 31);
		}
	}

	// draw a white HI on the background
	for (x = 20; x <= 60; x += 15)
	for (y = 30; y<50; y++)
		Screen[x + y * 240] = RGB16(31, 31, 31);
	for (x = 20; x < 35; x++)
		Screen[x + 40 * 240] = RGB16(31, 31, 31);


	while (1)
	{
	}	//loop forever
}