/*	turtle.cc

	Version 1.1

	Turtle Logo in the hyperbolic plane

	January 5 2013

	Copyright Danny Calegari

	released under the terms of the GNU GPL, version 3.0
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
#define ivec	vector<int >	// vector of integers
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
#include "endpoint.cc"
#include "draw_grid.cc"
#include "program.cc"

int main(int argc, char *argv[]){ 
	double ANGLE, LENGTH;
	int seed;
	
	if(argc==1){
		cout << "Type turtle -r for random mode, turtle -p for programming mode.\n";
	} else {
		if(strcmp(argv[1],"-r")==0){	// random mode 
			cout << "Welcome to hyperbolic turtles!\n";
			cout << "I will draw a random turtle trajectory.\n";
			cout << "Enter initial step length (1.0 is infinite): ";
			cin >> LENGTH;
			cout << "Enter initial turning angle (in radians): ";
			cin >> ANGLE;
			cout << "Enter initial seed (an integer): ";
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
		} else {	// programming mode; (default)
			turtle_program T;
			long pen_color;
			
			cmat turtle_state;
			turtle_state=forward_mat(0.0);
			pen_color=0;
		
			cout << "Welcome to hyperbolic turtles!\n";
			cout << "Enter turtle program.\n";
			input_program(T);
			cout << "Now executing program.\n";
			cout << "Press [q] to quit.\n";
		
			setup_graphics();
		
			draw_circle(cpx_to_point(0.0),400,0);	// boundary circle
			execute_program(T,turtle_state,pen_color);
			XFlush(display);
			while(1){
				program_user_interface();
			};
		};
	};
	
	return(0);
};
