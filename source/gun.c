//----------------------------------------Includes
#include "bullets.c"



//----------------------------------------Variables
int G_CanFire = 1; //if the player's gun can fire or not
int G_FireCount = 0; //the count up to the firerate. 
int G_FireRate = 5; //the speed at which the gun can fire. this is the wait time between shots. so a lower number is faster
int G_Spread = 0; //the amount of spread. the lower the better





//----------------------------------------General Methods
//fire the players gun, if possible.
int GunFire(int x, int y, int direction) //0 - nothing happened, 1 - gun fired and bullet instantiated
{
	if (G_CanFire) //fire the gun
	{
		G_CanFire = 0;
		G_FireCount = 0;
		BulletsAdd(x, y, direction);
		return 1;
	}
	return 0;
}

//update the gun stuff
void GunUpdate()
{
	//printf("%d", G_CanFire);
	if (!G_CanFire) //if gun can't fire then count until it can
	{
		if (G_FireCount > G_FireRate)
		{
			G_CanFire = 1;
		}
		else
		{
			G_FireCount++;
		}
	}
}