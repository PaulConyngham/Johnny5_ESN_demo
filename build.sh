#!/bin/sh

AppName=johnny5enhance

g++ \
	main.cpp \
	graphics.cpp \
	controls.cpp \
	toolbox.cpp \
	atto.cpp \
	atto_internals.cpp \
	Misc.cpp\
	SimpleEsnNet.h \
	gnuplot_i.cpp \
    -Wall -lm -lstdc++ `fltk-config --ldflags --use-images` -o ${AppName}
    

