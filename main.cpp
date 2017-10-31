/* file: main.cpp
   author: paul steven conyngham
   date: 04/07/09
   updated : 23/07/09
*/
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <math.h>

// robot game include files
#include "atto.h"
#include "graphics.h"
#include "controls.h"
#include "toolbox.h"

//Russ ESN include files
#include "Misc.h"
#include "SimpleEsnNet.h"
#include "gnuplot_i.hpp"

char gDisplayString[] = "x";
//int GraphicsDisplayMap[1000][600];
double gInitialArrowPositionX = 200;
double gInitialArrowPositionY = 451.0;
double gArrowPositionX = gInitialArrowPositionX;
double gArrowPositionY = gInitialArrowPositionY;
double gArrowHeadPositionX = 0;
double gArrowHeadPositionY = 0;
double gArrowSpeed = 0; //hypotenuse of the speed vector
double gArrowSpeedX = 0.0;
double gArrowSpeedY = 0.0;
double gTheta = 0.0;
int gTargetPositionX = 0;
int gTargetPositionY = 0;
int gTextX = 0;
int gTextY = 0;

int gSim = 0;
int gCollisionDetected = 0;
int gFlag = 0;
int gFlag1 = 0;
int gNumLoops = 0;
int gPlaybackloop = 0;
int gInitialTime = 0;


//double gInitialDistance = 0.0;
double gRelativedistance = 0.0;
double gCurrentdistance = 0.0;
double gSpeed = 0.0;
int gNumsteps = 0;
double gReward = 0.0;
double gRewardtemp = 0.0;
double gXcoord = 0.0;
double gYcoord = 0.0;


vector< double > gdistance0;
vector< double > gdistance1;
vector< double > gdistance2;
vector< double > gdistance3;
vector< double > gdistance4;
//vector< double > gpred;

vector< double > gArrowPositionXvector;
vector< double > gArrowPositionYvector;
vector< double > gThetavector;
vector< double > gArrowSpeedvector; //hypotenuse of the speed vector
vector< double > gArrowSpeedXvector;
vector< double > gArrowSpeedYvector;


void draw()
{
	double speedvectorangle = 0.0;
	
	
	refresh_canvas();
	draw_target(gTargetPositionX,gTargetPositionY);
	//draw_triangle(gArrowPositionX,gArrowPositionY);
	
	CalculateArrowHeadPos(&gArrowPositionX, &gArrowPositionY, &gArrowHeadPositionX, &gArrowHeadPositionY, gTheta);
	printf("gTheta is %lf\n",gTheta);

	gCollisionDetected = CalculateCollision(gArrowHeadPositionX, gArrowHeadPositionY, gTargetPositionX, gTargetPositionY,10);
	if(gCollisionDetected == 1)
	{	
		gFlag = 1;
	}
	
	if(gFlag == 1)
	{
		atto_string(gTargetPositionX+20, gTargetPositionY+5,"collision detected");
	}

	speedvectorangle = (180/3.14)*atan2(gArrowSpeedY,gArrowSpeedX);

	MoveInSpeedVectorDirectionNew(&gArrowPositionX,&gArrowPositionY,&gArrowSpeedX,&gArrowSpeedY);
	printf("gArrowSpeedX is %lf\n",gArrowSpeedX);
	printf("gArrowSpeedY is %lf\n",gArrowSpeedY);


	gRelativedistance = CalculateDistance(gArrowHeadPositionX, gArrowHeadPositionY, gTargetPositionX, gTargetPositionY);
	printf("Distance is %lf\n",gRelativedistance);
	gReward = CalculateReward(gRelativedistance);	
	printf("gReward is %lf\n",gReward);


	//draw_triangle_adv(gArrowPositionX,gArrowPositionY,gTheta);
	
//void CalculateArrowHeadPos(int *x1, int *y1, int *headx, int *heady, double theta);
	atto_color(1.0, 0.0, 0.0);
	draw_targetdistance(gArrowHeadPositionX, gArrowHeadPositionY, gTargetPositionX, gTargetPositionY);
		
	atto_color(1.0, 1.0, 0.0);
	draw_triangle_adv(((int)gArrowPositionX),((int)gArrowPositionY),gTheta,14);
	
	//atto_color(1.0, 0.0, 0.0);
	//draw_triangle_adv(((int)gArrowPositionX),((int)gArrowPositionY),speedvectorangle,25);
	
	atto_color(128.0, 128.0, 128.0);
	draw_bar(0, 600, 1000, 700);
	
	atto_color(0.0, 0.0, 0.0);

	draw_triangle_adv(800,650,speedvectorangle,25);
	atto_string(750, 620,"Orientation");

	atto_color(1.0, 0.0, 0.0);
	atto_frame(50, 645, gArrowSpeed*10, 10);
	atto_color(0.0, 0.0, 0.0);	
	atto_string(50, 620,"Acceleration");
	//draw_bar(50, 610, 50+gArrowSpeed, 611);
	
	//atto_string(gArrowPositionX, gArrowPositionY, "X");
	if(gSim == 1)
	{
		atto_color(1.0, 1.0, 0.0);
		atto_string(50, 50,"Simulating....Please Stand By");
		//gSim = 0;
	}	
	if(gSim == 2)
	{
		//atto_idle_end(IdleESNcalc);
		gSim = 0;
	}
	printf("Frame Updated...Draw succesfully called\n");

}

