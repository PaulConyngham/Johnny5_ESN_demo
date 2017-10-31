/*
 *  Misc.h
 *  HOME
 *
 *  Created by Russell Webb on 25/10/05.
 *  Copyright 2005 UC. All rights reserved.
 *
 */

#ifndef MISC_H
#define MISC_H

#include <math.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::ostringstream;

typedef unsigned long u32;
typedef unsigned char u8;
typedef unsigned int uint;

#ifndef Assert

#ifndef DEBUG_MODE
#define DEBUG_MODE true
#endif

#if DEBUG_MODE

#define Confirm(cond) if(!(cond)) do_assert_failed(__FILE__, __LINE__)
#define Assert(cond) if(!(cond)) do_assert_failed(__FILE__, __LINE__)
#define Require(cond) if(!(cond)) do_assert_failed(__FILE__, __LINE__)

#else

#define Confirm(cond)
#define Assert(cond)
#define Require(cond)

#endif

#endif

#define loop(var, start, end) for(int var = start, endV = end; var < endV; ++var)

#define Failure() do_assert_failed(__FILE__, __LINE__)

void do_assert_failed(const char *file, int line);

const char *AppPath();

template < class T >
string ToString(const T &arg){
	ostringstream out;
	out << arg;
	return(out.str());
}

#endif
