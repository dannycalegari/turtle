/* variance.cc */

void compute_variance(double ANGLE, double LENGTH){
	cmat S,R,L,C,D;
	cvec v;
	double det;
	double A, turning_angle, V;
	det=sqrt(1.0-LENGTH*LENGTH);
	v.push_back(1.0/det);
	v.push_back(LENGTH/det);
	S.push_back(v);
	v[0]=LENGTH/det;
	v[1]=1.0/det;
	S.push_back(v);
	R=S;
	R[0][0]=cos(ANGLE)+sin(ANGLE)*I;
	R[0][1]=0.0;
	R[1][0]=0.0;
	R[1][1]=cos(ANGLE)-sin(ANGLE)*I;
	L=R;
	L[0][0]=R[1][1];
	L[1][1]=R[0][0];
	
	int i,j,k;
	cpx z,w;
	
	V=0.0;
	cout << "angle " << ANGLE << " length " << LENGTH << " variance ";
	for(k=0;k<10000;k++){	// number of trials
		z=1.0;
		turning_angle=0.0;
		for(i=0;i<1000;i++){
			j=rand()%2;
			if(j==0){
				w=mobius(S*L,z);
			} else {
				w=mobius(S*R,z);
			};
			w=w/abs(w);
			A=arg(w)-arg(z);
			if(A>PI){
			//	cout << "positive jump ";
			//	cout << "z " << z << " w " << w << " ";
				turning_angle=turning_angle+1.0;
			//	cout << "turning angle " << turning_angle << "\n";
			};
			if(A<-PI){
			//	cout << "negative jump ";
			//	cout << "z " << z << " w " << w << " ";
				turning_angle=turning_angle-1.0;
			//	cout << "turning angle " << turning_angle << "\n";
			};
			z=w;
		};
		V=V+(turning_angle*turning_angle);
	//	cout << turning_angle << " ";
	//	cout.flush();
	};
	V=V/100.0;
	cout << V << "\n";
	cout.flush();
};
