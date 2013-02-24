/*	turtle.cc

	Version 1.2

	Turtle Logo in the hyperbolic plane

	version 1.0 December 15 2012; random walk in hyperbolic plane with prescribed angle and step length
	version 1.1 January 5 2013; added programming mode
	version 1.2 February 23 2013; big clean up. incorporated random programming command

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

#define SMALLSCREEN		0	// for small resolutions, set to 1

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
#include "turtle_class.cc"
#include "input_output.cc"
#include "elementary_program.cc"
#include "recursive_program.cc"
#include "interface.cc"


int main(int argc, char *argv[]){ 
	turtle T;
	ifstream input_file;
	ofstream output_file;
	string R,S = "";
	bool loaded_program;
	char C;
	
	loaded_program=false;
	
	if(argc<=1){
		cout << "Welcome to hyperbolic turtle logo!\n";
		cout << "Usage is as follows.\n";
		cout << "To read a recursive program from a file, enter ./turtle -r filename\n";
		cout << "To read an elementary program from a file, enter ./turtle -e filename\n";
		cout << "To enter an elementary program to cin, enter ./turtle -c\n";
	} else {
		R=argv[1];
		if(R=="-r"){
			if(argc<=2){
				cout << "Usage ./turtle -r filename\n";
			} else {
				S=std::string(argv[2]);
				input_file.open(S.c_str(), std::fstream::in);
				T.initialize();
				T.read_program(input_file);
				input_file.close();
				cout << "Enter depth.\n";
				cin >> T.initial_depth;
				loaded_program=true;
			};
		} else if(R=="-e"){
			if(argc<=2){
				cout << "Usage ./turtle -e filename\n";
			} else {
				S=std::string(argv[2]);
				input_file.open(S.c_str(), std::fstream::in);
				T.initialize();
				T.read_simple_program(input_file);
				input_file.close();		
				T.initial_depth=0;
				loaded_program=true;
			};
		} else if(R=="-c"){
			T.initialize();
			T.enter_program();
			T.initial_depth=0;
			loaded_program=true;
		} else {
			cout << "option unrecognized!\n";
		};
	};
	if(loaded_program==true){
		cout << "echo output to .eps file (y/n): ";
		cin >> C;
		cin.ignore(256, '\n');
		if(C=='y'){
			T.epsout=true;	
		} else {
			T.epsout=false;
		};
 		if(T.epsout){
			T.initialize_eps_output(output_file);
		};
		setup_graphics();
		usleep(100000);
 		draw_circle(cpx_to_point(0.0),400,0);   // draw boundary circle

		T.execute_recursive_program(T.prog, 0, T.initial_depth, output_file);
		if(T.epsout){
			T.close_eps_output(output_file);
		};
		XFlush(display);
		T.user_interface();	
	};
	
	return(0);
};
