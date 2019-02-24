// report.cc
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the Regular people, Zombie killers, and Zombies 

#include "report.h"
#include <iostream>

// void report_state(const double x, const double t){
void report_state(const rarray<double,1>& x, const double t){

    std::cout << "t = " << t << " S: " << x[0] << " K: " << x[1] << " Z: " << x[2] << std::endl;

    // std::cout << "t = " << t << " Z: " << x << std::endl;
    
}
