//----------------------------------------includes



//----------------------------------------Variables
int M_FrameIndex = 0;
int M_Dir = 1;
int M_Speed = 1; //speed which this guy moves

int M_PosX = 50;
int M_PosY = 50;



//----------------------------------------Methods
//move the sprite around
void MonsterMoveSprite(int x, int y, int SpriteNum)
{
	move_sprite(SpriteNum - 4, x - 4, y - 4);
	move_sprite(SpriteNum - 3, x + 4, y - 4);
	move_sprite(SpriteNum - 2, x + 4, y + 4);
	move_sprite(SpriteNum - 1, x - 4, y + 4);
}

//move the whole monster up
void MonsterMoveUp(int changeDir, int SpriteNum)
{
	if (changeDir)
	{
		M_Dir = 1;
	}

	M_PosY -= M_Speed;
	MonsterMoveSprite(M_PosX, M_PosY, SpriteNum);
}

//move the whole monster down
void MonsterMoveDown(int changeDir, int SpriteNum)
{
	if (changeDir)
	{
		M_Dir = 3;
	}

	M_PosY += M_Speed;
	MonsterMoveSprite(M_PosX, M_PosY, SpriteNum);
}

//move the whole monster right
void MonsterMoveRight(int changeDir, int SpriteNum)
{
	if (changeDir)
	{
		M_Dir = 2;
	}

	M_PosX += M_Speed;
	MonsterMoveSprite(M_PosX, M_PosY, SpriteNum);
}

//move the whole monster left
void MonsterMoveLeft(int changeDir, int SpriteNum)
{
	if (changeDir)
	{
		M_Dir = 4;
	}

	M_PosX -= M_Speed;
	MonsterMoveSprite(M_PosX, M_PosY, SpriteNum);
}

//update the monster, includes sprites and AI
void MonsterUpdate(int SpriteNum)
{
	if (M_Dir == 1)
	{
		set_sprite_tile(SpriteNum - 4, 41);
		set_sprite_tile(SpriteNum - 3, 42);
		set_sprite_tile(SpriteNum - 2, 39);
		set_sprite_tile(SpriteNum - 1, 40);
	}
	if (M_Dir == 2)
	{
		set_sprite_tile(SpriteNum - 4, 45);
		set_sprite_tile(SpriteNum - 3, 46);
		set_sprite_tile(SpriteNum - 2, 47);
		set_sprite_tile(SpriteNum - 1, 44);
	}
	if (M_Dir == 3)
	{
		set_sprite_tile(SpriteNum - 4, 29);
		set_sprite_tile(SpriteNum - 3, 30);
		set_sprite_tile(SpriteNum - 2, 31);
		set_sprite_tile(SpriteNum - 1, 32);
	}
	if (M_Dir == 4)
	{
		set_sprite_tile(SpriteNum - 4, 37);
		set_sprite_tile(SpriteNum - 3, 34);
		set_sprite_tile(SpriteNum - 2, 35);
		set_sprite_tile(SpriteNum - 1, 36);
	}
	MonsterMoveSprite(M_PosX, M_PosY, SpriteNum);

	MonsterMoveDown(1, SpriteNum);
}

//setup the monsters stuff
void MonsterLoad()
{
	set_sprite_tile(0, 29);
	move_sprite(0, M_PosX - 4, M_PosY - 4);
	set_sprite_tile(1, 30);
	move_sprite(1, M_PosX + 4, M_PosY - 4);
	set_sprite_tile(2, 31);
	move_sprite(2, M_PosX + 4, M_PosY + 4);
	set_sprite_tile(3, 32);
	move_sprite(3, M_PosX - 4, M_PosY + 4);
}