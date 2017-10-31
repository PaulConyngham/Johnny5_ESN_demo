/*
 *  atto_internals.cpp
 *  atto
 *
 *  Created by Russell Webb on 16/02/06.
 *  Copyright 2006 UC. All rights reserved.
 *
 */

#include "atto_internals.h"
#include "atto.h"
//#include "common.h"

static int gAreaWidth = 600;
static int gAreaHeight = 600;
static int gBorder = -1;

static AttoKeyDownFunction gKeyFunctionDown = 0;
static AttoKeyUpFunction gKeyFunctionUp = 0;
static AttoMouseDownFunction gDownFunction = 0;
static AttoMouseDragFunction gDragFunction = 0;
static AttoMouseUpFunction gUpFunction = 0;
static AttoDrawFunction gDrawFunction = 0;
static AttoMouseScroll gScrollFunction = 0;

int i;

void SetFocus_CB(Fl_Widget *widget, void *custom);

static void Exit_CB(Fl_Widget *widget, void *custom) {
  exit(0);
}

Fl_Double_Window *gAttoWindow=(Fl_Double_Window *)0;

AttoArea *gAttoArea=(AttoArea *)0;

int atto_main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = gAttoWindow = new Fl_Double_Window(gAreaWidth + 2*gBorder, gAreaHeight + 2*gBorder, "Johnny5 is Alive!");
    w = o;
    o->color((Fl_Color)48);
    o->callback((Fl_Callback*)Exit_CB);
    { AttoArea* o = gAttoArea = new AttoArea(gBorder, gBorder, gAreaWidth, gAreaHeight);
      o->box(FL_BORDER_FRAME);
      o->color((Fl_Color)40);
      o->selection_color(FL_DARK1);
      o->labeltype(FL_NORMAL_LABEL);
      o->labelfont(0);
      o->labelsize(14);
      o->labelcolor(FL_BLACK);
      o->align(FL_ALIGN_CENTER);
      o->when(FL_WHEN_RELEASE);
    }
    o->end();
  }
  Fl::visual(FL_DOUBLE|FL_INDEX);
  w->show(argc, argv);
  fl_font(0, 14);
  return Fl::run();
}

void SetFocus_CB(Fl_Widget *widget, void *custom) {
    gAttoArea->take_focus();
}

void atto_setup(int w, int h, AttoKeyDownFunction keydown, AttoKeyUpFunction keyup ,AttoMouseDownFunction down, AttoMouseDragFunction drag, AttoMouseUpFunction up, AttoDrawFunction draw, AttoMouseScroll scroll){
    gAreaWidth = w;
    gAreaHeight = h;

    gKeyFunctionDown = keydown;
    gKeyFunctionUp = keyup;
    gDownFunction = down;
    gDragFunction = drag;
    gUpFunction = up;
    gDrawFunction = draw;
    gScrollFunction = scroll;
}

AttoArea::AttoArea(int x,int y,int w,int h) : Fl_Box(x, y, w, h){

}

AttoArea::~AttoArea(){

}

void AttoArea::draw(){
	Fl_Box::draw();

	if(gDrawFunction){
		gDrawFunction();
	}
}

int AttoArea::handle(int event){
	switch(event){
		case FL_PUSH:
			if(gDownFunction){
				gDownFunction(Fl::event_x() - x(), Fl::event_y() - y(), Fl::event_button());
			}
			return true;
			break;
        case FL_MOUSEWHEEL:
            if(gScrollFunction){
                gScrollFunction(Fl::event_dy());
            }
            return true;
            break;
		case FL_DRAG:
			if(gDragFunction){
				gDragFunction(Fl::event_x() - x(), Fl::event_y() - y(), Fl::event_button());
			}
			return true;
			break;
		case FL_RELEASE:
			if(gUpFunction){
				gUpFunction(Fl::event_x() - x(), Fl::event_y() - y(), Fl::event_button());
			}
			return true;
			break;
		case FL_FOCUS:

			return true;
			break;
		case FL_UNFOCUS:

			return true;
			break;
		case FL_KEYDOWN:
			if(gKeyFunctionDown){
				gKeyFunctionDown(Fl::event_key());
			}
			return true;
			break;
		case FL_KEYUP:
			if(gKeyFunctionUp){
				gKeyFunctionUp(Fl::event_key());
			}
			return true;
			break;
	}
	return false;
}


