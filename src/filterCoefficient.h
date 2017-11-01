#ifndef FILTERCOEFFICIENT_H_
#define FILTERCOEFFICIENT_H_

#endif /*FILTERCOEFFICIENT_H_*/

#define TAPS 256

Int16 LP[TAPS] = { 
	#include "lowpass.dat" 
};

Int16 BP[TAPS] = {
	#include "bandpass.dat"
};

Int16 HP[TAPS] = {
	#include "highpass.dat"
};
