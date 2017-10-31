/* file: graphics.h
   author: paul steven conyngham
   date: 04/07/09
*/

#include <iostream>
#include <time.h>
#include <math.h>
#include "atto.h"
#include "toolbox.h"

#define LINELENGTH 14.0
//#define PI 3.14159

void draw_triangle(int x, int y);
void draw_triangle_adv(int x1, int y1, double theta, int length);
void draw_target(int x, int y);
void draw_pixel(int x, int y);
void draw_targetdistance(int arrowx, int arrowy, int targetx, int targety);
void draw_bar(int startx, int starty, int endx, int endy);
void refresh_canvas();