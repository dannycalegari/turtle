/* program.cc */

struct turtle_command{
	char c;		// type of command
	int i;		// value of command
	/* each command has two parts, a *type* and a *value*. the list of types is:
		p: pen; value: 0-7 RGB color value
		f: forward; value: how far, in units where hyperbolic length is tanh^{-1}(i/100)
		r: rotate; value: degrees	
		e: eof; value: irrelevant
		l: loop open; value: number of executions
		c: loop close; value: irrelevant
	*/
};

#define turtle_program 	vector<turtle_command >	// vector of turtle commands

void input_program(turtle_program &T){
	cout << "A turtle program is a list of commands of the form c i\n";
	cout << "where c is a letter and i is a number (an integer)\n";
	cout << "[p] means pen color; i is the RGB color value.\n";
	cout << "[f] means forward; i is the step (measured at the origin).\n";
	cout << "[r] means rotate; i is the angle (in degrees).\n";
	cout << "[l] means start loop; i is the number of iterations.\n";
	cout << "[c] means close loop; i is ignored.\n";
	cout << "[e] means end program; i is ignored.\n\n";
	T.clear();	// should initialize T
	turtle_command N;
	char c;
	int i;
	bool finish;
	finish=false;
	while(finish==false){
		cin >> c >> i;
		N.c=c;
		N.i=i;
		T.push_back(N);
		if(N.c=='e'){
			finish=true;
		};
	};
	return;
};

int end_loop_location(turtle_program T, int start_loop_location){
	/* finds the instruction that ends the loop that starts at start_loop_location */
//	cout << "looking for end of loop that starts at location " << start_loop_location << "\n";
//	cout.flush();
	int loop_counter,j;
	if(T[start_loop_location].c!='l'){	// if we don't start at a loop
		cout << "we didn't start at a loop!!\n";
		cout.flush();
		return(-1);	// error
	} else {
		loop_counter=1;
		j=start_loop_location;
		while(loop_counter>0){
			j++;
			if(T[j].c=='l'){	//
				loop_counter++;
			};
			if(T[j].c=='c'){
				loop_counter--;
			};
		};
		return(j);
	};
};

void execute_program(turtle_program T, cmat &turtle_state, long &pen_color){
	turtle_program S;
//	long pen_color;
	cpx z;
	z=0.0;	// could specify initial position if I like, I suppose
	
//	cmat turtle_state,
	cmat new_state;	
	/* turtle_state is a matrix which acts on the complex number z by a Mobius
	transformation to give the location and orientation of the turtle */
//	turtle_state=forward_mat(0.0);	// initial turtle_state is identity
	
	int instruction,j,k;	// current instruction pointer
	instruction=0;	// initially points to the first instruction of T
	
	ivec loop_counter;	// list of how many times we have executed each loop
	
//	cout << "Executing instructions!\n";

	while(instruction<(int) T.size()){
//		cout << "executing instruction " << instruction << ";   " << T[instruction].c << " " << T[instruction].i << "\n";
//		cout.flush();
		switch(T[instruction].c){
			case 'p':
				pen_color=(255*(T[instruction].i%2))+(255*256*(((T[instruction].i)/2)%2))+(255*256*256*(((T[instruction].i)/4)%2));
				break;
			case 'f':
				new_state=turtle_state*forward_mat(((double) T[instruction].i)/100.0);
				color_geodesic(mobius(turtle_state,z),mobius(new_state,z), pen_color);
				turtle_state=new_state;
				break;
			case 'r':
				new_state=turtle_state*turn_mat(TWOPI*((double) T[instruction].i)/360.0);
		//		color_geodesic(mobius(turtle_state,z),mobius(new_state,z), pen_color);
				turtle_state=new_state;
				break;
			case 'l':
				j=end_loop_location(T,instruction);
//				cout << "loop starting at " << instruction << " ends at " << j << "\n";
//				cout.flush();
				S.clear();	// initialize S
				for(k=instruction+1;k<j;k++){	// set S to be the subset of T inside the loop
					S.push_back(T[k]);
				};
				for(k=0;k<T[instruction].i;k++){	// T[instruction].i is the number of times to execute the loop
					execute_program(S,turtle_state,pen_color);	// execute the content of the loop
				};
				instruction=j+1;
				break;
			default:
				break;
		};
		instruction++;
	};
//	cout << "Program executed.\n";
//	cout.flush();
	return;
};