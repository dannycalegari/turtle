/* draw.cc drawing routines */

void geodesic(cpx u, cpx v){
	cpx z;
	double r;
	double angle1, angle2;
	int R,A1,A2,A;
	long color;
	color = 10000000;	// default color
	if(abs(u)>0.03 && abs(v)>0.03 && abs(u-v)>0.03){	// points are not too close, and far from the origin
		z=u/v;
		if(abs(z.imag())<0.03){		// if points are almost on the same radius
//			cout << u << " " << v << " straight line \n";
			draw_line(cpx_to_point(u),cpx_to_point(v),color);
			draw_dot(cpx_to_point(u),0);
			draw_dot(cpx_to_point(v),0);
		} else {
//			cout << u << " " << v << " curved line \n";
			z=circumcenter(u,invert(u),v);	
//			cout << "  circumcenter " << z << "\n";
			draw_dot(cpx_to_point(u),0);
			draw_dot(cpx_to_point(v),0);
			r=abs(u-z);	// radius
//			cout << "  radius " << r << "\n";
			if(SMALLSCREEN){
				R=(int) (r*200.0);
			} else {
				R=(int) (r*400.0);
			};
			angle1=arg(u-z);
			angle2=arg(v-z);
//			cout << "  angle 1 " << angle1 << "  angle 2 " << angle2 << "\n";
			A1=(int) (angle1*23040.0/TWOPI);
			A2=(int) (angle2*23040.0/TWOPI);
			A=A2-A1;
			while(A<0){
				A=A+23040;
			};
			A=A%23040;
//			cout << "  A " << A << "\n";
			if(A<40 || A>23000){
//				cout << "  angle too small; drawing straight line after all!\n";
				draw_line(cpx_to_point(u),cpx_to_point(v),color);		
			} else {
				if(A>11520){
					draw_arc(cpx_to_point(z),R,A2,23040-A,color);
				} else {
					draw_arc(cpx_to_point(z),R,A1,A,color);
				};	
			};
		};
	} else {
//		cout << u << " " << v << " straight line \n";
		draw_line(cpx_to_point(u),cpx_to_point(v),color);
		draw_dot(cpx_to_point(u),0);
		draw_dot(cpx_to_point(v),0);	
	};
	return;
};

void color_geodesic(cpx u, cpx v, long color){
	cpx z;
	double r;
	double angle1, angle2;
	int R,A1,A2,A;
	if(abs(u)>0.03 && abs(v)>0.03 && abs(u-v)>0.03){	// points are not too close, and far from the origin
		z=u/v;
		if(abs(z.imag())<0.03){		// if points are almost on the same radius
//			cout << u << " " << v << " straight line \n";
			draw_line(cpx_to_point(u),cpx_to_point(v),color);
			draw_dot(cpx_to_point(u),0);
			draw_dot(cpx_to_point(v),0);
		} else {
//			cout << u << " " << v << " curved line \n";
			z=circumcenter(u,invert(u),v);	
//			cout << "  circumcenter " << z << "\n";
			draw_dot(cpx_to_point(u),0);
			draw_dot(cpx_to_point(v),0);
			r=abs(u-z);	// radius
//			cout << "  radius " << r << "\n";
			R=(int) (r*400.0);
			angle1=arg(u-z);
			angle2=arg(v-z);
//			cout << "  angle 1 " << angle1 << "  angle 2 " << angle2 << "\n";
			A1=(int) (angle1*23040.0/TWOPI);
			A2=(int) (angle2*23040.0/TWOPI);
			A=A2-A1;
			while(A<0){
				A=A+23040;
			};
			A=A%23040;
//			cout << "  A " << A << "\n";
			if(A<40 || A>23000){
//				cout << "  angle too small; drawing straight line after all!\n";
				draw_line(cpx_to_point(u),cpx_to_point(v),color);		
			} else {
				if(A>11520){
					draw_arc(cpx_to_point(z),R,A2,23040-A,color);
				} else {
					draw_arc(cpx_to_point(z),R,A1,A,color);
				};	
			};
		};
	} else {
//		cout << u << " " << v << " straight line \n";
		draw_line(cpx_to_point(u),cpx_to_point(v),color);
		draw_dot(cpx_to_point(u),0);
		draw_dot(cpx_to_point(v),0);	
	};
	return;
};

void eps_color_geodesic(cpx u, cpx v, long color, ofstream &output_file){
	cpx z;
	double r;
	double angle1, angle2;
	double Rcolor, Gcolor, Bcolor;
	double A1,A2,A;
	
	Rcolor = ((double) (color/(256*256))) / 256.0;
	Gcolor = ((double) ((color/256)%256)) / 256.0;
	Bcolor = ((double) (color%256)) / 256.0;
	if(abs(u)>0.03 && abs(v)>0.03 && abs(u-v)>0.03){	// points are not too close, and far from the origin
		z=u/v;
		if(abs(z.imag())<0.03){		// if points are almost on the same radius
			output_file << u.real() << " " << u.imag() << " " << v.real() << " " << v.imag() << " "
				<< Rcolor << " " << Gcolor << " " << Bcolor << " l\n";
		} else {
			z=circumcenter(u,invert(u),v);	
			r=abs(u-z);	// radius
			angle1=arg(u-z);
			angle2=arg(v-z);
			A1=(angle1*360.0/TWOPI);
			A2=(angle2*360.0/TWOPI);
			A=A2-A1;
			while(A<0.0){
				A=A+360.0;
			};
			while(A>360.0){
				A=A-360.0;
			};
			if(A<0.6 || A>359.4){
				output_file << u.real() << " " << u.imag() << " " << v.real() << " " << v.imag() << " "
					<< Rcolor << " " << Gcolor << " " << Bcolor << " l\n";	
			} else {
				if(A>180.0){
					output_file << z.real() << " " << z.imag() << " " << r << " " << A2 << " " << 360.0-A+A2 << " "
						<< Rcolor << " " << Gcolor << " " << Bcolor << " c\n";	
				} else {
					output_file << z.real() << " " << z.imag() << " " << r << " " << A1 << " " << A+A1 << " "
						<< Rcolor << " " << Gcolor << " " << Bcolor << " c\n";	
				};	
			};
		};
	} else {
		output_file << u.real() << " " << u.imag() << " " << v.real() << " " << v.imag() << " "
			<< Rcolor << " " << Gcolor << " " << Bcolor << " l\n";
	};
	return;
};

