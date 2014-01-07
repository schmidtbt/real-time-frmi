/*
 *  Log.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/12/10.
 *  Copyright 2010 University of Pittsburgh. All rights reserved.
 *
 */
#define DEBUG_MODE 1
#include "Logger.h"

Logger::Logger( int thread )
{
	myid = thread;
	micro2mili = 1/1000000.0;
	
	std::string prefix= "NodeLog";
	std::stringstream out;
	out << myid;
	FileName = prefix + out.str();
	
	//open a file using this name
	std::ofstream myfile( FileName.c_str() );
	time_t rawtime;
	time( &rawtime );			
	//Write time created to this node
	myfile << ctime( &rawtime );
	//myfile << get_cur_time();
	
	
}


void Logger::begin( void )
{
	std::string startMsg = "Log Start";
	log_event( startMsg );
}


void Logger::log_event( std::string message )
{
	std::ofstream tfile( FileName.c_str(), std::ofstream::app );
	time_t rawtime;
	time( &rawtime );
	std::stringstream out;
	out << ( &rawtime );
	//out << get_cur_time();
	message = out.str() + " " + message;
	message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
	message = message + "\n";
#if DEBUG_MODE==1
	std::cout << "Message - Node " << myid << ": " << message; 
#endif
	tfile << message;
	
#if DEBUG_MODE==1
	std::cout << "Logger: Event Logged" << std::endl; 
#endif
}


void Logger::log_event( std::vector<char> myvec)
{
	std::cout << "logging vector" << std::endl;
	std::string message;
	std::ofstream tfile( FileName.c_str(), std::ofstream::app );
	time_t rawtime;
	time( &rawtime );
	std::stringstream out;
	out << ( &rawtime );
	//out << get_cur_time();
	message = out.str();
	tfile << "Files Detected:\n";
	for(int i = 0; i < myvec.size(); i++)
	{
		tfile << myvec[i] << "\n";
	}
	
#if DEBUG_MODE==1
	std::cout << "Logger: Vector Event Logged" << std::endl; 
#endif
}



double Logger::get_cur_time( void )
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	
	return tv.tv_sec + tv.tv_usec * micro2mili;
}
