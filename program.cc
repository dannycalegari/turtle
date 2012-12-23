/* program.cc */

void draw_grid(int type, int depth, double angle, double length, cmat C){
	cmat S,R,L,D;
	cvec v;
	v.push_back(1.0);
	v.push_back(length);
	S.push_back(v);
	v[0]=length;
	v[1]=1.0;
	S.push_back(v);
	R=S;
	R[0][0]=cos(angle/2.0)+sin(angle/2.0)*I;
	R[0][1]=0.0;
	R[1][0]=0.0;
	R[1][1]=cos(angle/2.0)-sin(angle/2.0)*I;
	L=R;
	L[0][0]=R[1][1];
	L[1][1]=R[0][0];
	cpx z;
	z=0.0;
	int i;
	
	D=C;
	if(depth>=0){
		if(type==0){	// type 0
			for(i=0;i<7;i++){
				D=D*L*L;
				geodesic(mobius(C,z),mobius(D*S,z));
				draw_grid(1, depth-1, angle, length, D*S);
			};
		};
		if(type==1){	// type 1
			geodesic(mobius(C,z),mobius(C*L*S,z));
			geodesic(mobius(C,z),mobius(C*L*L*L*S,z));
			geodesic(mobius(C,z),mobius(C*L*L*L*L*L*S,z));
			geodesic(mobius(C,z),mobius(C*R*S,z));
			geodesic(mobius(C,z),mobius(C*R*R*R*S,z));			
			draw_grid(1, depth-1, angle, length, C*L*S);
			draw_grid(1, depth-1, angle, length, C*R*S);
			draw_grid(2, depth-2, angle, length, C*R*R*R*S);
		};
		if(type==2){	// type 2
			geodesic(mobius(C,z),mobius(C*L*S,z));
			geodesic(mobius(C,z),mobius(C*R*S,z));
			geodesic(mobius(C,z),mobius(C*L*L*L*S,z));
			geodesic(mobius(C,z),mobius(C*L*L*L*L*L*S,z));
			draw_grid(1, depth-1, angle, length, C*L*S);	
			draw_grid(2, depth-1, angle, length, C*R*S);			
		};		
	};
};