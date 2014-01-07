/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

//include "test.h"
#include <iostream> 
#include <mpi.h> 
//#include <mpe.h>
#include <math.h>
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
			h = 1.0 / (double) n;
			sum = 0.0;
			for (int i = myid + 1; i <= n; i += numprocs)
			{
				x = h * ( (double)i - .5 );
				//std::cout << h << std::endl;
				sum += ( 4.0 / ( 1.0 + x*x ) );
			}
			mypi = h * sum;
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
