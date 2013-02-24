**turtle** version 1.2; February 23, 2013
=======================================

Turtle logo in the hyperbolic plane (rendered in the Poincare disk model). 
This is a variation on the Logo
programming language, created in 1967 for educational use by Wally Feurzeig and
Seymour Papert, but has a limited set of commands, and a primitive interface.

![random tree](https://raw.github.com/dannycalegari/turtle/master/random_tree.png)

running the program
-------------------

The program can be run with one of three options:

* to read a recursive program from a file, enter ./turtle -r filename
* to read an elementary program from a file, enter ./turtle -e filename
* to enter an elementary program to cin, enter ./turtle -c

elementary program
------------------

An elementary program is a list of commands of the form c i where c is a letter (character)
and i is a number (double or integer). The meaning of the commands is as follows:

* [p] means pen color; i is an RGB color between 0 and 999
* [f] means move forward; i is the step (100 is infinite)
* [r] means rotate; i is the angle (in degrees)
* [l] means start loop; i is the number of iterations
* [c] means close loop; i is ignored (but must be entered!)
* [R] meands random; i is how many subsequent commands to select from
* [e] means end program; i is ignored (but must be entered!)

These options are mostly self-explanatory, with perhaps the following exceptions.

The step size (for option [f]) moves a hyperbolic length L such that 
L=arcosh(1+2/(1-(i/100)<sup>2</sup>)).

The command R i chooses at random one of the next i operations, executes it,
and ignores the rest. So, for example, a snippet like

	R 2
	r 90
	r -90
	
means: rotate either left or right through 90 degrees with equal probability.

recursive program
-----------------

A recursive program is a tuple, consisting of the following:

* a vector of elementary programs
* a vector of vectors of integers options[i][j]
* a vector of vectors of integers transition[i][j]

Although the vectors options[i] may have different length for different i, for each fixed i
the vectors options[i] and transition[i] must have the same length.

If R is a recursive program, it is executed with the command execute_recursive_program(R, T, D)
where T is the type, and D is the depth. This means the following:

* if D is negative, do nothing
* otherwise, 
	* save the location, orientation and pen color; then
	* for each k up to the size of options[T], 
		* execute elementary program number options[T][k]; then
		* execute_recursive_program(R, transition[T][k], D-1); then
	* restore the location, orientation and pen color

This makes it possible to write complicated recursive procedures quite easily.

file format
-----------

A file giving an elementary program has the format of an integer i, followed by a list of
elementary commands. The last command should be e 0. The number of elementary commands should be i.

A file giving a recursive program has the following format:

* an integer v, which is the number of elementary programs
	* for each i up to v, the code of elementary program i in the format above (hence it should start with the number of lines!)
* an integer t, which is the number of types
	* for each i up to t, an integer s which is the size of the vector options[i]
		* for each j up to s, the value of options[i][j]
		* for each j up to s, the value of transition[i][j]
		
Three sample programs _sample\_elementary\_program.txt_, _sample\_recursive\_program.txt_ and _73\_recursive\_program.txt_ are included.

to dos
------
* add the ability to save the graphical output as an .eps file

copyright
---------

This program is released under the terms of the GNU GPL version 3.0. See the
attached license file.

![73 grid](https://raw.github.com/dannycalegari/turtle/master/73_grid.png)
