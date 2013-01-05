**turtle** version 1.1; January 5, 2013
=======================================

Turtle logo in the hyperbolic plane. This is an obvious variation on the Logo
programming language, created in 1967 for educational use by Wally Feurzeig and
Seymour Papert, but has a much more limited set of commands, and a very
primitive interface.

This program has two modes; *random mode* and *programming mode*.


random mode
-----------

To launch in random mode, type ./turtle -r

In random mode, the turtle draws a random trajectory in the hyperbolic plane,
alternating between taking a step of some fixed length, and turning left or
right (with equal probability) through some fixed angle. The length/angle
and the random seed can be entered at launch, and adjusted interactively
after the trajectory is calculated and drawn. The image can be saved as an
.eps file by pressing [e].


programming mode
----------------

To launch in programming mode, type ./turtle -p

In programming mode, the programmer enters a list of commands of the form c i
where c is a letter (character) and i is a number (integer). The meaning of
the commands is as follows:

* [p] means pen color; i (0-7) is the RGB color value
* [f] means forward; i is the step size (100 is "infinite")
* [r] means rotate; i is the angle (in degrees)
* [l] means start loop; i is the number of iterations
* [c] means close loop; i is ignored
* [e] means end program; i is ignored

After entering the program (i.e. after entering the command "e 0") the
turtle's trajectory is calculated and drawn. (to do: allow the ability to
save as an .eps file)


copyright
---------

This program is released under the terms of the GNU GPL version 3.0. See the
attached license file.
