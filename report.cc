// report.cc
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the Regular people, Zombie killers, and Zombies 

#include "report.h"
#include <iostream>

int report_state(const rarray<double,1>& current_state, const double t);
{
    std::cout << 't = ' << t << 'S: ' << current_state[0] << ' K: ' << current_state[1] << ' Z: ' << current_state[2] << std::endl;
    
    // Success, return 1
    return 1;
}
