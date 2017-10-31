/*
 *  Random.h
 *  Pictionary 3
 *
 *  Created by Russ Webb on Mon Dec 08 2003.
 *  Copyright (c) 2003 RNI. All rights reserved.
 *
 */

#ifndef RANDOM_H
#define RANDOM_H
#include <time.h>
#include "Misc.h"

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

class RandomSource{
public:
    RandomSource(u32 seed = 0) : initialSeed(seed), mti(N+1){ 
		mag01[0] = 0x0;
		mag01[1] = MATRIX_A;
		
		if(initialSeed == 0){
			initialSeed = time(0);
			//initialSeed = clock();
			if(initialSeed == 0){
				initialSeed = 0xFA43AB56;
			}
		}
		sgenrand(initialSeed);
	}
    ~RandomSource(){ }
		
	
	u32 U32(){
		u32 y;
		/* mag01[x] = x * MATRIX_A  for x=0,1 */
		
		if (mti >= N) { /* generate N words at one time */
			int kk;
			
			if (mti == N+1)   /* if sgenrand() has not been called, */
				sgenrand(4357); /* a default initial seed is used   */
			
			for (kk=0;kk<N-M;kk++) {
				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
				mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
			}
			for (;kk<N-1;kk++) {
				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
				mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
			}
			y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
			
			mti = 0;
		}
		
		y = mt[mti++];
		y ^= TEMPERING_SHIFT_U(y);
		y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
		y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
		y ^= TEMPERING_SHIFT_L(y);
		
		return y;     
	}
    
	double Normal(){
		double u = Float();
		double v = Float();
		// half of Box-Muller algorithm (could get another sample from u and v)
		return sqrt(-2 * log(u)) * cos(2 * M_PI * v);
	}
	
	double Float(){
		// [0, 1]
		return ((double)U32()) * 2.3283064370807974e-10;
	}
	
	u32 Seed() const{ return initialSeed; }
private:
    void sgenrand(u32 seed){
		for(int i=0;i<N;i++) {
			mt[i] = seed & 0xffff0000;
			seed = 69069 * seed + 1;
			mt[i] |= (seed & 0xffff0000) >> 16;
			seed = 69069 * seed + 1;
		}
		mti = N;	
	}
	
	u32 initialSeed;
    u32 mt[N]; /* the array for the state vector  */
    int mti; /* mti==N+1 means mt[N] is not initialized */
    u32 mag01[2];
};

RandomSource &R();

class BoolSource : protected RandomSource{
public: 
	BoolSource(u32 seed = 0) : RandomSource(seed), num(0), sample(0){  }
	
	bool operator()(){ return Bool(); }
	
	bool Bool(){
		if(num <= 0){
			sample = U32();
			num = 32;
		}
		bool result = sample & 1UL;
		sample >>= 1;
		num -= 1;
		return result;
	}
private:
	int num;
	u32 sample;
};

extern BoolSource RandBool;

#undef N 
#undef M 

#endif

// license
/* A C-program for MT19937: Integer version (1999/10/28)          */
/*  genrand() generates one pseudorandom unsigned integer (32bit) */
/* which is uniformly distributed among 0 to 2^32-1  for each     */
/* call. sgenrand(seed) sets initial values to the working area   */
/* of 624 words. Before genrand(), sgenrand(seed) must be         */
/* called once. (seed is any 32-bit integer.)                     */
/*   Coded by Takuji Nishimura, considering the suggestions by    */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.              */

/* This library is free software under the Artistic license:       */
/* see the file COPYING distributed together with this code.       */
/* For the verification of the code, its output sequence file      */
/* mt19937int.out is attached (2001/4/2)                           */

/* Copyright (C) 1997, 1999 Makoto Matsumoto and Takuji Nishimura. */
/* Any feedback is very welcome. For any question, comments,       */
/* see http://www.math.keio.ac.jp/matumoto/emt.html or email       */
/* matumoto@math.keio.ac.jp                                        */

/* REFERENCE                                                       */
/* M. Matsumoto and T. Nishimura,                                  */
/* "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform  */
/* Pseudo-Random Number Generator",                                */
/* ACM Transactions on Modeling and Computer Simulation,           */
/* Vol. 8, No. 1, January 1998, pp 3--30.                          */