void IdlePlayback(void *custom)
{	
	int k = 0;
	int wastetime = 0;
	gArrowPositionX = gArrowPositionXvector[gPlaybackloop];
	gArrowPositionY = gArrowPositionYvector[gPlaybackloop];
	gArrowSpeedX = gArrowSpeedXvector[gPlaybackloop];
	gArrowSpeedY = gArrowSpeedYvector[gPlaybackloop];
	gTheta = gThetavector[gPlaybackloop];

	gPlaybackloop++;
	draw();
	
	/*for(k=0; k<100000; k++)
	{
	
	}*/
	
	if(gPlaybackloop == gArrowPositionXvector.size())
	{
		atto_idle_end(IdlePlayback);
		gPlaybackloop = 0;
	}
}



void IdleAnimate(void *custom)
{
	atto_redraw();
}

void IdleESNcalc(void *custom)
{
	Esn< 3, 2, 400,float> esn0(0.20, 0.95); //esn(0.20, 0.95);
	Esn< 3, 2, 400, float > esn1(0.20, 0.95);// esn1(0.20, 0.95); 
	
	//time_t rawtime;
   	//struct tm * timeinfo;

	int numsteps = 50000;
	double k = 0.0;
	double j = 0.0;
	double random = 0.0;
	int loopcount = 0;
	int i = 0;
	double tempangle = 0.0;
	
	double gArrowHeadPositionXtemp = gArrowHeadPositionX;
	double gArrowHeadPositionYtemp = gArrowHeadPositionY;
	double ArrowSpeedLocal = 0.0;

	
	//esn 0 variables
	double tempaccelerationprediction0 = 0.0;
	double tempturningprediction0 = 0.0;
	double arrowpositionx0 = gArrowPositionX;
	double arrowpositiony0 = gArrowPositionY;
	double ArrowSpeedX0 = gArrowSpeedX;
	double ArrowSpeedY0 = gArrowSpeedY;
	double theta0 = gTheta;
	double result0 = 0.0;
	
	//esn 1 variables
	double tempaccelerationprediction1 = 0.0;
	double tempturningprediction1 = 0.0;
	double arrowpositionx1 = gArrowPositionX;
	double arrowpositiony1 = gArrowPositionY;
	double ArrowSpeedX1 = gArrowSpeedX;
	double ArrowSpeedY1 = gArrowSpeedY;
	double theta1 = gTheta;
	double result1 = 0.0;
	
	double currentdistance0 = 0.0;	
	double currentdistance1 = 0.0;	

	atto_idle_end(IdleAnimate);

	
		//for(loopcount = 0; loopcount < numsteps; loopcount++)
		while((gNumLoops != 5)) 
		{
		
		//handy for debugging
		loopcount++;
		printf("loopcount is %i\n",loopcount);	
		
		/*if(loopcount > 100000)
		{
			break;
		}*/
	
		//resetting variables here for next use of this loop
		currentdistance0 = 0.0;
		currentdistance1 = 0.0;
		tempaccelerationprediction0 = 0.0;
		tempturningprediction0  = 0.0;
		tempaccelerationprediction1 = 0.0;
		tempturningprediction1 = 0.0;
		
		arrowpositionx0 = gArrowPositionX;
		arrowpositionx1 = gArrowPositionX;
		arrowpositiony0 = gArrowPositionY;
		arrowpositiony1 = gArrowPositionY;
		
		ArrowSpeedX0 = gArrowSpeedX;
		ArrowSpeedY0 = gArrowSpeedY;
		ArrowSpeedX1 = gArrowSpeedX;
		ArrowSpeedY1 = gArrowSpeedY;
		theta0 = gTheta;
		theta1 = gTheta;
		
		//this is the randomization control
		k = k+0.0001;
		if(k > 0.7)
		{
			k = 0.7;

		}
		

		
		//stuff that needs to be calculated every loop	
		//calculating the new distance after a interation of a loop between the arrow head and the target
		CalculateArrowHeadPos(&gArrowPositionX, &gArrowPositionY, &gArrowHeadPositionX, &gArrowHeadPositionY, gTheta);
		gRelativedistance = CalculateDistance(gArrowHeadPositionX, gArrowHeadPositionY, gTargetPositionX, gTargetPositionY);
		printf("gRelativedistance is %lf\n",gRelativedistance);
		gXcoord = CalculateRelativeXDistance(gArrowPositionX);
		gYcoord = CalculateRelativeYDistance(gArrowPositionY);

		gRewardtemp = CalculateReward(gRelativedistance);
		printf("gRewardtemp is %lf\n",gRewardtemp);


		gSpeed = sqrt(gArrowSpeedY*gArrowSpeedY+gArrowSpeedX*gArrowSpeedX);
		printf("gSpeed is %lf\n",gSpeed);
//gXcoord
		
		if(gSpeed > 10)
		{
			gSpeed = 10;
		}
		if(gSpeed < -10)
		{
			gSpeed = -10;
		}

		
		esn1 = esn0;

		
		//connect esn 0 network
		//esn0.Input(0, (gSpeed/10));
		esn0.Input(0, gXcoord); //gRewardtemp
		esn0.Input(1, gSpeed);
		esn0.Input(2, gYcoord);

	
		esn0.Update();
		
		tempaccelerationprediction0 = esn0.Output(0);
		tempturningprediction0 = esn0.Output(1);
		
		random = -1.0+double(2.0*rand()/(RAND_MAX + 1.0));
		tempaccelerationprediction0 = tanh(k*tempaccelerationprediction0 + (1-k)*random);
			printf("tempaccelerationprediction0 is %lf\n",tempaccelerationprediction0);

		random = -1.0+double(2.0*rand()/(RAND_MAX + 1.0));
		tempturningprediction0 = tanh(k*tempturningprediction0 + (1-k)*random);
		
		//evaluating ESN 0's results
		if (tempturningprediction0 > 0)
		{
			for(i=0; i < tempturningprediction0*360; i++)
			{
			RotateClockwise(&theta0);
			}
		}
		if (tempturningprediction0 < 0)
		{
			for(i=0; i < tempturningprediction0*360; i++)
			{
			RotateAntiClockwise(&theta0);
			}
		}
	
		//NOT HAPPY WITH THIS SECTION AT ALL
		if (tempaccelerationprediction0 > 0)
		{

			ArrowSpeedLocal = tempaccelerationprediction0/20;
			UpdateSpeedVector(&ArrowSpeedLocal,&ArrowSpeedX0,&ArrowSpeedY0,theta1);
			ArrowSpeedLocal = 0;
		}
		/*if (tempaccelerationprediction0 < 0)
		{

			ArrowSpeedLocal = tempaccelerationprediction0;
			UpdateSpeedVector(&ArrowSpeedLocal,&ArrowSpeedX0,&ArrowSpeedY0,theta1);
						ArrowSpeedLocal = 0;
		}*/
		
		//implemeting the evaluated results
		MoveInSpeedVectorDirectionNew(&arrowpositionx0,&arrowpositiony0,&ArrowSpeedX0,&ArrowSpeedY0);
		
		CalculateArrowHeadPos(&arrowpositionx0, &arrowpositiony0, &gArrowHeadPositionXtemp, &gArrowHeadPositionYtemp, theta0);
		currentdistance0 = CalculateDistance(gArrowHeadPositionXtemp, gArrowHeadPositionYtemp, gTargetPositionX, gTargetPositionY);
		printf("currentdistance0  position is %lf\n",currentdistance0);

		
		result0 = CalculateReward(currentdistance0);

		
		//connect esn 1 network
		esn1.Input(0, gXcoord);
		esn1.Input(1, gSpeed);
	 	esn1.Input(2, gYcoord);
	
		esn1.Update();
		
		tempaccelerationprediction1 = esn1.Output(0);
		//tempturningprediction1 = esn1.Output(1);
		
		random = -1.0+double(2.0*rand()/(RAND_MAX + 1.0));
		tempaccelerationprediction1 = tanh(k*tempaccelerationprediction1 + (1-k)*random);
	    printf("tempaccelerationprediction1 is %lf\n",tempaccelerationprediction1);


		random = -1.0+double(2.0*rand()/(RAND_MAX + 1.0));
		tempturningprediction1 = tanh(k*tempturningprediction1 + (1-k)*random);
		
		//evaluating ESN 0's results
		if (tempturningprediction1 > 0)
		{
			for(i=0; i < tempturningprediction1*360; i++)
			{
			RotateClockwise(&theta1);
			}
		}
		if (tempturningprediction1 < 0)
		{
			for(i=0; i < tempturningprediction1*360; i++)
			{
			RotateAntiClockwise(&theta1);
			}
		}
	
		//NOT HAPPY WITH THIS SECTION AT ALL
		if (tempaccelerationprediction1 > 0)
		{

			ArrowSpeedLocal = tempaccelerationprediction1/20;
			UpdateSpeedVector(&ArrowSpeedLocal,&ArrowSpeedX1,&ArrowSpeedY1,theta1);
			ArrowSpeedLocal = 0;
		}
		/*if (tempaccelerationprediction1 < 0)
		{

			ArrowSpeedLocal = tempaccelerationprediction1;
			UpdateSpeedVector(&ArrowSpeedLocal,&ArrowSpeedX1,&ArrowSpeedY1,theta1);
			ArrowSpeedLocal = 0;
		}*/
		
		//implemeting the evaluated results
		MoveInSpeedVectorDirectionNew(&arrowpositionx1,&arrowpositiony1,&ArrowSpeedX1,&ArrowSpeedY1);
		
		CalculateArrowHeadPos(&arrowpositionx1, &arrowpositiony1, &gArrowHeadPositionXtemp, &gArrowHeadPositionYtemp, theta1);
		currentdistance1 = CalculateDistance(gArrowHeadPositionXtemp, gArrowHeadPositionYtemp, gTargetPositionX, gTargetPositionY);
		printf("currentdistance1  position is %lf\n",currentdistance1);

		
		result1 = CalculateReward(currentdistance1);
		
		//now evaluate which esn produced a better result...
		if(result0 > result1)
		{

			esn0.TrainPrevious(0, tempaccelerationprediction0, 1.0 ); //fmax(0, 2.0*(1.0 - float(i)/(numSteps - numGraph)))
			esn0.TrainPrevious(1, tempturningprediction0, 1.0 ); 
			//UpdateSpeedVector(&gArrowSpeedLocal,&ArrowSpeedX0,&ArrowSpeedY0,theta0);
			gArrowSpeedX = ArrowSpeedX0;
			gArrowSpeedY = ArrowSpeedY0;
			gTheta = theta0;
			//UpdateSpeedVector(&gArrowSpeed,&gArrowSpeedX,&gArrowSpeedY,gTheta);	
			
			printf("ESN 0 wins! with a result of %lf\n",result0);
			printf("ESN 1 was..... %lf\n",result1);

			printf("temp acceleration prediction 0 is %lf\n",tempaccelerationprediction0);
			printf("temp turning prediction 0 is %lf\n",tempturningprediction0);
			

		}
		if(result1 > result0)
		{
			esn0 = esn1;
			esn0.TrainPrevious(0, tempaccelerationprediction1, 1.0 ); //fmax(0, 2.0*(1.0 - float(i)/(numSteps - numGraph)))
			esn0.TrainPrevious(1, tempturningprediction1, 1.0 ); 
			//UpdateSpeedVector(&gArrowSpeedLocal,&ArrowSpeedX1,&ArrowSpeedY1,theta1);
			gArrowSpeedX = ArrowSpeedX1;
			gArrowSpeedY = ArrowSpeedY1;
			gTheta = theta1;
			
			printf("ESN 1 wins! with a result of %lf\n",result1);
			printf("ESN 0 was..... %lf\n",result0);

			printf("temp acceleration prediction 1 is %lf\n",tempaccelerationprediction1);
			printf("temp turning prediction 1 is %lf\n",tempturningprediction1);
		}
		if(result0 == result1)
		{
			printf("NO winner\n");			

			esn0.TrainPrevious(0, tempaccelerationprediction0, 1.0 ); //fmax(0, 2.0*(1.0 - float(i)/(numSteps - numGraph)))
			esn0.TrainPrevious(1, tempturningprediction0, 1.0 ); 
			//UpdateSpeedVector(&gArrowSpeed,&ArrowSpeedX0,&ArrowSpeedY0,theta0);
			gArrowSpeedX = ArrowSpeedX0;
			gArrowSpeedY = ArrowSpeedY0;
			gTheta = theta0;
		}	//UpdateSpeedVect
   	    //gArrowSpeedX *= 0.99;
		//gArrowSpeedY *= 0.99;
			
	    printf("gArrowSpeedX is %lf\n",gArrowSpeedX);
	    printf("gArrowSpeedY is %lf\n",gArrowSpeedY);
	    printf("gTheta is %lf\n",gTheta);




			
		//sleep(1);
		
		MoveInSpeedVectorDirectionNew(&gArrowPositionX,&gArrowPositionY,&gArrowSpeedX,&gArrowSpeedY);
	    printf("Pixel X position is %lf\n",gArrowPositionX);
	    printf("Pixel Y position is %lf\n",gArrowPositionY);

		printf("************************************************\n");
		
		currentdistance1 = CalculateDistance(gArrowPositionX, gArrowPositionY, gTargetPositionX, gTargetPositionY);
		
		if(gNumLoops == 0)
		{
			gdistance0.push_back(currentdistance1);
		}
		if(gNumLoops == 1)
		{
			//gArrowPositionX = 700;
			//gArrowPositionY = 150;
			gdistance1.push_back(currentdistance1);
		}
		if(gNumLoops == 2)
		{
			gdistance2.push_back(currentdistance1);
		}
		if(gNumLoops == 3)
		{
			gdistance3.push_back(currentdistance1);
		}
		if(gNumLoops == 4)
		{
			gdistance4.push_back(currentdistance1);
		}
		
		
		gArrowPositionXvector.push_back(gArrowPositionX);
		gArrowPositionYvector.push_back(gArrowPositionY);
		gArrowSpeedXvector.push_back(gArrowSpeedX);
		gArrowSpeedYvector.push_back(gArrowSpeedY);
		gThetavector.push_back(gTheta);

		
		gCollisionDetected = CalculateCollision(gArrowHeadPositionX, gArrowHeadPositionY, gTargetPositionX, gTargetPositionY,3);
		//randomize location if within the tolerance 
		if(gCollisionDetected == 1)
		{
			gNumLoops++;
			
			gArrowPositionX = gInitialArrowPositionX;// 800+double(2.0*rand()/(RAND_MAX + 1000.0));//gInitialArrowPositionX;//
			gArrowPositionY = gInitialArrowPositionY;// 300+double(2.0*rand()/(RAND_MAX + 600.0));//gInitialArrowPositionY;//
			
			//k = 0;
			gCollisionDetected = 0;
		} 
		printf("Number of loops is %d\n",gNumLoops);

		//draw();
		

	}
		
	Gnuplot::set_GNUPlotPath("/Applications/Gnuplot.app/Contents/Resources/bin");
	Gnuplot gp2;
	gp2.set_style("lines");
	gp2.plot_x(gdistance0,"Attempt 1");
	gp2.plot_x(gdistance1,"Attempt 2");
	gp2.plot_x(gdistance2,"Attempt 3");
	gp2.plot_x(gdistance3,"Attempt 4");
	gp2.plot_x(gdistance4,"Attempt 5");
    //gp2.plot_x(gArrowPositionXvector);
    //gp2.plot_x(gArrowPositionYvector);

	gp2.showonscreen();
	sleep(1);
	
	printf("process complete\n");
	
	printf("Attempt 1 took %d\n", (int) gdistance0.size());
	printf("Attempt 2 took %d\n", (int) gdistance1.size());
	printf("Attempt 3 took %d\n", (int) gdistance2.size());
	printf("Attempt 4 took %d\n", (int) gdistance3.size());
	printf("Attempt 5 took %d\n", (int) gdistance4.size());
	printf("The random time variable was %d\n",gInitialTime);
	
	




	

	
	
	atto_idle_end(IdleESNcalc);
	gSim = 2;
	

	
}




