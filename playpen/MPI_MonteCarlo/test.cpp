/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
 This code was used to play with the MPI message passing. Here we send the total number of times we would like to sample (n) and then it iterates through each sample amongst different cores.
 
 Adding the functionality for openMP in this context slowed things dramatically. As each node is responsible for a single point at a time rather than a chunk of data. No parallelization possible with only a single point. 
 */

//include "test.h"
#include <iostream> 
#include <mpi.h> 
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <omp.h>

using namespace MPI; 

int main(int argc, char* argv[]) { 
	int myid, numprocs, rc;
	
	int n = 10000; // Total number of samples in monte carlo
	
	double PI25DT = 3.141592653589793238462643;
	double mypi, pi, h, sum, x, y, a;
	double Tstart, Tstop;
	Init(argc,argv); 
	myid=COMM_WORLD.Get_rank(); 
	numprocs=COMM_WORLD.Get_size(); 
	int tcount = 0, tot;
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
		int th_id;
//#pragma omp parallel private(th_id)
			{
//#pragma omp barrier

				for (int i = myid + 1; i <= n; i += numprocs)
				{
					x = rand() / (double)RAND_MAX;
					y = rand() / (double)RAND_MAX;
					//std::cout << x << " " << y << std::endl;
					//tcount++;
					if ( sqrt( x*x + y*y ) < 1 )
						tcount++;
					
					//std::cout << tcount << std::endl;
				}
			}
			std::cout << tcount << std::endl;
			COMM_WORLD.Reduce( &tcount, &tot, 1, DOUBLE, SUM, 0 );
			
			if (myid == 0)
			{
				std::cout << "Total Inside: " << tot << std::endl;
				std::cout << "Estimated Pi: " << 4*(double)tot/(double)n << std::endl;
				Tstop = Wtime();
				std::cout << "Time : " << Tstop-Tstart << std::endl;
				break;
			}
			
		}
		break;
	}
	Finalize();
	
	
	
	return 1;
} 
