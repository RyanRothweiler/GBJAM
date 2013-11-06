//----------------------------------------Includes




//----------------------------------------Variables
int B_BulletNum = 0; //the number of bullets on screen
int B_BulletSpeed = 10; //the number of pixels to move the bullet each frame
int B_Num = 0; //a basic number

//bullet sprite number id's. These change as bullets are create and destroyed, but they always represent the bullets sprite number
int B1_SpriteID = 0;
int B2_SpriteID = 0;
int B3_SpriteID = 0;
int B4_SpriteID = 0;

//bullet1 info
int B1_Using = 0;
int B1_PosX = 0;
int B1_PosY = 0;
int B1_FrameIndex = 5;
int B1_Animating = 0; 
int B1_Dir = 0; //1 - north, 2 - east, 3 - south, 4 - west
int B1_Dead = 0; //if this bulleth as hit something and shold be playing the death animation

//bullet2 info
int B2_Using = 0;
int B2_PosX = 0;
int B2_PosY = 0;
int B2_FrameIndex = 5;
int B2_Animating = 0;
int B2_Dir = 0; //1 - north, 2 - east, 3 - south, 4 - west
int B2_Dead = 0; //if this bulleth as hit something and shold be playing the death animation

//bullet3 info
int B3_Using = 0;
int B3_PosX = 0;
int B3_PosY = 0;
int B3_FrameIndex = 5;
int B3_Animating = 0;
int B3_Dir = 0; //1 - north, 2 - east, 3 - south, 4 - west
int B3_Dead = 0; //if this bulleth as hit something and shold be playing the death animation

//bullet3 info
int B4_Using = 0;
int B4_PosX = 0;
int B4_PosY = 0;
int B4_FrameIndex = 5;
int B4_Animating = 0;
int B4_Dir = 0; //1 - north, 2 - east, 3 - south, 4 - west
int B4_Dead = 0; //if this bulleth as hit something and shold be playing the death animation




//----------------------------------------Methods
//this adds one to every sprite ID, thus allowing a new sprite to be added. it also set sprites for each bullet accoringly
void BulletSlideSpriteIDsUp()
{
	B1_SpriteID++;
	if (B1_Using)
	{
		set_sprite_tile(B1_SpriteID, B1_FrameIndex);
	}

	B2_SpriteID++;
	if (B2_Using)
	{
		set_sprite_tile(B2_SpriteID, B2_FrameIndex);
	}

	B3_SpriteID++;
	if (B3_Using)
	{
		set_sprite_tile(B3_SpriteID, B3_FrameIndex);
	}

	B4_SpriteID++;
	if (B4_Using)
	{
		set_sprite_tile(B4_SpriteID, B4_FrameIndex);
	}
}

//this subtractws one from every sprite whos ID is larger than the given number, thus removing a sprite
void BulletSlideSpriteIDsDown(int num)
{
	if (B1_SpriteID > num)
	{
		B1_SpriteID--;
	}
	if (B2_SpriteID > num)
	{
		B2_SpriteID--;
	}
	if (B3_SpriteID > num)
	{
		B3_SpriteID--;
	}
	if (B4_SpriteID > num)
	{
		B4_SpriteID--;
	}
}

