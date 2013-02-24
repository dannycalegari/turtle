/* turtle_class.cc */

struct single_command{
	char c;		// type of command
	double i;		// value of command
	/* each command has two parts, a *type* and a *value*. the list of types is:
	
		p: pen color; value: 0-999 RGB color value. Each of R,G,B is from 0 to 9. First
		digit is R, second digit is G, third digit is B.
		
		f: more forward some distance; value: how far to move, in units 
		where hyperbolic length is tanh^{-1}(i/100)
		
		r: rotate through some angle; value: angle to turn, specified in degrees	
		
		e: eof - signals end of program; value: irrelevant
		
		l: loop open; value: number of times to execute the loop
		
		c: loop close; value: irrelevant
		
		R: random operation; value: number of options. One of the subsequent i commands is
		chosen at random to be executed, and the other (i-1) commands are skipped. Useful in loops.
	
	*/
};

#define elementary_program 	vector<single_command >	
	// vector of turtle commands
	
struct recursive_program{
	vector<elementary_program > subprogram;	// vector of elementary programs
	vector<vector<int> > options;	// which subprogram to execute it which order?
	vector<vector<int> > transition; // which state to transition to after executing it?
};


class turtle{
	public:
		// data defining state of turtle, program to execute, etc.
		recursive_program	prog;
		bool				verbose;
		bool				epsout;
		cmat				state;
		long				pen_color;
		int					initial_depth;
		
		// default initial values
		
		void initialize();
				
		// functions to execute program or recursive program
		
		void execute_elementary_program(elementary_program P, ofstream &output_file);
		void execute_recursive_program(recursive_program R, int type, int depth, ofstream &output_file);
		
		// input
		
		elementary_program read_elementary_program(ifstream &input_file);
		void read_program(ifstream &input_file);
		void read_simple_program(ifstream &input_file);
		void enter_program();

		// output 
		
		void write_program();
		void initialize_eps_output(ofstream &output_file);
		void close_eps_output(ofstream &output_file);
		
		// interface
		
		void user_interface();
};

void turtle::initialize(){
	verbose=false;
	state=turn_mat(PI/2.0);
	pen_color=0;
};

void turtle::initialize_eps_output(ofstream &output_file){
	string S;
	cin.clear();
	cout << "Enter name of file to write .eps output to: ";
	cin.clear();

	getline(cin, S, '\n');
	if(S.length()<3){
		S="output.eps";
	};
	output_file.open(S.c_str());
    output_file << "%!PS-Adobe-2.0 EPSF-2.0 \n";
    output_file << "%%BoundingBox: 0 0 500 500 \n";
   	output_file << "gsave \n";
    output_file << "200 200 scale \n";
    output_file << "1 400 div setlinewidth \n";
    output_file << "1.25 1.25 translate \n";
	output_file << "/l {7 dict begin \n";
	output_file << "	/c3 exch def \n";
	output_file << "	/c2 exch def \n";
	output_file << "	/c1 exch def \n";
	output_file << "	/y2 exch def \n";
	output_file << "	/x2 exch def \n";
	output_file << "	/y1 exch def \n";
	output_file << "	/x1 exch def \n";
	output_file << "	gsave \n";
	output_file << "	c1 c2 c3 setrgbcolor \n";
	output_file << "	newpath \n";
	output_file << "	x1 y1 moveto \n";
	output_file << "	x2 y2 lineto \n";
	output_file << "	stroke \n";
	output_file << "	grestore \n";
	output_file << "end} def\n";
	output_file << "/c {8 dict begin \n";
	output_file << "	/c3 exch def \n";
	output_file << "	/c2 exch def \n";
	output_file << "	/c1 exch def \n";
	output_file << "	/a2 exch def \n";
	output_file << "	/a1 exch def \n";
	output_file << "	/r exch def \n";
	output_file << "	/y exch def \n";
	output_file << "	/x exch def \n";
	output_file << "	gsave \n";
	output_file << "	c1 c2 c3 setrgbcolor \n";
	output_file << "	newpath \n";
	output_file << "	x y r a1 a2 arc \n";
	output_file << "	stroke \n";
	output_file << "	grestore \n";
	output_file << "end} def\n";
	output_file << "0 0 1 0 360 0 0 0 c \n";
};

void turtle::close_eps_output(ofstream &output_file){
	output_file << "grestore \n";
	output_file << "%eof \n";
	output_file.close();
};
