//----------------------------------------Includes
//player graphics
#include "graphics\player\player.h"
#include "graphics\player\player.c"




//----------------------------------------Variables
int P_PosX = 20; //players position in x screen space
int P_PosY = 60; //players position in y screen space

int P_MovementSpeed = 1; //the number of pixels the player moves each time she is moved

int P_FrameTotal = 6; //the total number of frames in the player animation
int P_FrameIndex = 0; //the tile number
int P_Animating = 1; //if the player is animating //1true 0false
int P_Looping = 1; //if the animation is looping
int P_PingPong = 0; //if the animation is pingponging
int P_PingPongReturning = 0; //if the animation is pingponging and is pinging back, meaning the frame index is decreasing

int joykey = 0; //holds which buttons are being pressed




//----------------------------------------Movement Methods
//moves the player to the given position
void PlayerMove(int x, int y)
{
	P_PosX = x;
	P_PosY = y;
	move_sprite(0, P_PosX, P_PosY);
}

//move the player up one pixel
void PlayerMoveUp()
{
	P_PosY -= P_MovementSpeed;
	move_sprite(0, P_PosX, P_PosY);
}

//move the player down one pixel
void PlayerMoveDown()
{
	P_PosY += P_MovementSpeed;
	move_sprite(0, P_PosX, P_PosY);
}

//move the player right one pixel
void PlayerMoveRight()
{
	P_PosX += P_MovementSpeed;
	move_sprite(0, P_PosX, P_PosY);
}

//move the player left one pixel
void PlayerMoveLeft()
{
	P_PosX -= P_MovementSpeed;
	move_sprite(0, P_PosX, P_PosY);
}

//checks the controls and how the affect the player
void PlayerCheckControls()
{
	joykey = joypad(); //get joypad
	if (joykey == J_UP) //up
	{
		PlayerMoveUp();
	}
	if (joykey == J_DOWN) //down
	{
		PlayerMoveDown();
	}
	if (joykey == J_LEFT) //left
	{
		PlayerMoveLeft();
	}
	if (joykey == J_RIGHT) //right
	{
		PlayerMoveRight();
	}
}




//----------------------------------------Sprite Methods
//updates the player tiles
void PlayerUpdate()
{
	//do animation stuff
	if (P_Animating) //if animating
	{
		//if (P_PingPongReturning)
		P_FrameIndex++;
		if (P_FrameIndex == (P_FrameTotal)) //and at the end of the animation
		{
			if (P_Looping) //and looping
			{
				P_FrameIndex = 0;
			}

			if (P_PingPong)
			{

			}
		}
	}

	//set the sprite
	set_sprite_tile(0, P_FrameIndex);
}

//loads the player sprites
void PlayerLoad()
{
	set_sprite_data(0, 8, PlayerTiles);
	set_sprite_tile(0, P_FrameIndex);
}