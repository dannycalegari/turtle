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