//----------------------------------------Includes
#include "gun.c"



//----------------------------------------Variables
int P_PosX = 40; //players position in x screen space
int P_PosY = 40; //players position in y screen space
int P_Direction = 0; // clockwise starting up with 1
int P_MovementSpeed = 1; //the number of pixels the player moves each time she is moved
int P_Strafing = 0; //if the character is strafing or not
int P_StrafeToggle = 1; //1 for can toggle 0 for can't

int P_FrameIndex = 0; //the tile number

int joykey = 0; //holds which buttons are being pressed
int P_Num = 0; //general number for player





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
void PlayerMoveUp(int SpriteNum, int changeDir)
{
	if (!CheckCollision(P_PosX, P_PosY - P_MovementSpeed, 0, 0)) //doesn't collide
	{
		P_PosY -= P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		if (changeDir)
		{
			P_FrameIndex = 0;
			P_Direction = 1;
		}
	}
}

//move the player down
void PlayerMoveDown(int SpriteNum, int changeDir)
{
	if (!CheckCollision(P_PosX, P_PosY + P_MovementSpeed, 1, 0)) //doesn't collide
	{
		P_PosY += P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		if (changeDir)
		{
			P_FrameIndex = 2;
			P_Direction = 3;
		}
	}
}

//move the player right
void PlayerMoveRight(int SpriteNum, int changeDir)
{
	if (!CheckCollision(P_PosX + P_MovementSpeed, P_PosY, 0, 1)) //doesn't collide
	{
		P_PosX += P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		if (changeDir)
		{
			P_FrameIndex = 1;
			P_Direction = 2;
		}
	}
}

//move the player left
void PlayerMoveLeft(int SpriteNum, int changeDir)
{
	if (!CheckCollision(P_PosX - P_MovementSpeed, P_PosY, 0, 0)) //doesn't collide
	{
		P_PosX -= P_MovementSpeed;
		move_sprite(SpriteNum, P_PosX, P_PosY);
		if (changeDir)
		{
			P_FrameIndex = 3;
			P_Direction = 4;
		}
	}
}

//slides the player back (back being relative to whatever her current direction is)
void PlayerSlideBack(int SpriteNum)
{
	if (P_Direction == 1)
	{
		PlayerMoveDown(SpriteNum, 0);
	}
	if (P_Direction == 2)
	{
		PlayerMoveLeft(SpriteNum, 0);
	}
	if (P_Direction == 3)
	{
		PlayerMoveUp(SpriteNum, 0);
	}
	if (P_Direction == 4)
	{
		PlayerMoveRight(SpriteNum, 0);
	}
}

