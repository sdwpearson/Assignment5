// report.h
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the time, Regular people, Zombie killers, and Zombies in
// a netCDF file. On the first iteration it creates the file and on subsequent ones it appends to the existing
// file. For each different value of Z0 it will create a new variable.


#ifndef REPORTH
#define REPORTH

#include <rarray>

void report_state(const rarray<double,1>& x,  const char* filename, int length, const double t, const double INITIAL_Z0);

#endif