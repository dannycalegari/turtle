/* interface.cc */

void turtle::user_interface(){
	bool finished;
	point p;

	finished=false;
	
	cout << "Entering interactive mode. Press [q] to exit.\n";
	cout << "(note: mouse must be focussed in X-window)\n";
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
            default:
            	break;
        };
    };
};
