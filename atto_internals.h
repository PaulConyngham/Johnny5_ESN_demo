/*
 *  atto_internals.h
 *  atto
 *
 *  Created by Russell Webb on 16/02/06.
 *  Copyright 2006 UC. All rights reserved.
 *
 */

#ifndef ATTO_INTERNALS_H
#define ATTO_INTERNALS_H

#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Image.H>
#include <FL/fl_draw.H>
#include <FL/gl.h>
#include <FL/Fl_PNM_Image.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Color_Chooser.H>

class AttoArea : public Fl_Box {
public:
	AttoArea(int x,int y,int w,int h);
	~AttoArea();
	
	void draw();
	int handle(int event);
private:	

};

extern AttoArea *gAttoArea;
extern Fl_Double_Window *gAttoWindow;

#endif


