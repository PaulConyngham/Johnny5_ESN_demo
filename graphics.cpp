 /* file: graphics.cpp
   author: paul steven conyngham
   date: 04/07/09
*/
//#include "atto.h"
#include "graphics.h"


// draws a triangle with the x and y co-ordinates specified as the "point" or head of the triangle
void draw_triangle(int x, int y)
{
	atto_color(1.0, 1.0, 0.0);
	
	atto_line(x,y,(x+10),(y+10));
	atto_line(x,y,(x-10),(y+10));
	atto_line((x+10),(y+10),(x-10),(y+10));
}	

void draw_triangle_adv(int x1, int y1, double theta, int length)
{
	/*
	printf("theta is %f\n", theta); 
	printf("theta-30 is %f\n", (theta-30.0)); */
	
	int x2 = 0;
	int y2 = 0;
	
	int arrowx1, tempx1 = 0;
	int arrowy1, tempy1 = 0;
	
	int arrowx2, tempx2 = 0;
	int arrowy2, tempy2 = 0;
	
	double result1, result2 = 0.0;
	
	result1 = length*cos(DegreeToRad(theta));
	result2 = length*sin(DegreeToRad(theta));
	
	//printf("adjacent is %f\n", result1); 
	//printf("opposite is %f\n", result2); 
	
	//rounding up
	result1 = (result1+0.5);
	result2 = (result2+0.5);
	
	//printf("after casting adjacent is %d\n", (int) result1); 
	//printf("after casting opposite is %d\n", (int) result2); 

	
	x2 = x1 - ((int) result1);
	y2 = y1 + ((int) result2);
	
	
	atto_line(x1,y1,x2,y2);
	
	tempy1 = 7*sin(DegreeToRad(45.0-theta));
	arrowy1 = y2+(tempy1+0.5);
	tempx1 = 7*cos(DegreeToRad(45.0-theta));
	arrowx1 = x2+(tempx1+0.5);
	
	//atto_line(x2,y2, ((int) arrowx), ((int) arrowy));
	atto_line(((int) arrowx1),((int) arrowy1), x2, y2);
	
	tempy2 = 7*cos(DegreeToRad(90.0+(45+theta)));
	arrowy2 = y2+(tempy2+0.5);
	tempx2 = 7*sin(DegreeToRad(90.0+(45+theta)));
	arrowx2 = x2+(tempx2+0.5);
	
	atto_line(((int) arrowx2),((int) arrowy2), x2, y2);
	
	atto_line(((int) arrowx1),((int) arrowy1),((int) arrowx2),((int) arrowy2));

	
}

void draw_target(int x, int y)
{
	atto_color(1.0, 1.0, 0.0);

	atto_line((x-10),(y-10),(x+10),(y+10));
	atto_line((x+10),(y-10),(x-10),(y+10));
}

void draw_pixel(int x, int y)
{
	atto_line(x,y,x,y);
}

void draw_targetdistance(int arrowx, int arrowy, int targetx, int targety)
{	
	atto_line(arrowx,arrowy,targetx,targety);
}

void refresh_canvas()
{
	atto_color(0.0, 0.0, 0.0);
	atto_fill(0,0,1000,620);
}

void draw_bar(int startx, int starty, int endx, int endy)
{
	atto_fill(startx,starty,endx,endy);
}

//void atto_line(int x1, int y1, int x2, int y2);