void keydown(int code)
{
	//atto_idle_end(IdleAnimate);

	//increase arrow speed in the forward direction relative to the arrow head
	if((code == 'w')||(code == 'W'))
	{
		IncreaseSpeed(&gArrowSpeed);
		UpdateSpeedVector(&gArrowSpeed,&gArrowSpeedX,&gArrowSpeedY,gTheta);
		//MoveInYPos(&gArrowPositionY);
		atto_redraw();
	}
	//decrease arrow speed in the reverse direction relative to the arrow head
	if((code == 's')||(code == 'S'))
	{
		DecreaseSpeed(&gArrowSpeed);
		UpdateSpeedVector(&gArrowSpeed,&gArrowSpeedX,&gArrowSpeedY,gTheta);
		//DecreaseSpeed(&gArrowSpeed);
		//MoveInYNeg(&gArrowPositionY);
		atto_redraw();
	}
	
	//rotate arrow anti-clockwise
	if((code == 'a')||(code == 'A'))
	{
		//MoveInXNeg(&gArrowPositionX);
		RotateAntiClockwise(&gTheta);
		atto_redraw();
	}
	//rotate arrow clockwise
	if((code == 'd')||(code == 'D'))
	{
		//MoveInXPos(&gArrowPositionX);
		RotateClockwise(&gTheta);
		atto_redraw();
	}
	
	if((code == 'u')||(code == 'U'))
	{
		gFlag = 0;
	}
	
	//void atto_idle_start(AttoGenericFunction f, void *custom);
	//atto_idle_start(IdleAnimate,0);

}

