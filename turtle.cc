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
#include "endpoint.cc"
#include "program.cc"

int main(int argc, char *argv[]){ 
	double ANGLE, LENGTH;
	int seed;
	
	/*	
	int i;
	LENGTH=0.125;
	ANGLE=0.0;
	cout << "[ ";
	for(i=0;i<=4000;i++){
		compute_endpoint(ANGLE, LENGTH, 17);
		ANGLE=ANGLE+PI/4000.0;
	};
	cout << "]\n";
	*/
	
	/*
	int i,j;
	LENGTH=0.0;
	for(i=0;i<=40;i++){
		cout << "[ ";
		ANGLE=0.0;
		for(j=0;j<=40;j++){
			compute_variance(ANGLE, LENGTH);
			ANGLE=ANGLE+PI/160.0;
		};
		cout << " ]";
		LENGTH=LENGTH+0.00625;
	};
	*/
	
	if(argc==1){
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
//		horocycle(ANGLE);
//		eps_horocycle(ANGLE);
		geodesic_segments(ANGLE,LENGTH,seed);

		XFlush(display);
		while(1){
			user_interface(ANGLE,LENGTH,seed);
		};
	} else {
		cmat S;
		cvec v;
		v.push_back(1.0);
		v.push_back(0.0);
		S.push_back(v);
		v[0]=0.0;
		v[1]=1.0;
		S.push_back(v);
	
		ofstream output_file;
		output_file.open("7-3.eps");
		output_file << "%!PS-Adobe-2.0 EPSF-2.0 \n";
		output_file << "%%BoundingBox: 0 0 440 440 \n";
		output_file << "gsave 200 200 scale 1 400 div setlinewidth 1.1 1.1 translate \n";
		output_file << "/l {4 dict begin /y2 exch def /x2 exch def /y1 exch def /x1 exch def \n";
		output_file << "newpath x1 y1 moveto x2 y2 lineto stroke end} def \n";
		output_file << "/c {5 dict begin /a2 exch def /a1 exch def /r exch def /c2 exch def \n";
		output_file << "/c1 exch def newpath c1 c2 r a1 a2 arc stroke end} def \n";
		output_file << "0 0 1 0 360 c \n";	// boundary circle
	
	
		setup_graphics();
		draw_grid(0, 7, PI/7.0, 0.5, S, output_file);
		draw_extra_lines(PI/7.0, 0.5, S, output_file);
	
		output_file << "grestore %eof \n";
		output_file.close();

		XFlush(display);
		while(1){
		};
	};
	
	return(0);
};
