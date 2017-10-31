/* file: toolbox.c
   author: paul steven conyngham
   date: 09/07/09
*/

#include "toolbox.h"

void SeedRandom()
{
	srand(time(NULL));
}

	//gTargetPositionX = rand()%1001;
	//gTargetPositionY = rand()%601;

void RandomizeCoords(int *x, int *y, int xrange, int yrange)
{
	*x = rand()%(xrange+1);
	*y = rand()%(yrange+1);
}

double DegreeToRad(double degrees)
{
	double radians = 0.0;
		radians = (degrees*PI)/180;
	
	return radians;
}

void CheckXBounds(double *x)
{
	if (*x > SCREENWIDTH)
	{
		*x =  1000.0; // *x = *x- 1000.0;
	}
	
	if (*x < 0)
	{
		*x = 0.0; // *x = *x+1000.0;
	}
}

void CheckYBounds(double *y)
{
	if (*y > SCREENHEIGHT)
	{
		*y = 600.0; // *y = *y-600.0;
	}
	
	if (*y < 0)
	{
		*y = 0.0; // *y = *y+600.0;
	}
}

void CheckXSpeedBounds(double *Xspeed)
{
	if(*Xspeed > 1.0)
	{
		*Xspeed = 1.0;
	}
	if(*Xspeed < -1.0)
	{
		*Xspeed = -1.0;
	}
	
}

void CheckYSpeedBounds(double *Yspeed)
{
	if(*Yspeed < -1.0)
	{
		*Yspeed = -1.0;
	}
	if(*Yspeed > 1.0)
	{
		*Yspeed = 1.0;
	}
	
}

void CalculateArrowHeadPos(double *x1, double *y1, double *headx, double *heady, double theta)
{
	double result1, result2 = 0.0;
	
	result1 = LINELENGTH*cos(DegreeToRad(theta));
	result2 = LINELENGTH*sin(DegreeToRad(theta));
	
	*headx = (*x1) -  (result1);
	*heady = (*y1) + (result2);
	
}

int CalculateCollision(int arrowx, int arrowy, int targetx, int targety, int tolerance)
{
	
	if ( (((targetx+tolerance)-arrowx) < (tolerance*2))&&(((targetx+tolerance)-arrowx) > 0)&&(((targety+tolerance)-arrowy) < (tolerance*2))&&(((targety+tolerance)-arrowy) > 0) )
	
	//if( ((targetx-arrowx) <= abs((int) (xspeed+0.5)))&&((arrowx-targetx) <= abs((int) (xspeed+0.5)))&&((targety-arrowy) <= abs((int) (yspeed+0.5)))&&((arrowy-targety) <= abs((int) (yspeed+0.5)))     )
	{
		//&&((targety-arrowy) < hspeed)&&((targety-arrowy) < -hspeed)&&(((xspeed)&&(yspeed)) != 0)
		return 1;
	}
	return 0;
}

double CalculateDistance(double x1, double y1, double x2, double y2)
{
	double x,y = 0.0;
	double result = 0.0;
	double thetatemp = 0.0;
	
	x =  ((x2-x1));
	y =  ((y1-y2));
	
	thetatemp =  atan(y/x);//	thetatemp =  (180/3.14)*atan(y/x);
	
	//		gSpeed = gArrowSpeedY/(sin((gTheta*3.14/180)));
	result = abs(y/(sin(thetatemp))); //	result = y/(sin((thetatemp*3.14/180)));
	
	//result = sqrt(x^2+y^2);
	
	return result;
}

/*
double CalculateRelativeDistance(double initialdistance, double currentdistance)
{
	currentdistance = initialdistance-currentdistance;
	
	currentdistance = currentdistance/initialdistance;
	
	if(currentdistance < 0.0)
	{
		//currentdistance = currentdistance*-1;
		currentdistance = 0.0;
	}
	
	return currentdistance;
} */

double CalculateReward(double currentdistance)
{
	double reward = 1.0-currentdistance/1000;
	
	return reward;
}

double CalculateRelativeXDistance(double currentdistance)
{
		double reward = (currentdistance-500)/1000;
		
			return reward;


}

double CalculateRelativeYDistance(double currentdistance)
{
		double reward = (currentdistance-300)/600;
		
			return reward;


}