//go through and update all the bullets positions and sprites
int BulletsUpdate() //0 - nothing, 1 - bullet died
{
	if (B1_Using)
	{
		if (!B1_Dead)
		{
			//moving up
			if (B1_Dir == 1)
			{
				if (!CheckCollision(B1_PosX, B1_PosY - B_BulletSpeed, 1, 0) && !CheckCollision(B1_PosX, B1_PosY - (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B1_PosX, B1_PosY - (B_BulletSpeed / 3), 1, 0))
				{
					B1_PosY -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B1_PosY % 8;
					B1_PosY = (B1_PosY - (8 - B_Num)) + 8;

					B1_Dead = 1;
				}
			}
			//moving down
			if (B1_Dir == 3)
			{
				if (!CheckCollision(B1_PosX, B1_PosY + B_BulletSpeed, 1, 0) && !CheckCollision(B1_PosX, B1_PosY + (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B1_PosX, B1_PosY + (B_BulletSpeed / 3), 1, 0))
				{
					B1_PosY += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B1_PosY % 8;
					B1_PosY = (B1_PosY + (8 - B_Num));

					B1_Dead = 1;
				}
			}
			//moving right
			if (B1_Dir == 2)
			{
				if (!CheckCollision(B1_PosX + B_BulletSpeed, B1_PosY, 1, 0) && !CheckCollision(B1_PosX + (B_BulletSpeed / 2), B1_PosY, 1, 0) && !CheckCollision(B1_PosX + (B_BulletSpeed / 3), B1_PosY, 1, 0))
				{
					B1_PosX += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B1_PosX % 8;
					B1_PosX = (B1_PosX + (8 - B_Num));

					B1_Dead = 1;
				}
			}
			//moving left
			if (B1_Dir == 4)
			{
				if (!CheckCollision(B1_PosX - B_BulletSpeed, B1_PosY, 1, 0) && !CheckCollision(B1_PosX - (B_BulletSpeed / 2), B1_PosY, 1, 0) && !CheckCollision(B1_PosX - (B_BulletSpeed / 3), B1_PosY, 1, 0))
				{
					B1_PosX -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B1_PosX % 8;
					B1_PosX = (B1_PosX - (8 - B_Num) + 8);

					B1_Dead = 1;
				}
			}
			move_sprite(B1_SpriteID, B1_PosX, B1_PosY);
		}
		else //else this bullet is dead and should be playing the death animation
		{
			if (B1_Dir == 1) //up
			{
				if (B1_FrameIndex < (5 + 5)) //still alive
				{
					B1_FrameIndex++;
					set_sprite_tile(B1_SpriteID, B1_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B1_SpriteID);
					B1_Using = 0;
					return 1;
				}
			}
			if (B1_Dir == 2) //right
			{
				if (B1_FrameIndex < (11 + 5)) //still alive
				{
					B1_FrameIndex++;
					set_sprite_tile(B1_SpriteID, B1_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B1_SpriteID);
					B1_Using = 0;
					return 1;
				}
			}
			if (B1_Dir == 3) //down
			{
				if (B1_FrameIndex < (17 + 5)) //still alive
				{
					B1_FrameIndex++;
					set_sprite_tile(B1_SpriteID, B1_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B1_SpriteID);
					B1_Using = 0;
					return 1;
				}
			}
			if (B1_Dir == 4) //left
			{
				if (B1_FrameIndex < (23 + 5)) //still alive
				{
					B1_FrameIndex++;
					set_sprite_tile(B1_SpriteID, B1_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B1_SpriteID);
					B1_Using = 0;
					return 1;
				}
			}
		}
	}

	if (B2_Using)
	{
		if (!B2_Dead)
		{
			//moving up
			if (B2_Dir == 1)
			{
				if (!CheckCollision(B2_PosX, B2_PosY - B_BulletSpeed, 1, 0) && !CheckCollision(B2_PosX, B2_PosY - (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B2_PosX, B2_PosY - (B_BulletSpeed / 3), 1, 0))
				{
					B2_PosY -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B2_PosY % 8;
					B2_PosY = (B2_PosY - (8 - B_Num)) + 8;

					B2_Dead = 1;
				}
			}
			//moving down
			if (B2_Dir == 3)
			{
				if (!CheckCollision(B2_PosX, B2_PosY + B_BulletSpeed, 1, 0) && !CheckCollision(B2_PosX, B2_PosY + (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B2_PosX, B2_PosY + (B_BulletSpeed / 3), 1, 0))
				{
					B2_PosY += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B2_PosY % 8;
					B2_PosY = (B2_PosY + (8 - B_Num));

					B2_Dead = 1;
				}
			}
			//moving right
			if (B2_Dir == 2)
			{
				if (!CheckCollision(B2_PosX + B_BulletSpeed, B2_PosY, 1, 0) && !CheckCollision(B2_PosX + (B_BulletSpeed / 2), B2_PosY, 1, 0) && !CheckCollision(B2_PosX + (B_BulletSpeed / 3), B2_PosY, 1, 0))
				{
					B2_PosX += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B2_PosX % 8;
					B2_PosX = (B2_PosX + (8 - B_Num));

					B2_Dead = 1;
				}
			}
			//moving left
			if (B2_Dir == 4)
			{
				if (!CheckCollision(B2_PosX - B_BulletSpeed, B2_PosY, 1, 0) && !CheckCollision(B2_PosX - (B_BulletSpeed / 2), B2_PosY, 1, 0) && !CheckCollision(B2_PosX - (B_BulletSpeed / 3), B2_PosY, 1, 0))
				{
					B2_PosX -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B2_PosX % 8;
					B2_PosX = (B2_PosX - (8 - B_Num) + 8);

					B2_Dead = 1;
				}
			}
			move_sprite(B2_SpriteID, B2_PosX, B2_PosY);
		}
		else //else this bullet is dead and should be playing the death animation
		{
			if (B2_Dir == 1) //up
			{
				if (B2_FrameIndex < (5 + 5)) //still alive
				{
					B2_FrameIndex++;
					set_sprite_tile(B2_SpriteID, B2_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B2_SpriteID);
					B2_Using = 0;
					return 1;
				}
			}
			if (B2_Dir == 2) //right
			{
				if (B2_FrameIndex < (11 + 5)) //still alive
				{
					B2_FrameIndex++;
					set_sprite_tile(B2_SpriteID, B2_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B2_SpriteID);
					B2_Using = 0;
					return 1;
				}
			}
			if (B2_Dir == 3) //down
			{
				if (B2_FrameIndex < (17 + 5)) //still alive
				{
					B2_FrameIndex++;
					set_sprite_tile(B2_SpriteID, B2_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B2_SpriteID);
					B2_Using = 0;
					return 1;
				}
			}
			if (B2_Dir == 4) //left
			{
				if (B2_FrameIndex < (23 + 5)) //still alive
				{
					B2_FrameIndex++;
					set_sprite_tile(B2_SpriteID, B2_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B2_SpriteID);
					B2_Using = 0;
					return 1;
				}
			}
		}
	}

	if (B3_Using)
	{
		if (!B3_Dead)
		{
			//moving up
			if (B3_Dir == 1)
			{
				if (!CheckCollision(B3_PosX, B3_PosY - B_BulletSpeed, 1, 0) && !CheckCollision(B3_PosX, B3_PosY - (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B3_PosX, B3_PosY - (B_BulletSpeed / 3), 1, 0))
				{
					B3_PosY -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B3_PosY % 8;
					B3_PosY = (B3_PosY - (8 - B_Num)) + 8;

					B3_Dead = 1;
				}
			}
			//moving down
			if (B3_Dir == 3)
			{
				if (!CheckCollision(B3_PosX, B3_PosY + B_BulletSpeed, 1, 0) && !CheckCollision(B3_PosX, B3_PosY + (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B3_PosX, B3_PosY + (B_BulletSpeed / 3), 1, 0))
				{
					B3_PosY += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B3_PosY % 8;
					B3_PosY = (B3_PosY + (8 - B_Num));

					B3_Dead = 1;
				}
			}
			//moving right
			if (B3_Dir == 2)
			{
				if (!CheckCollision(B3_PosX + B_BulletSpeed, B3_PosY, 1, 0) && !CheckCollision(B3_PosX + (B_BulletSpeed / 2), B3_PosY, 1, 0) && !CheckCollision(B3_PosX + (B_BulletSpeed / 3), B3_PosY, 1, 0))
				{
					B3_PosX += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B3_PosX % 8;
					B3_PosX = (B3_PosX + (8 - B_Num));

					B3_Dead = 1;
				}
			}
			//moving left
			if (B3_Dir == 4)
			{
				if (!CheckCollision(B3_PosX - B_BulletSpeed, B3_PosY, 1, 0) && !CheckCollision(B3_PosX - (B_BulletSpeed / 2), B3_PosY, 1, 0) && !CheckCollision(B3_PosX - (B_BulletSpeed / 3), B3_PosY, 1, 0))
				{
					B3_PosX -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B3_PosX % 8;
					B3_PosX = (B3_PosX - (8 - B_Num) + 8);

					B3_Dead = 1;
				}
			}
			move_sprite(B3_SpriteID, B3_PosX, B3_PosY);
		}
		else //else this bullet is dead and should be playing the death animation
		{
			if (B3_Dir == 1) //up
			{
				if (B3_FrameIndex < (5 + 5)) //still alive
				{
					B3_FrameIndex++;
					set_sprite_tile(B3_SpriteID, B3_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B3_SpriteID);
					B3_Using = 0;
					return 1;
				}
			}
			if (B3_Dir == 2) //right
			{
				if (B3_FrameIndex < (11 + 5)) //still alive
				{
					B3_FrameIndex++;
					set_sprite_tile(B3_SpriteID, B3_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B3_SpriteID);
					B3_Using = 0;
					return 1;
				}
			}
			if (B3_Dir == 3) //down
			{
				if (B3_FrameIndex < (17 + 5)) //still alive
				{
					B3_FrameIndex++;
					set_sprite_tile(B3_SpriteID, B3_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B3_SpriteID);
					B3_Using = 0;
					return 1;
				}
			}
			if (B3_Dir == 4) //left
			{
				if (B3_FrameIndex < (23 + 5)) //still alive
				{
					B3_FrameIndex++;
					set_sprite_tile(B3_SpriteID, B3_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B3_SpriteID);
					B3_Using = 0;
					return 1;
				}
			}
		}
	}

	if (B4_Using)
	{
		if (!B4_Dead)
		{
			//moving up
			if (B4_Dir == 1)
			{
				if (!CheckCollision(B4_PosX, B4_PosY - B_BulletSpeed, 1, 0) && !CheckCollision(B4_PosX, B4_PosY - (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B4_PosX, B4_PosY - (B_BulletSpeed / 3), 1, 0))
				{
					B4_PosY -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B4_PosY % 8;
					B4_PosY = (B4_PosY - (8 - B_Num)) + 8;

					B4_Dead = 1;
				}
			}
			//moving down
			if (B4_Dir == 3)
			{
				if (!CheckCollision(B4_PosX, B4_PosY + B_BulletSpeed, 1, 0) && !CheckCollision(B4_PosX, B4_PosY + (B_BulletSpeed / 2), 1, 0) && !CheckCollision(B4_PosX, B4_PosY + (B_BulletSpeed / 3), 1, 0))
				{
					B4_PosY += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B4_PosY % 8;
					B4_PosY = (B4_PosY + (8 - B_Num));

					B4_Dead = 1;
				}
			}
			//moving right
			if (B4_Dir == 2)
			{
				if (!CheckCollision(B4_PosX + B_BulletSpeed, B4_PosY, 1, 0) && !CheckCollision(B4_PosX + (B_BulletSpeed / 2), B4_PosY, 1, 0) && !CheckCollision(B4_PosX + (B_BulletSpeed / 3), B4_PosY, 1, 0))
				{
					B4_PosX += B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B4_PosX % 8;
					B4_PosX = (B4_PosX + (8 - B_Num));

					B4_Dead = 1;
				}
			}
			//moving left
			if (B4_Dir == 4)
			{
				if (!CheckCollision(B4_PosX - B_BulletSpeed, B4_PosY, 1, 0) && !CheckCollision(B4_PosX - (B_BulletSpeed / 2), B4_PosY, 1, 0) && !CheckCollision(B4_PosX - (B_BulletSpeed / 3), B4_PosY, 1, 0))
				{
					B4_PosX -= B_BulletSpeed;
				}
				else
				{
					//snap the nearest grid
					B_Num = B4_PosX % 8;
					B4_PosX = (B4_PosX - (8 - B_Num) + 8);

					B4_Dead = 1;
				}
			}
			move_sprite(B4_SpriteID, B4_PosX, B4_PosY);
		}
		else //else this bullet is dead and should be playing the death animation
		{
			if (B4_Dir == 1) //up
			{
				if (B4_FrameIndex < (5 + 5)) //still alive
				{
					B4_FrameIndex++;
					set_sprite_tile(B4_SpriteID, B4_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B4_SpriteID);
					B4_Using = 0;
					return 1;
				}
			}
			if (B4_Dir == 2) //right
			{
				if (B4_FrameIndex < (11 + 5)) //still alive
				{
					B4_FrameIndex++;
					set_sprite_tile(B4_SpriteID, B4_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B4_SpriteID);
					B4_Using = 0;
					return 1;
				}
			}
			if (B4_Dir == 3) //down
			{
				if (B4_FrameIndex < (17 + 5)) //still alive
				{
					B4_FrameIndex++;
					set_sprite_tile(B4_SpriteID, B4_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B4_SpriteID);
					B4_Using = 0;
					return 1;
				}
			}
			if (B4_Dir == 4) //left
			{
				if (B4_FrameIndex < (23 + 5)) //still alive
				{
					B4_FrameIndex++;
					set_sprite_tile(B4_SpriteID, B4_FrameIndex);
				}
				else //else dead
				{
					BulletSlideSpriteIDsDown(B4_SpriteID);
					B4_Using = 0;
					return 1;
				}
			}
		}
	}
	return 0;
}

//create another bullet
void BulletsAdd(int x, int y, int direction)
{
	if (!B1_Using) //bullet 1
	{
		//data stuff
		BulletSlideSpriteIDsUp();
		B1_SpriteID = 0;
		B1_Using = 1;
		B1_PosX = x;
		B1_PosY = y;
		B1_Animating = 0;
		B1_Dir = direction;
		B1_Dead = 0;

		//sprite stuff
		if (B1_Dir == 1) //up
		{
			set_sprite_tile(0, 5);
			B1_FrameIndex = 5;
		}
		if (B1_Dir == 2) //right
		{
			set_sprite_tile(0, 11);
			B1_FrameIndex = 11;
		}
		if (B1_Dir == 3) //down
		{
			set_sprite_tile(0, 17);
			B1_FrameIndex = 17;
		}
		if (B1_Dir == 4) //left
		{
			set_sprite_tile(0, 23);
			B1_FrameIndex = 23;
		}
		move_sprite(0, x, y);
		return;
	}

	if (!B2_Using) //bullet 2
	{
		//data stuff
		BulletSlideSpriteIDsUp();
		B2_SpriteID = 0;
		B2_Using = 1;
		B2_PosX = x;
		B2_PosY = y;
		B2_Animating = 0;
		B2_Dir = direction;
		B2_Dead = 0;

		//sprite stuff
		if (B2_Dir == 1) //up
		{
			set_sprite_tile(0, 5);
			B2_FrameIndex = 5;
		}
		if (B2_Dir == 2) //right
		{
			set_sprite_tile(0, 11);
			B2_FrameIndex = 11;
		}
		if (B2_Dir == 3) //down
		{
			set_sprite_tile(0, 17);
			B2_FrameIndex = 17;
		}
		if (B2_Dir == 4) //left
		{
			set_sprite_tile(0, 23);
			B2_FrameIndex = 23;
		}
		move_sprite(0, x, y);
		return;
	}

	if (!B3_Using) //bullet 1
	{
		//data stuff
		BulletSlideSpriteIDsUp();
		B3_SpriteID = 0;
		B3_Using = 1;
		B3_PosX = x;
		B3_PosY = y;
		B3_Animating = 0;
		B3_Dir = direction;
		B3_Dead = 0;

		//sprite stuff
		if (B3_Dir == 1) //up
		{
			set_sprite_tile(0, 5);
			B3_FrameIndex = 5;
		}
		if (B3_Dir == 2) //right
		{
			set_sprite_tile(0, 11);
			B3_FrameIndex = 11;
		}
		if (B3_Dir == 3) //down
		{
			set_sprite_tile(0, 17);
			B3_FrameIndex = 17;
		}
		if (B3_Dir == 4) //left
		{
			set_sprite_tile(0, 23);
			B3_FrameIndex = 23;
		}
		move_sprite(0, x, y);
		return;
	}

	if (!B4_Using) //bullet 1
	{
		//data stuff
		BulletSlideSpriteIDsUp();
		B4_SpriteID = 0;
		B4_Using = 1;
		B4_PosX = x;
		B4_PosY = y;
		B4_Animating = 0;
		B4_Dir = direction;
		B4_Dead = 0;

		//sprite stuff
		if (B4_Dir == 1) //up
		{
			set_sprite_tile(0, 5);
			B4_FrameIndex = 5;
		}
		if (B4_Dir == 2) //right
		{
			set_sprite_tile(0, 11);
			B4_FrameIndex = 11;
		}
		if (B4_Dir == 3) //down
		{
			set_sprite_tile(0, 17);
			B4_FrameIndex = 17;
		}
		if (B4_Dir == 4) //left
		{
			set_sprite_tile(0, 23);
			B4_FrameIndex = 23;
		}
		move_sprite(0, x, y);
		return;
	}
}




//----------------------------------------Sprite Methods
