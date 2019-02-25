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
#define FILENAME "MZA.nc"
#define STATE_LENGTH 4
#define INITIAL_Z0 1.0

using namespace boost::numeric::odeint;

typedef boost::array<double,STATE_LENGTH> state_type;
typedef runge_kutta_dopri5 < state_type > stepper_type;

// Function that computes the right hand side of the ODEs for the stepper
void rhs ( const state_type& x, state_type& dxdt , const double t) {
	// Extract the current state variables so they're easier to read 
	double S = x[0];
	double K = x[1];
	double Z = x[2];

	// Equations that define the next state
	dxdt[0] = -B*S*Z - E*S*K;
	dxdt[1] = -C*K*Z + E*S*K;
	dxdt[2] =  B*S*Z + C*K*Z - A*K*Z;
}

void observer(const state_type& x, const double t){
    rarray<double,1> x_rarray(STATE_LENGTH); // array to pass to the netCDF writer with the current state

    // Store the current state in an rarray to send to the netCDF writer
    x_rarray[0] = x[0];
    x_rarray[1] = x[1];
    x_rarray[2] = x[2];
    x_rarray[3] = x[3];

    // Write the current state in a netCDF file
    report_state(x_rarray, FILENAME, STATE_LENGTH-1, t, INITIAL_Z0); 
}

int  main() {

	int num_apartment = 500; 			// Total number of people in the apartment building
	double K0 = 9;						// Initial number of zombie killers
	double Z0 = 0;						// Initial number of zombies
	double S0 = 0;						// Initial number of regular people
	double initial_time = 0;			// Initial time of the simulation (I'm pretending the units are hours)
	double end_time = 24;				// End time of the simulation (hours)
	double time_step = 1;				// Time step to report (hours)
    state_type x;     					// State vector containing [S K Z Z0]

    

    // Loop through different initial zombie populations to find the one that lets
    // the zombies win. Once you've found that critical population, exit the program.
    for (Z0=INITIAL_Z0; x[2]<1.0; Z0++){
		S0 = num_apartment - K0 - Z0; 	// Initial number of regular people
	    
	    // Initial condition assignment into the state variable
	    x[0] = S0;						// Initial number of regular people
	    x[1] = K0;						// Initial number of zombie killers
	    x[2] = Z0;						// Initial number of zombies
	    x[3] = Z0;						// Keeps track of the initial condition set for this simulation

		std::cout << "Initial state: S: " << x[0] << " K: " << x[1] << " Z: " << x[2] << std::endl;  

	    // Simulate 24 "hours" to see if the zombies or the humans survive (population > 1)
		integrate_adaptive(
			make_controlled (1E-6, 1E-6,  stepper_type ()),
		 	rhs , x, initial_time, end_time, time_step, observer);

		// After one day there are still surviving zombies and people so we need to simulate more days until 
		// we have a winner (only one type of population left)
		while((x[0] > 1.0 || x[1] > 1.0) && (x[2] > 1.0)){
			std::cout << "Simulating another day ... " << x[0] << " " << x[1] << " "  << x[2] << std::endl;
			integrate_adaptive(
			make_controlled (1E-6, 1E-6,  stepper_type ()),
		 	rhs , x, initial_time, end_time, time_step, observer);
		}

		std::cout << "Final state: " << " S: " << x[0] << " K: " << x[1] << " Z: " << x[2] << std::endl; 

		if((x[0] > 1.0 || x[1] > 1.0))
			std::cout << "Humans win!!" << std::endl;
		else
			std::cout << "Zombies win :'(" << std::endl;

		std::cout << "--------------------------------------" << std::endl;
	}

	// Decrement Z0 to get the actual last value used because the for loop automatically increments it
	Z0--;
	// Report final results
	std::cout << std::endl << "Final Result: If the initial Zombie population is greater than or equal to " << Z0 << " zombies, no one in the apartment building will survive!" << std::endl;

	return 0;
}




