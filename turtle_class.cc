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
		cmat				state;
		long				pen_color;
		int					initial_depth;
		
		// default initial values
		
		void initialize();
				
		// functions to execute program or recursive program
		
		void execute_elementary_program(elementary_program P);
		void execute_recursive_program(recursive_program R, int type, int depth);
		
		// input
		
		elementary_program read_elementary_program(ifstream &input_file);
		void read_program(ifstream &input_file);
		void read_simple_program(ifstream &input_file);
		void enter_program();

		// output 
		
		void write_program();
		void draw_eps();
		
		// interface
		
		void user_interface();
};

void turtle::initialize(){
	verbose=false;
	state=turn_mat(PI/2.0);
	pen_color=0;
};
