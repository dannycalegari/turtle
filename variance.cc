/* variance.cc */

void compute_variance(double ANGLE, double LENGTH){
	cvec v;
	double A, turning_angle, V,angle;
	
	int i,j,k;
	cpx z,w;
	
	V=0.0;
//	cout << "angle " << ANGLE << " length " << LENGTH << " variance ";
	for(k=0;k<50000;k++){	// number of trials
		z=1.0;
		angle=0.0;
		turning_angle=0.0;
		for(i=0;i<1000;i++){
			z=(z+LENGTH)/(LENGTH*z+1.0);
			j=rand()%2;
			if(j==0){
				w=z*(cos(ANGLE)+sin(ANGLE)*I);
			} else {
				w=z*(cos(ANGLE)-sin(ANGLE)*I);
			
			};
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
	//		cout << "z is " << z << " turning angle is " << turning_angle << "\n";
		};
		V=V+(turning_angle*turning_angle);
	//	cout << turning_angle << " ";
	//	cout.flush();
	};
	V=V/1500000.0;
	cout << V << " ";
	cout.flush();
};
