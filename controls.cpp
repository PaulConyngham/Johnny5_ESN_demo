/* file: controls.h
   author: paul steven conyngham
   date: 06/07/09
*/
#include "controls.h"

void MoveInXPos(double *PositionX)
{
	*PositionX = *PositionX+1.0;
}

void MoveInXNeg(double *PositionX)
{
	*PositionX = *PositionX-1;
}

void MoveInYPos(double *PositionY)
{
	*PositionY = *PositionY-1;
}

void MoveInYNeg(double *PositionY)
{
	*PositionY = *PositionY+1;
}

void RotateAntiClockwise(double *theta)
{
	*theta = *theta+10.0;
	
	if(*theta > 360)
	{
		*theta = 0;
	}
}

void RotateClockwise(double *theta)
{
	*theta = *theta-10.0;
	
	if(*theta < -360)
	{
		*theta = 0;
	}
}

void IncreaseSpeed(double *speed)
{
	*speed = *speed+0.1;
	
	if(*speed > 10)
	{
		*speed = 10;
	}
}

void DecreaseSpeed(double *speed)
{
	*speed = *speed-0.01;
	
	if(*speed < -10)
	{
		*speed = -10;
	}
}
/*
void MoveInSpeedVectorDirection(double *x1, double *y1, int *speed, int *Xspeed, int *Yspeed, double theta)
{	
	double result1, result2 = 0.0;	
	
	printf("speed is %d\n", *speed); 

	
	result1 = (*speed)*cos(DegreeToRad(theta));
	result2 = (*speed)*sin(DegreeToRad(theta));
	
	*Xspeed = *Xspeed+((int) (result1+0.5));
	*Yspeed = *Yspeed+((int) (result2+0.5));
					
	*x1 = *x1 - *Xspeed;
	*y1 = *y1 + *Yspeed;
	
	printf("the speed in the x direction is %d\n", *Xspeed); 
	printf("the speed in the y direction is %d\n", *Yspeed); 

	
	CheckXBounds(x1);
	CheckYBounds(y1);

	
}*/

void UpdateSpeedVector(double *speed, double *Xspeed, double *Yspeed, double theta)
{
	double result1, result2 = 0.0;	
	
	//printf("speed is %d\n", *speed); 

	
	result1 = (*speed)*cos(DegreeToRad(theta));
	result2 = (*speed)*sin(DegreeToRad(theta));
	
	*Xspeed = *Xspeed+(result1); //rounding up built in here
	*Yspeed = *Yspeed+(result2);
	
	CheckXSpeedBounds(Xspeed);
	CheckYSpeedBounds(Yspeed);
			
}

void MoveInSpeedVectorDirectionNew(double *x1, double *y1, double *Xspeed, double *Yspeed)
{
	*x1 = *x1 - (*Xspeed);
	*y1 = *y1 + (*Yspeed);
	
	/*printf("the speed in the x direction is %f\n", *Xspeed); 
	printf("the speed in the y direction is %f\n", *Yspeed); 
	
	printf("the X co-ordinate is now %f\n", *x1); 
	printf("the Y co-ordinate is now %f\n", *y1); */

	
	CheckXBounds(x1);
	CheckYBounds(y1);	
}	

