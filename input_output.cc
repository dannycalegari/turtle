/* input_ouput.cc */

elementary_program turtle::read_elementary_program(ifstream &input_file){
	elementary_program E;	// E is vector<single_command >
	single_command S;	// S.c is a char, S.i is a double
	int i,v;
	
	E.resize(0);
	input_file >> v;	// length of program
	for(i=0;i<v;i++){
		input_file >> S.c;	// read char
		input_file >> S.i;	// read double
		E.push_back(S);
	};
	
	return(E);
};

void turtle::read_simple_program(ifstream &input_file){	
	// encodes elementary program as recursive program with 1 type and 1 option

	elementary_program E;
	
	vector<int > I;
	
	prog.subprogram.resize(0);
	prog.options.resize(0);
	prog.transition.resize(0);

	E = read_elementary_program(input_file);	
	prog.subprogram.push_back(E);
	I.resize(0);
	I.push_back(0);
	prog.options.push_back(I);
	prog.transition.push_back(I);
};

void turtle::read_program(ifstream &input_file){
	int number_of_subprograms, number_of_types;
	int i,j,k,v;
	elementary_program E;
	
	vector<int > I;
	
	prog.subprogram.resize(0);
	prog.options.resize(0);
	prog.transition.resize(0);
	
	input_file >> number_of_subprograms;
	for(i=0;i<number_of_subprograms;i++){
		E = read_elementary_program(input_file);	
		prog.subprogram.push_back(E);
	};
	input_file >> number_of_types;
	for(i=0;i<number_of_types;i++){
		I.resize(0);
		input_file >> v;
		for(j=0;j<v;j++){
			input_file >> k;
			I.push_back(k);
		};
		prog.options.push_back(I);
		I.resize(0);
		for(j=0;j<v;j++){
			input_file >> k;
			I.push_back(k);
		};
		prog.transition.push_back(I);
	};
};

void turtle::enter_program(){	
	// can enter elementary program through cin; encoded as prog

	elementary_program E;	
	single_command S;	
	
	vector<int > I;	
	prog.subprogram.resize(0);
	prog.options.resize(0);
	prog.transition.resize(0);
	I.resize(0);
	I.push_back(0);
	prog.options.push_back(I);
	prog.transition.push_back(I);
	
	cout << "An elementary turtle program is a list of commands of the form c i\n";
	cout << "where c is a letter and i is a number.\n";
	cout << "[p] means pen color; i is an RGB color between -1 and 999 (-1 is penup)\n";
	cout << "[f] means move forward; i is the step (100 is infinite)\n";
	cout << "[r] means rotate; i is the angle (in degrees)\n";
	cout << "[l] means start loop; i is the number of iterations\n";
	cout << "[c] means close loop; i is ignored (but must be entered!)\n";
	cout << "[R] meands random; i is how many subsequent commands to select from\n";
	cout << "[e] means end program; i is ignored (but must be entered!)\n";
	E.resize(0);
	char c;
	int i;
	double t;
	bool finish;
	finish=false;
	i=0;
	while(finish==false){
		cout << i << "    ";
		cin >> c >> t;
		S.c = c;
		S.i = t;
		E.push_back(S);
		if(S.c=='e'){
			finish=true;
		};
		i++;
	};

	prog.subprogram.push_back(E);
};


void turtle::write_program(){
	// writes the contents of prog to cout
	
	int i,j;
	
	cout << "number of elementary subprograms " << (int) prog.subprogram.size() << "\n";
	for(i=0;i<(int) prog.subprogram.size();i++){
		cout << "elementary subprogram " << i << "\n";
		for(j=0;j<(int) prog.subprogram[i].size();j++){
			cout << "  " << prog.subprogram[i][j].c << " " << prog.subprogram[i][j].i << "\n";
		};
	};
	cout << "number of types " << (int) prog.options.size() << "\n";
	for(i=0;i<(int) prog.options.size();i++){
		for(j=0;j<(int) prog.options[i].size();j++){
			cout << "  option[" << i << "][" << j << "] is " << prog.options[i][j] << "\n";
		};
	};
	for(i=0;i<(int) prog.transition.size();i++){
		for(j=0;j<(int) prog.transition[i].size();j++){
			cout << "  transition[" << i << "][" << j << "] is " << prog.transition[i][j] << "\n";
		};
	};
};