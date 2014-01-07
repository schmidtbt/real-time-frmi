/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

//include "test.h"
#include <omp.h>
#include <iostream>
#include <sys/inotify.h>

int main (int argc, char *argv[]) 
{
	int th_id, nthreads;
#pragma omp parallel private(th_id)
	{
		std::cout << system( "hostname" ) << std::endl;
		th_id = omp_get_thread_num();
		std::cout << "Hello World from thread "  << th_id << " a" << std::endl;
		std::cout << "I am here now " << std::endl;
#pragma omp barrier
		if ( th_id == 0 ) {
			nthreads = omp_get_num_threads();
			std::cout << "There are " << nthreads << " threads" << std::endl;
		}
	}
	return 0;
}
