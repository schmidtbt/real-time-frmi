/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
 Timing and file IO using MPI. 
 
 
 */

//include "test.h"
#include <iostream> 
#include <mpi.h> 
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

//#include <boost/nondet_random.hpp>

using namespace MPI; 

int main(int argc, char* argv[]) { 
	int myid,numprocs, n = 1000, rc;
	double PI25DT = 3.141592653589793238462643;
	double mypi, pi, h, sum, x, a;
	double Tstart, Tstop;
	Init(argc,argv); 
	myid=COMM_WORLD.Get_rank(); 
	numprocs=COMM_WORLD.Get_size(); 
	//boost::random_device rnd;
	//int asdf = rnd();
	//std::cout << rnd.min() << std::endl;
	while(1)
	{
		Tstart = Wtime();
		COMM_WORLD.Bcast( &n, 1, INT, 0  );
		//std::cout << "here" << std::endl;
		
		if (n==0)
		{
			break;
		}
		else
		{
			std::string filename= "Log";
			std::stringstream out;
			out << myid;
			filename += out.str();
			//std::cout << myid << std::endl;
			std::ofstream myfile( filename.c_str() );
			time_t rawtime;
			time( &rawtime );			
			myfile << ctime( &rawtime );
			
			COMM_WORLD.Reduce( &mypi, &pi, 1, DOUBLE, SUM, 0 );
			
			if (myid == 0)
			{
				std::cout << "Pi is approx: " << pi << "\nWith error: " << fabs(pi-PI25DT) << std::endl;
				Tstop = Wtime();
				std::cout << "Time : " << Tstop-Tstart << std::endl;
				break;
			}
			
		}
	}
	Finalize();
	
	
	
	return 1;
} 
