/* points.cc definitions and basic functions of points	*/

struct point{	//
	int x,y;
};

point cpx_to_point(cpx w){
    point p;
	if(SMALLSCREEN){
	    p.x = (int) 250.0+200.0*w.real();
	    p.y = (int) 250.0-200.0*w.imag();
	} else {
		p.x = (int) 500.0+400.0*w.real();
		p.y = (int) 420.0-400.0*w.imag();
	};
    return(p);
};

cpx circumcenter(cpx u, cpx v, cpx w){
	cpx Z,C;
	Z=(w-u)/(v-u);
	double X,Y,h;
	X=Z.real();
	Y=Z.imag();
	h=(X*X+Y*Y-X)/(2.0*Y);
	C.real()=0.5;
	C.imag()=h;
	C=u+(C*(v-u));
	return(C);
};

cpx invert(cpx u){
	cpx v;
	v=1.0/u;
	v.imag()=-v.imag();
	return(v);
};

