// MZA.cc
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file attempts to find the minimum initial number of zombies that are needed to overwhelm the apartment building as outlined in Assignment 5.

#include <iostream>
#include <boost/numeric/odeint.hpp>
#include <rarray>
#include "report.h"

#define B 0.02
#define E 0.015
#define A 0.03
#define C 0.01

using namespace boost::numeric::odeint;
typedef boost::array< double , 3 > state_type;

// void rhs (const double x, double& dxdt , const double t) {
//void rhs ( const rarray<double,1>& x, rarray<double,1>& dxdt , const double t) {
void rhs ( const state_type& x, state_type& dxdt , const double t) {
	double S = x[0];
	double K = x[1];
	double Z = x[2];

	// Equations that define the next state
	dxdt[0] = -B*S*K - E*S*K;
	dxdt[1] = -C*K*Z + E*S*K;
	dxdt[2] =  B*S*Z + C*K*Z - A*K*Z;

	// double S = 10.0;
	// double K = 30.0;
	// double Z = 4.0;
	// dxdt = B*S*Z + C*K*Z - A*K*Z;
}

typedef  runge_kutta_dopri5 < state_type > stepper_type;

int  main() {

	int num_apartment = 500; 			// Total number of people in the apartment building
	int K0 = 9;							// Initial number of zombie killers
	int Z0 = 1;							// Initial number of zombies
	int S0 = num_apartment - K0 - Z0; 	// Initial number of regurlar people
	double initial_time = 0;			// Initial time of the simulation (hours)
	double end_time = 24;				// End time of the simulation (hours)
	double time_step = 1;				// Time step to report (hours)
    //rarray<double,1> x(3);     					// State vector containing [S K Z]
    state_type x;     					// State vector containing [S K Z]

    // double x = 1.0;

    // Initial condition assignment
    x[0] = S0;				
    x[1] = K0;
    x[2] = Z0;

	integrate_adaptive(
		make_controlled (1E-6, 1E-6,  stepper_type ()),
	 	rhs , x, initial_time, end_time, time_step, report_state);

	return 0;
}




