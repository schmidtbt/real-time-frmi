/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
 This program will sound off all nodes and all threads using both MPI and openMP
 
 */

//include "test.h"
#include <iostream> 
#include <mpi.h> 
#include <omp.h>
 
using namespace MPI; 
 
int main(int argc, char* argv[]) { 
  int rank,size; 
  Init(argc,argv); 
  rank=COMM_WORLD.Get_rank(); 
  size=COMM_WORLD.Get_size(); 
  
int th_id, nthreads;
#pragma omp parallel private(th_id)
	{
		th_id = omp_get_thread_num();
		nthreads = omp_get_num_threads();
			//std::cout << "There are " << nthreads << " threads" << std::endl;
			std::cout << th_id << "/" << nthreads << " of " << rank << std::endl;
		//std::cout << "I am here now " << std::endl;
#pragma omp barrier
		if ( th_id == 0 ) {
			nthreads = omp_get_num_threads();
			//std::cout << "There are " << nthreads << " threads" << std::endl;
			//std::cout << th_id << "/" << nthreads << " of " << rank << std::endl;
		}
	}
  
  
  //std::cout << "P:" << rank << " out of " << size << " in time: " << Wtime() << std::endl; 
  Finalize(); 
} 