//slides the player forward (forward being relative to whatever her current direction is)
void PlayerSlideForward(int SpriteNum)
{
	if (P_Direction == 1)
	{
		PlayerMoveUp(SpriteNum, 0);
	}
	if (P_Direction == 2)
	{
		PlayerMoveRight(SpriteNum, 0);
	}
	if (P_Direction == 3)
	{
		PlayerMoveDown(SpriteNum, 0);
	}
	if (P_Direction == 4)
	{
		PlayerMoveLeft(SpriteNum, 0);
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
		if (P_Strafing)
		{
			PlayerMoveUp(SpriteNum, 0);
		}
		else
		{
			PlayerMoveUp(SpriteNum, 1);
		}
	}
	if (joykey == 8) //down
	{
		if (P_Strafing)
		{
			PlayerMoveDown(SpriteNum, 0);
		}
		else
		{
			PlayerMoveDown(SpriteNum, 1);
		}
	}
	if (joykey == 2) //left
	{
		if (P_Strafing)
		{
			PlayerMoveLeft(SpriteNum, 0);
		}
		else
		{
			PlayerMoveLeft(SpriteNum, 1);
		}
	}
	if (joykey == 1) //right
	{
		if (P_Strafing)
		{
			PlayerMoveRight(SpriteNum, 0);
		}
		else
		{
			PlayerMoveRight(SpriteNum, 1);
		}
	}
	if (joykey == 5) //northeast
	{
		if (P_Strafing)
		{
			PlayerMoveUp(SpriteNum, 0);
			PlayerMoveRight(SpriteNum, 0);
		}
		else
		{
			PlayerMoveUp(SpriteNum, 1);
			PlayerMoveRight(SpriteNum, 1);
		}
	}
	if (joykey == 9) //southeast
	{
		if (P_Strafing)
		{
			PlayerMoveDown(SpriteNum, 0);
			PlayerMoveRight(SpriteNum, 0);
		}
		else
		{
			PlayerMoveDown(SpriteNum, 1);
			PlayerMoveRight(SpriteNum, 1);
		}
	}
	if (joykey == 10) //southwest
	{
		if (P_Strafing)
		{
			PlayerMoveDown(SpriteNum, 0);
			PlayerMoveLeft(SpriteNum, 0);
		}
		else
		{
			PlayerMoveDown(SpriteNum, 1);
			PlayerMoveLeft(SpriteNum, 1);
		}
	}
	if (joykey == 6) //northwest
	{
		if (P_Strafing)
		{
			PlayerMoveUp(SpriteNum, 0);
			PlayerMoveLeft(SpriteNum, 0);
		}
		else
		{
			PlayerMoveUp(SpriteNum, 1);
			PlayerMoveLeft(SpriteNum, 1);
		}
	}

	//bullets and movement
	if (joykey == 16) //A only
	{
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 20) //A and up
	{
		if (P_Strafing)
		{
			PlayerMoveUp(SpriteNum, 0);
		}
		else
		{
			PlayerMoveUp(SpriteNum, 1);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 24) //A and down
	{
		if (P_Strafing)
		{
			PlayerMoveDown(SpriteNum, 0);
		}
		else
		{
			PlayerMoveDown(SpriteNum, 1);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 17) //A and right
	{
		if (P_Strafing)
		{
			PlayerMoveRight(SpriteNum, 0);
		}
		else
		{
			PlayerMoveRight(SpriteNum, 1);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 18) //A and left
	{
		if (P_Strafing)
		{
			PlayerMoveLeft(SpriteNum, 0);
		}
		else
		{
			PlayerMoveLeft(SpriteNum, 1);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}

	//strafing
	if (joykey == 32) //B only
	{
		if (P_StrafeToggle)
		{
			if (P_Strafing)
			{
				P_Strafing = 0;
			}
			else
			{
				P_Strafing = 1;
			}
			P_StrafeToggle = 0;
		}
	}
	if (joykey == 36) //up and B
	{
		if (P_StrafeToggle)
		{
			if (P_Strafing)
			{
				P_Strafing = 0;
			}
			else
			{
				P_Strafing = 1;
			}
			P_StrafeToggle = 0;
		}
		PlayerMoveUp(SpriteNum, 0);
	}
	if (joykey == 40) //down and B
	{
		if (P_StrafeToggle)
		{
			if (P_Strafing)
			{
				P_Strafing = 0;
			}
			else
			{
				P_Strafing = 1;
			}
			P_StrafeToggle = 0;
		}
		PlayerMoveDown(SpriteNum, 0);
	}
	if (joykey == 33) //right and B
	{
		if (P_StrafeToggle)
		{
			if (P_Strafing)
			{
				P_Strafing = 0;
			}
			else
			{
				P_Strafing = 1;
			}
			P_StrafeToggle = 0;
		}
		PlayerMoveRight(SpriteNum, 0);
	}
	if (joykey == 34) //left and B
	{
		if (P_StrafeToggle)
		{
			if (P_Strafing)
			{
				P_Strafing = 0;
			}
			else
			{
				P_Strafing = 1;
			}
			P_StrafeToggle = 0;
		}
		PlayerMoveLeft(SpriteNum, 0);
	}
	//reset strafe toggle
	if ((joykey != 32) && (joykey != 36) && (joykey != 40) && (joykey != 3) && (joykey != 34))
	{
		P_StrafeToggle = 1;
	}
	return 0;
}




//----------------------------------------Sprite Methods
//updates the player stuff (also updates bullet stuff)
int PlayerUpdate(int SpriteNum) //0 - nothing happened, 1 - bullet died
{
	//set the sprite
	set_sprite_tile(SpriteNum, P_FrameIndex);

	//update gun stuff
	GunUpdate();

	//Update bullet stuff
	return BulletsUpdate();
}

//loads the player sprites (this doesn't increment sprite num since it starts at 0
void PlayerLoad(int SpriteNum)
{
	//load sprite data
	set_sprite_tile(0, P_FrameIndex);

	PlayerMoveUp(SpriteNum, 1);
}