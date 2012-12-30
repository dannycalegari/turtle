/* draw.cc drawing routines */

void geodesic(cpx u, cpx v){
	cpx z;
	double r;
	double angle1, angle2;
	int R,A1,A2,A;
	z=u/v;
	if(abs(z.imag())<0.01 || abs(u-v)<0.01){
		draw_line(cpx_to_point(u),cpx_to_point(v),10000000);
		draw_dot(cpx_to_point(u),0);
		draw_dot(cpx_to_point(v),0);
	} else {
		z=circumcenter(u,invert(u),v);	
		draw_dot(cpx_to_point(u),0);
		draw_dot(cpx_to_point(v),0);
		r=abs(u-z);	// radius
		R=(int) (r*400.0);
		angle1=arg(u-z);
		angle2=arg(v-z);
		A1=(int) (angle1*23040.0/TWOPI);
		A2=(int) (angle2*23040.0/TWOPI);
		A=A2-A1;
		while(A<0){
			A=A+23040;
		};
		A=A%23040;
		if(A>11520){
			draw_arc(cpx_to_point(z),R,A2,23040-A,10000000);
		} else {
			draw_arc(cpx_to_point(z),R,A1,A,10000000);
		};
	};
	return;
};

void red_geodesic(cpx u, cpx v){
	cpx z;
	double r;
	double angle1, angle2;
	int R,A1,A2,A;
	z=u/v;
	if(abs(z.imag())<0.01 || abs(u-v)<0.01 || abs(v)<0.01){
		draw_line(cpx_to_point(u),cpx_to_point(v),16711680);
		draw_dot(cpx_to_point(u),0);
		draw_dot(cpx_to_point(v),0);
	} else {
		z=circumcenter(u,invert(u),v);	
		draw_dot(cpx_to_point(u),0);
		draw_dot(cpx_to_point(v),0);
		r=abs(u-z);	// radius
		R=(int) (r*400.0);
		angle1=arg(u-z);
		angle2=arg(v-z);
		A1=(int) (angle1*23040.0/TWOPI);
		A2=(int) (angle2*23040.0/TWOPI);
		A=A2-A1;
		while(A<0){
			A=A+23040;
		};
		A=A%23040;
		if(A>11520){
			draw_arc(cpx_to_point(z),R,A2,23040-A,16711680);
		} else {
			draw_arc(cpx_to_point(z),R,A1,A,16711680);
		};
	};
	return;
};

void geodesic_segments(double ANGLE, double LENGTH, int seed){

	draw_circle(cpx_to_point(0.0),400,0);	// boundary circle
	
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
	R[0][0]=cos(ANGLE/2.0)+sin(ANGLE/2.0)*I;
	R[0][1]=0.0;
	R[1][0]=0.0;
	R[1][1]=cos(ANGLE/2.0)-sin(ANGLE/2.0)*I;
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
		geodesic(mobius(C,z),mobius(D,z));
		C=D;
		if(1.0-abs(mobius(D,z))<0.001){
			break;
		};
	};
};

void horocycle(double ANGLE){
	draw_circle(cpx_to_point(0.0),400,0);	// boundary circle
	double LENGTH;
	LENGTH=sin(ANGLE/2.0);
	
	cmat S,R,L,C,D;
	cvec v;
	v.push_back(1.0);
	v.push_back(LENGTH);
	S.push_back(v);
	v[0]=LENGTH;
	v[1]=1.0;
	S.push_back(v);
	R=S;
	R[0][0]=cos(ANGLE/2.0)+sin(ANGLE/2.0)*I;
	R[0][1]=0.0;
	R[1][0]=0.0;
	R[1][1]=cos(ANGLE/2.0)-sin(ANGLE/2.0)*I;
	L=R;
	L[0][0]=R[1][1];
	L[1][1]=R[0][0];
	
	int i;
	cpx z;
	z=0.0;
	//0.0001+0.0001*I;
	C=R;
	for(i=0;i<10000;i++){
		D=C*S;
		D=D*R;
		geodesic(mobius(C,z),mobius(D,z));
		C=D;
		if(1.0-abs(mobius(D,z))<0.001){
			break;
		};
	};
};