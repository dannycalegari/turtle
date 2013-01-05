/* matrix.cc Mobius transformations and so on */

cpx mobius(cmat M, cpx z){
	return((M[0][0]*z+M[0][1])/(M[1][0]*z+M[1][1]));
};

cmat operator*(cmat M, cmat N){
	cmat O;
	O=M;
	int i,j,k;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			O[i][j]=0;
			for(k=0;k<2;k++){
				O[i][j]=O[i][j]+M[i][k]*N[k][j];
			};
		};
	};
	return(O);
};

cmat forward_mat(double length){
	cmat F;
	cvec v;
	// should initialize F and v
	v.push_back(1.0);
	v.push_back(length);
	F.push_back(v);
	v[0]=length;
	v[1]=1.0;
	F.push_back(v);
	return(F);
};

cmat turn_mat(double angle){
	cmat T;
	cvec v;
	// should initialize T and v
	v.push_back(cos(angle/2.0)+sin(angle/2.0)*I);
	v.push_back(0.0);
	T.push_back(v);
	v[0]=0.0;
	v[1]=cos(angle/2.0)-sin(angle/2.0)*I;
	T.push_back(v);
	return(T);
};