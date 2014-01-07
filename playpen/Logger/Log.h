/*
 *  Log.h
 *  
 *
 *  Created by Benjamin Schmidt on 5/12/10.
 *  Copyright 2010 University of Pittsburgh. All rights reserved.
 *
 */
 
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <vector>
#include <algorithm>

class Logger
{
	private:
		double get_cur_time( void );
	public:
		int myid;
		Logger( int thread ); //constructor
		void log_event( std::string message );
		std::string FileName;
		double micro2mili;
		void begin( void );
		void log_event( std::vector<char> myvec);
};