void keyup(int code)
{
	
	//atto_idle_end(IdleAnimate);

	if((code == 'w')||(code == 'W'))
	{
		//IncreaseSpeed(&gArrowSpeed);
		//gArrowSpeed =  ((int) gArrowSpeed/10);

		//UpdateSpeedVector(&gArrowSpeed,&gArrowSpeedX,&gArrowSpeedY,gTheta);
		gArrowSpeed = 0.0;
		//MoveInYPos(&gArrowPositionY);
		atto_idle_start(IdleAnimate,0);
		//atto_redraw();
	}
	
	//decrease arrow speed in the reverse direction relative to the arrow head
	if((code == 's')||(code == 'S'))
	{
		//gArrowSpeed = 0;

		//MoveInYNeg(&gArrowPositionY);
		atto_redraw();
	}
	
	if((code == 'p')||(code == 'P'))
	{
		gArrowSpeedX = 0.0;
		gArrowSpeedY = 0.0;
	}
	
	if((code == 'l')||(code == 'L'))
	{
		gInitialArrowPositionX = gArrowPositionX;
		gInitialArrowPositionY = gArrowPositionY;

		//if(gFlag1 == 0)
		//{
		//	gFlag1 =1;
		gSim = 1;
		atto_redraw();
		atto_idle_end(IdleAnimate);


		atto_idle_start(IdleESNcalc,0);
		

		atto_idle_end(IdleAnimate);

	//	}
	//	
	}
	
	if((code == 'k')||(code == 'K'))
	{
		atto_idle_end(IdleESNcalc);
		atto_idle_end(IdleAnimate);
		atto_idle_end(IdlePlayback);


	}
	
	if((code == 'r')||(code == 'R'))
	{
		atto_idle_end(IdleAnimate);

		gArrowPositionX = gInitialArrowPositionX;
		gArrowPositionY = gInitialArrowPositionY;
		atto_idle_start(IdlePlayback,0);


		
	}
	if((code == 'q')||(code == 'Q'))
	{
		exit(0);
	}
	

	//atto_idle_start(IdleAnimate,0);


	
	printf("keyboard key %c released\n",code);

}

