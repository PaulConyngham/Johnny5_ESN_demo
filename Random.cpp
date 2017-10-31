/*
 *  Random.cpp
 *  Pictionary 3
 *
 *  Created by Russ Webb on Mon Dec 08 2003.
 *  Copyright (c) 2003 RNI. All rights reserved.
 *
 */

#include "Random.h"
#include <time.h>


static RandomSource gR;

RandomSource &R(){
	return gR;
}

BoolSource RandBool;

