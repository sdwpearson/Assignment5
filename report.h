// report.h
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the Regular people, Zombie killers, and Zombies 


#ifndef REPORTH
#define REPORTH

#include <rarray>

// records the current state in a netCDF File
//
void report_state(const rarray<double,1>& x,  const char* filename, int length, const double t, const double INITIAL_Z0);

#endif