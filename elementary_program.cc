/* elementary_program.cc function to execute an elementary program */

int end_loop_location(elementary_program T, int start_loop_location){
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

void turtle::execute_elementary_program(elementary_program P){
	elementary_program Q;
	cpx z;
	z=0.0;	// could specify initial position if I like, I suppose
	
	cmat new_state;	
	/* state is a matrix which acts on the complex number z by a Mobius
	transformation to give the location and orientation of the turtle */
	
	int instruction;	// current instruction pointer
	instruction=0;	// initially points to the first instruction of T
	
	int j,k,color;
	double distance, angle;
	
	ivec loop_counter;	// list of how many times we have executed each loop
	if(verbose){
		cout << "Executing elementary program. \n";
	};
	
	while(instruction<(int) P.size()){
		if(verbose){
			cout << "executing instruction " << instruction << ";   " << P[instruction].c << " " << P[instruction].i << "\n";
			cout.flush();
		};
		switch(P[instruction].c){
			case 'p':
				color=(int) P[instruction].i;	// integer from 0 to 999
				pen_color=(long) (26*(color%10))+(26*256*((color/10)%10))+(26*256*256*((color/100)%10));
				break;
			case 'f':
				distance = P[instruction].i/100.0;
				new_state=state*forward_mat(distance);
				color_geodesic(mobius(state,z),mobius(new_state,z), pen_color);
				state=new_state;
				break;
			case 'r':
				angle = TWOPI*P[instruction].i/360.0;
				new_state=state*turn_mat(angle);
		//		color_geodesic(mobius(turtle_state,z),mobius(new_state,z), pen_color);
				state=new_state;
				break;
			case 'l':
				j=end_loop_location(P,instruction);
				if(verbose){
					cout << "loop starting at " << instruction << " ends at " << j << "\n";
					cout.flush();
				};
				Q.clear();	// initialize Q
				for(k=instruction+1;k<j;k++){	// set Q to be the subset of P inside the loop
					Q.push_back(P[k]);
				};
				for(k=0;k<P[instruction].i;k++){	// P[instruction].i is the number of times to execute the loop
					execute_elementary_program(Q);	// execute the content of the loop
				};
				instruction=j;
				break;
			case 'R':
				j=(int) P[instruction].i;	// number of subsequent instructions to choose from
				k=rand()%j;	// which instruction shall we execute?
				Q.clear();	// initialize Q
				Q.push_back(P[instruction+1+k]);
				execute_elementary_program(Q);	// execute random instruction
				instruction=instruction+j;
				break;
			default:
				break;
		};
		instruction++;
	};
	if(verbose){
		cout << "Program executed.\n";
		cout.flush();
	};
	return;
};