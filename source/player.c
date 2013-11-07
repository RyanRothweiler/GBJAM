//----------------------------------------Includes
#include "gun.c"



//----------------------------------------Variables
int P_PosX = 80; //players position in x screen space
int P_PosY = 72; //players position in y screen space
int P_Direction = 0; // clockwise starting up with 1
int P_MovementSpeed = 1; //the number of pixels the player moves each time she is moved
int P_Strafing = 0; //if the character is strafing or not
int P_StrafeToggle = 1; //1 for can toggle 0 for can't

int P_FrameIndex = 0; //the tile number

int joykey = 0; //holds which buttons are being pressed
int P_Num = 0; //general number for player




//----------------------------------------Movement Methods
//move the player up
void PlayerMoveUp(int changeDir, int SpriteNum)
{
	if (!CheckCollision(P_PosX, P_PosY - P_MovementSpeed, 0, 0)) //doesn't collide
	{
		BackgroundMoveDown(P_MovementSpeed, SpriteNum);
		if (changeDir)
		{
			P_FrameIndex = 0;
			P_Direction = 1;
		}
	}
}

//move the player down
void PlayerMoveDown(int changeDir, int SpriteNum)
{
	if (!CheckCollision(P_PosX, P_PosY + 1, 1, 0)) //doesn't collide
	{
		BackgroundMoveUp(P_MovementSpeed, SpriteNum);
		if (changeDir)
		{
			P_FrameIndex = 2;
			P_Direction = 3;
		}
	}
}

//move the player right
void PlayerMoveRight(int changeDir, int SpriteNum)
{
	//for some reason putting P_MovementSpeed in for 1 has problems. idk why
	if (!CheckCollision(P_PosX + 1, P_PosY, 0, 1)) //doesn't collide
	{
		BackgroundMoveLeft(P_MovementSpeed, SpriteNum);
		if (changeDir)
		{
			P_FrameIndex = 1;
			P_Direction = 2;
		}
	}
}

//move the player left
void PlayerMoveLeft(int changeDir, int SpriteNum)
{
	if (!CheckCollision(P_PosX - P_MovementSpeed, P_PosY, 0, 0)) //doesn't collide
	{
		BackgroundMoveRight(P_MovementSpeed, SpriteNum);
		if (changeDir)
		{
			P_FrameIndex = 3;
			P_Direction = 4;
		}
	}
}

//slides the player back (back being relative to whatever her current direction is)
void PlayerSlideBack()
{
	if (P_Direction == 1)
	{
		PlayerMoveDown(0);
	}
	if (P_Direction == 2)
	{
		PlayerMoveLeft(0);
	}
	if (P_Direction == 3)
	{
		PlayerMoveUp(0);
	}
	if (P_Direction == 4)
	{
		PlayerMoveRight(0);
	}
}

//slides the player forward (forward being relative to whatever her current direction is)
void PlayerSlideForward()
{
	if (P_Direction == 1)
	{
		PlayerMoveUp(0);
	}
	if (P_Direction == 2)
	{
		PlayerMoveRight(0);
	}
	if (P_Direction == 3)
	{
		PlayerMoveDown(0);
	}
	if (P_Direction == 4)
	{
		PlayerMoveLeft(0);
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
			PlayerMoveUp(0, SpriteNum);
		}
		else
		{
			PlayerMoveUp(1, SpriteNum);
		}
	}
	if (joykey == 8) //down
	{
		if (P_Strafing)
		{
			PlayerMoveDown(0, SpriteNum);
		}
		else
		{
			PlayerMoveDown(1, SpriteNum);
		}
	}
	if (joykey == 2) //left
	{
		if (P_Strafing)
		{
			PlayerMoveLeft(0, SpriteNum);
		}
		else
		{
			PlayerMoveLeft(1, SpriteNum);
		}
	}
	if (joykey == 1) //right
	{
		if (P_Strafing)
		{
			PlayerMoveRight(0, SpriteNum);
		}
		else
		{
			PlayerMoveRight(1, SpriteNum);
		}
	}
	if (joykey == 5) //northeast
	{
		if (P_Strafing)
		{
			PlayerMoveUp(0, SpriteNum);
			PlayerMoveRight(0, SpriteNum);
		}
		else
		{
			PlayerMoveUp(1, SpriteNum);
			PlayerMoveRight(1, SpriteNum);
		}
	}
	if (joykey == 9) //southeast
	{
		if (P_Strafing)
		{
			PlayerMoveDown(0, SpriteNum);
			PlayerMoveRight(0, SpriteNum);
		}
		else
		{
			PlayerMoveDown(1, SpriteNum);
			PlayerMoveRight(1, SpriteNum);
		}
	}
	if (joykey == 10) //southwest
	{
		if (P_Strafing)
		{
			PlayerMoveDown(0, SpriteNum);
			PlayerMoveLeft(0, SpriteNum);
		}
		else
		{
			PlayerMoveDown(1, SpriteNum);
			PlayerMoveLeft(1, SpriteNum);
		}
	}
	if (joykey == 6) //northwest
	{
		if (P_Strafing)
		{
			PlayerMoveUp(0, SpriteNum);
			PlayerMoveLeft(0, SpriteNum);
		}
		else
		{
			PlayerMoveUp(1, SpriteNum);
			PlayerMoveLeft(1, SpriteNum);
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
			PlayerMoveUp(0, SpriteNum);
		}
		else
		{
			PlayerMoveUp(1, SpriteNum);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 24) //A and down
	{
		if (P_Strafing)
		{
			PlayerMoveDown(0, SpriteNum);
		}
		else
		{
			PlayerMoveDown(1, SpriteNum);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 17) //A and right
	{
		if (P_Strafing)
		{
			PlayerMoveRight(0, SpriteNum);
		}
		else
		{
			PlayerMoveRight(1, SpriteNum);
		}
		return GunFire(P_PosX, P_PosY, P_Direction);
	}
	if (joykey == 18) //A and left
	{
		if (P_Strafing)
		{
			PlayerMoveLeft(0, SpriteNum);
		}
		else
		{
			PlayerMoveLeft(1, SpriteNum);
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
		PlayerMoveUp(0);
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
		PlayerMoveDown(0);
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
		PlayerMoveRight(0);
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
		PlayerMoveLeft(0);
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
	move_sprite(SpriteNum, 0, 0);
	move_sprite(SpriteNum, P_PosX, P_PosY);

	//update gun stuff
	GunUpdate();

	//Update bullet stuff
	return BulletsUpdate();
}

//loads the player sprites (this doesn't increment sprite num since it starts at 0
void PlayerLoad()
{
	//load sprite data
	set_sprite_tile(0, P_FrameIndex);

	move_sprite(0, P_PosX, P_PosY);
}