// MZA.cc
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file attempts to find the minimum initial number of zombies that are needed to overwhelm the apartment building as outlined in Assignment 5.

#include <iostream>
#include <rarray>
#include <boost/numeric/odeint.hpp>
#include "report.h"

#define B 0.02
#define E 0.015
#define A 0.03
#define C 0.01

using namespace boost::numeric::odeint;

void rhs (const rarray<double,1>& current_state, const rarray<double,1>& next_state , const  double t) {
	dxdt = 3.0/(2.0*t*t) + x/(2.0*t);
	double S = current_state[0];
	double K = current_state[0];
	double Z = current_state[0];

	// Equations that define the next state
	next_state[0] = -B*S*K - E*S*K;
	next_state[1] = -C*K*Z + E*S*K;
	next_state[2] =  B*S*Z + C*K*Z - A*K*Z;
}

typedef  runge_kutta_dopri5 <double > stepper_type;

int  main() {

	int num_apartment = 500; 			// Total number of people in the apartment building
	int K0 = 9;							// Initial number of zombie killers
	int Z0 = 1;							// Initial number of zombies
	int S0 = num_apartment - K0 - Z0; 	// Initial number of regurlar people
	double initial_time = 0;			// Initial time of the simulation (hours)
	double end_time = 24;				// End time of the simulation (hours)
	double time_step = 1;				// Time step to report (hours)
    rarray<int,1> current_state(3);     // State vector containing [S K Z]

    // Initial condition assignment
    current_state[0] = S0;				
    current_state[1] = K0;
    current_state[2] = Z0;

	integrate_adaptive(
		make_controlled (1E-6, 1E-6,  stepper_type ()),
	 	rhs , current_state, initial_time, end_time, time_step, report);
}




