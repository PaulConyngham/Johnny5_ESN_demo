/* file: toolbox.h
   author: paul steven conyngham
   date: 09/07/09
*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <math.h>

#define PI 3.14159
#define SCREENWIDTH 1000
#define SCREENHEIGHT 600
#define LINELENGTH 14.0
#define HYPOTENUSE 1166.19038

void SeedRandom();
void RandomizeCoords(int *x, int *y, int xrange, int yrange);
double DegreeToRad(double degrees);
void CheckXBounds(double *x);
void CheckYBounds(double *y);
void CheckXSpeedBounds(double *x);
void CheckYSpeedBounds(double *y);
void CalculateArrowHeadPos(double *x1, double *y1, double *headx, double *heady, double theta);
int CalculateCollision(int arrowx, int arrowy, int targetx, int targety, int tolerance);
double CalculateDistance(double x1, double y1, double x2, double y2);
//double CalculateRelativeDistance(double initialdistance, double currentdistance);
double CalculateReward(double currentdistance);
double CalculateRelativeXDistance(double currentdistance);
double CalculateRelativeYDistance(double currentdistance);