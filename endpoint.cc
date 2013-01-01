/* endpoint.cc */

void compute_endpoint(double ANGLE, double LENGTH, int seed){
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
		C=D;
		if(1.0-abs(mobius(D,z))<0.001){
			break;
		};
	};
	cout << arg(mobius(D,z)) << " ";
	cout.flush();
};