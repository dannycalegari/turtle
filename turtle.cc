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
#include "variance.cc"
#include "program.cc"

int main(int argc, char *argv[]){ 
	double ANGLE, LENGTH;
	int seed;
	
/*
	
	cout << "Welcome to hyperbolic turtles!\n";
	cout << "Enter initial step length: ";
	cin >> LENGTH;
	cout << "Enter initial turning angle: ";
	cin >> ANGLE;
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
	
*/
	cmat S;
	cvec v;
	v.push_back(1.0);
	v.push_back(0.0);
	S.push_back(v);
	v[0]=0.0;
	v[1]=1.0;
	S.push_back(v);
	
	setup_graphics();
	draw_grid(0, 10, PI/7.0, 0.5, S);

	XFlush(display);
	while(1){
	};
	
	return(0);
};
