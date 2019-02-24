// report.h
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the Regular people, Zombie killers, and Zombies 


#ifndef REPORTH
#define REPORTH

#include <rarray>
typedef boost::array< double , 3 > state_type;

// Prints the current state of the Regular people, Zombie killers, and Zombies to the terminal
//
// void report_state(const double x, const double t);
// void report_state(const rarray<double,1>& x, const double t);
void report_state(const state_type& x, const double t);

#endif