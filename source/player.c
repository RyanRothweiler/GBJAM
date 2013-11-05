//----------------------------------------Includes
//player graphics
#include "graphics\player\player.h"
#include "graphics\player\player.c"

#include "bullets.c"



//----------------------------------------Variables
int P_PosX = 40; //players position in x screen space
int P_PosY = 40; //players position in y screen space
int P_Direction = 0; // clockwise starting up with 1
int P_MovementSpeed = 1; //the number of pixels the player moves each time she is moved

//int P_FrameTotal = 6; //the total number of frames in the player animation
int P_FrameIndex = 0; //the tile number
//int P_Animating = 0; //if the player is animating //1true 0false
//int P_Looping = 1; //if the animation is looping
//int P_PingPong = 0; //if the animation is pingponging
//int P_PingPongReturning = 0; //if the animation is pingponging and is pinging back, meaning the frame index is decreasing

int joykey = 0; //holds which buttons are being pressed




//----------------------------------------Get Methods
//returns playes y position in pixels
int PlayerPosX()
{
	return P_PosX;
}

//returns players y position in pixels
int PlayerPosY()
{
	return P_PosY;
}




//----------------------------------------Movement Methods
//move the player up
void PlayerMoveUp(int SpriteNum)
{
	if (!CheckCollision(P_PosX, P_PosY - P_MovementSpeed, 0, 0)) //doesn't collide
	{
		P_PosY -= P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		P_FrameIndex = 0;
		P_Direction = 1;
	}
}

//move the player down
void PlayerMoveDown(int SpriteNum)
{
	if (!CheckCollision(P_PosX, P_PosY + P_MovementSpeed, 1, 0)) //doesn't collide
	{
		P_PosY += P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		P_FrameIndex = 2;
		P_Direction = 3;
	}
}

//move the player right
void PlayerMoveRight(int SpriteNum)
{
	if (!CheckCollision(P_PosX + P_MovementSpeed, P_PosY, 0, 1)) //doesn't collide
	{
		P_PosX += P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		P_FrameIndex = 1;
		P_Direction = 2;
	}
}

//move the player left
void PlayerMoveLeft(int SpriteNum)
{
	if (!CheckCollision(P_PosX - P_MovementSpeed, P_PosY, 0, 0)) //doesn't collide
	{
		P_PosX -= P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		P_FrameIndex = 3;
		P_Direction = 4;
	}
}

//checks the controls and how the affect the player
int PlayerCheckControls(int SpriteNum) //returns. 0 - nothing, 1 - a bullet was instantiated
{
	joykey = joypad(); //get joypad
	//printf("%d", joykey);
	//check movement
	if (joykey == 4) //up
	{
		PlayerMoveUp(SpriteNum);
	}
	if (joykey == 8) //down
	{
		PlayerMoveDown(SpriteNum);
	}
	if (joykey == 2) //left
	{
		PlayerMoveLeft(SpriteNum);
	}
	if (joykey == 1) //right
	{
		PlayerMoveRight(SpriteNum);
	}
	if (joykey == 5) //northeast
	{
		PlayerMoveUp(SpriteNum);
		PlayerMoveRight(SpriteNum);
	}
	if (joykey == 9) //southeast
	{
		PlayerMoveDown(SpriteNum);
		PlayerMoveRight(SpriteNum);
	}
	if (joykey == 10) //southwest
	{
		PlayerMoveDown(SpriteNum);
		PlayerMoveLeft(SpriteNum);
	}
	if (joykey == 6) //northwest
	{
		PlayerMoveUp(SpriteNum);
		PlayerMoveLeft(SpriteNum);
	}

	//bullets and movement
	if (joykey == 16) //A only
	{
		BulletsAdd(P_PosX, P_PosY, P_Direction);
		return 1;
	}
	if (joykey == 40) //A and up
	{
		PlayerMoveUp(SpriteNum);
	}
	if (joykey == 42) //A and down
	{
		PlayerMoveDown(SpriteNum);
	}
	if (joykey == 17) //A and right
	{
		PlayerMoveRight(SpriteNum);
	}
	if (joykey == 18) //A only left
	{
		PlayerMoveLeft(SpriteNum);
	}
	return 0;
}




//----------------------------------------Sprite Methods
//updates the player stuff (also updates bullet stuff)
void PlayerUpdate(int SpriteNum)
{
	//set the sprite
	set_sprite_tile(SpriteNum, P_FrameIndex);

	//Update bullet stuff
	BulletsUpdate(SpriteNum);
}

//loads the player sprites (this doesn't increment sprite num since it starts at 0
void PlayerLoad(int SpriteNum)
{
	//load sprite data
	set_sprite_data(0, 8, PlayerTiles);
	set_sprite_tile(0, P_FrameIndex);

	PlayerMoveUp(SpriteNum);
}