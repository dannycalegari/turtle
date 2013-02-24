/* recursive_program.cc */

void turtle::execute_recursive_program(recursive_program R, int type, int depth, ofstream &output_file){
	int k;
	cmat save_state;
	long save_pen_color;
	
	if(verbose){
		cout << "Executing recursive program in type " << type << " at depth " << depth << "\n";
		cout.flush();
	};
	
	if(depth>=0){
		for(k=0;k<(int) R.options[type].size();k++){
			save_state=state;			// save current state and pen color
			save_pen_color=pen_color;
			if(verbose){
				cout << "Executing elementary subprogram " << R.options[type][k] << "\n";
			};
			execute_elementary_program(R.subprogram[R.options[type][k]], output_file);
			execute_recursive_program(R,R.transition[type][k],depth-1, output_file);
			state=save_state;			// restore state and pen color
			pen_color=save_pen_color;
		};
	};
};
