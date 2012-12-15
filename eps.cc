/* eps.cc eps output function */

void eps_geodesic(cpx u, cpx v, ofstream &output_file){
	cpx z;
	double r;
	double angle1, angle2;
	double A1, A2, A;
	z=u/v;
	if(abs(z.imag())<0.01 || abs(u-v)<0.01){
		output_file << u.real() << " " << u.imag() << " " << v.real() << " " << v.imag() << " l \n";
	} else {
		z=circumcenter(u,invert(u),v);	
		r=abs(u-z);	// radius
		angle1=arg(u-z);
		angle2=arg(v-z);
		A1=angle1*360.0/TWOPI;
		A2=angle2*360.0/TWOPI;
		A=A2-A1;
		if(A>180.0){
			A=A-360.0;
		};
		if(A<-180.0){
			A=A+360.0;
		};
		if(A>0){
			output_file << z.real() << " " << z.imag() << " " << r << " " << A1 << " " << A2 << " c \n";
		} else {
			output_file << z.real() << " " << z.imag() << " " << r << " " << A2 << " " << A1 << " c \n";
		};
	};
	return;
};

void eps_geodesic_segments(double ANGLE, double LENGTH, int seed){

	ofstream output_file;
	output_file.open("turtle_picture.eps");
	output_file << "%!PS-Adobe-2.0 EPSF-2.0 \n";
	output_file << "%%BoundingBox: 0 0 440 460 \n";
	output_file << "gsave 200 200 scale 1 400 div setlinewidth 1.1 1.2 translate \n";
	output_file << "/l {4 dict begin /y2 exch def /x2 exch def /y1 exch def /x1 exch def \n";
	output_file << "newpath x1 y1 moveto x2 y2 lineto stroke end} def \n";
	output_file << "/c {5 dict begin /a2 exch def /a1 exch def /r exch def /c2 exch def \n";
	output_file << "/c1 exch def newpath c1 c2 r a1 a2 arc stroke end} def \n";
	output_file << "0 0 1 0 360 c \n";	// boundary circle
	
	srand(seed);

	cmat S,R,L,C,D;
	cvec v;
	v.push_back(1.0);
	v.push_back(LENGTH);
	S.push_back(v);
	v[0]=LENGTH;
	v[1]=1.0;
	S.push_back(v);
	R=S;
	R[0][0]=cos(ANGLE)+sin(ANGLE)*I;
	R[0][1]=0.0;
	R[1][0]=0.0;
	R[1][1]=cos(ANGLE)-sin(ANGLE)*I;
	L=R;
	L[0][0]=R[1][1];
	L[1][1]=R[0][0];
	
	int i,j;
	cpx z;
	z=0.0;
	//0.0001+0.0001*I;
	C=R;
	for(i=0;i<10000;i++){
		D=C*S;
		j=rand()%2;
		if(j==0){
			D=D*R;
		} else {
			D=D*L;
		};
		eps_geodesic(mobius(C,z),mobius(D,z),output_file);
		C=D;
		if(1.0-abs(mobius(D,z))<0.001){
			break;
		};
	};
	
	output_file << "/Helvetica findfont \n";
	output_file << "0.075 scalefont setfont \n";
	output_file << "newpath -0.95 -1.12 moveto \n";
	output_file << "( step length " << LENGTH << " turning angle " << ANGLE*2.0 << " random seed " << seed << ") show \n";
	output_file << "grestore %eof \n";
	output_file.close();
};