void mouse_down(int x, int y, int button)
{
	printf("Mouse Click Down\n");
}

void mouse_drag(int x, int y, int button)
{
	//atto_string(x,y,gDisplayString);
}

void mouse_up(int x, int y, int button)
{
	printf("Mouse Click Released\n");
}




void mouse_scroll(int scroll)
{
	printf("Mouse Scrolled\n");
}





int main (int argc, char **argv) 
{ 
	//gArrowPositionX = 50;
	//gArrowPositionY = 50;
	int i = 0;
	double random = 0.0;
	gTargetPositionX = 500;
	gTargetPositionY = 300;
	
	//SeedRandom();
	gInitialTime = time(NULL);
	srand(gInitialTime);

	//RandomizeCoords(&gTargetPositionX,&gTargetPositionY,1000,600);
//	RandomizeCoords(&( (int) gArrowPositionX),&((int) gArrowPositionY),1000,600);


	atto_setup(1000,700, keydown, keyup, mouse_down, mouse_drag, mouse_up, draw, mouse_scroll);
	//atto_idle_start(IdleESNcalc,0);

	atto_main(argc, argv);
	/*
				for(i = 0; i < 100; i++)
			{
			random = -1.0+double(2.0*rand()/(RAND_MAX + 1.0));
			printf("number generated is %f \n",random);
			}
*/


}