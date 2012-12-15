/*	turtle.cc	

	Random turtles in the hyperbolic plane

	December 15 2012

	Copyright Danny Calegari

	released under the terms of the GNU GPL
	
*/

// standard libraries to include

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>
#include <complex>

using namespace std;

// preprocessor definitions

#define PI 		3.14159265358979
#define TWOPI	6.28318530717959
#define cpx		complex<double>				// complex number
#define cvec 	vector<cpx >	// vector of complex numbers
#define cmat	vector< vector<cpx > >		// matrix of complex

// global constants

cpx I (0.0,1.0);

#include "matrix.cc"
#include "points.cc"
#include "graphics.cc"
#include "draw.cc"
#include "eps.cc"
#include "interface.cc"

int main(int argc, char *argv[]){ 
	double ANGLE, LENGTH;
	int seed;
	ANGLE=0.6;
	LENGTH=0.05;
	
	cout << "Welcome to hyperbolic turtles!\n";
	cout << "Initial step length is " << LENGTH << "\n";
	cout << "Initial turning angle is " << ANGLE*2.0 << "\n";
	cout << "Enter initial seed: ";
	cin >> seed;
	cout << "Starting graphics.\n";
	cout << "Use arrow keys to adjust length and angle.\n";
	cout << "Press [s] to increment random seed.\n";
	cout << "Press [e] to output to .eps file.\n";
	cout << "Press [q] to quit.\n";
	
	setup_graphics();
	geodesic_segments(ANGLE,LENGTH,seed);

	XFlush(display);
	while(1){
		user_interface(ANGLE,LENGTH,seed);
	};
	
	return(0);
};
