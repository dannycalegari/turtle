/* interface.cc */

void user_interface(double &ANGLE, double &LENGTH, int &seed){
	bool finished;
	point p;

	finished=false;
	while(finished==false){
		XNextEvent(display, &report);
		switch(report.type) {
			case ButtonPress:
				p=mouse_location();
				break;
			case KeyPress:
				if(XLookupKeysym(&report.xkey, 0) == XK_q){ // quit           
                    finished=true;
                    XCloseDisplay(display);
                    exit(0);
                    break;
                };
                if(XLookupKeysym(&report.xkey, 0) == XK_Left){
                	ANGLE=ANGLE+0.01;
                	erase_field();
                	geodesic_segments(ANGLE, LENGTH, seed);
                	break;
                };
                if(XLookupKeysym(&report.xkey, 0) == XK_Right){
                	ANGLE=ANGLE-0.01;
                	erase_field();
                	geodesic_segments(ANGLE, LENGTH, seed);
                	break;
                };
                if(XLookupKeysym(&report.xkey, 0) == XK_Up){
                	LENGTH=LENGTH*1.01;
                	erase_field();
                	geodesic_segments(ANGLE, LENGTH, seed);
                	break;
                };   
                if(XLookupKeysym(&report.xkey, 0) == XK_Down){
                	LENGTH=LENGTH/1.01;
                	erase_field();
                	geodesic_segments(ANGLE, LENGTH, seed);
                	break;
                };          
                if(XLookupKeysym(&report.xkey, 0) == XK_s){	// increment seed
                	seed++;
                	cout << "New seed is " << seed << "\n";
                	cout.flush();
                 	erase_field();
                	geodesic_segments(ANGLE, LENGTH, seed);
                	break;
                };                  
                if(XLookupKeysym(&report.xkey, 0) == XK_e){ // eps output
                	cout << "Writing output to file `turtle_picture.eps' \n";
                	cout.flush();
                	eps_geodesic_segments(ANGLE, LENGTH, seed);
                	break;
                };
            default:
            	break;
        };
    };
};

void program_user_interface(){
	bool finished;

	finished=false;
	while(finished==false){
		XNextEvent(display, &report);
		switch(report.type) {
			case KeyPress:
				if(XLookupKeysym(&report.xkey, 0) == XK_q){ // quit           
                    finished=true;
                    XCloseDisplay(display);
                    exit(0);
                    break;
                };
            default:
            	break;
        };
    };
};