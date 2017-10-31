/* file: controls.h
   author: paul steven conyngham
   date: 06/07/09
*/

#include <math.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "toolbox.h"

void MoveInXPos(double *PositionX);
void MoveInXNeg(double *PositionX);
void MoveInYPos(double *PositionY);
void MoveInYNeg(double *PositionY);
void RotateAntiClockwise(double *theta);
void RotateClockwise(double *theta);
void IncreaseSpeed(double *speed);
void DecreaseSpeed(double *speed);
//void MoveInSpeedVectorDirection(int *x1, int *y1, int *speed, int *Xspeed, int *Yspeed, double theta);
void UpdateSpeedVector(double *speed, double *Xspeed, double *Yspeed, double theta);
void MoveInSpeedVectorDirectionNew(double *x1, double *y1,double *Xspeed, double *Yspeed);