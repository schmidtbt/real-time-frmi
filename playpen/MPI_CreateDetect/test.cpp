/*
 *  MPI/LOG/QUERY Merger
 *  
 *
 *  Created by Benjamin Schmidt on 6/21/10.
 *  Copyright 2010 __University of Pittsburgh__. All rights reserved.
 *
 
 */

#define DEBUG_MODE 1


//include "test.h"
#include <iostream> 
#include "Log.h"
#include <mpi.h> 
#include <math.h>
#include <string>
#include "query.h"

using namespace MPI; 

int main(int argc, char* argv[]) { 
	
	//Initialize MPI
	int myid, numprocs;
	Init(argc,argv); 
	myid=COMM_WORLD.Get_rank(); 
	numprocs=COMM_WORLD.Get_size(); 
	MPI::Status status;
	
	//Create a Logger
	Logger mylog(myid);
	mylog.begin();
	
	//Initialize some values
	int master = 0;
	double wtime = Wtime(); //the current time
	
	char temp;
	if (myid == master)
	{
		system( "sleep 3" );
		query dirmon( "." );	//create query object
		
		//A loop over number of files anticipated
		for(int i = 1; i < 1000; i++)
		{
			temp = dirmon.monitor();
			mylog.log_event( "File creation event detected" );
			std::cout << temp << std::endl;
			//const char temp2 = temp;
		}
		//Now log the vector of files
		mylog.log_event( dirmon.files );
	}
		
	
	double time = Wtime();
	//Done
	Finalize();
#if DEBUG_MODE==1
	std::cout << "Time: " << time - wtime << " on node: " << myid << std::endl;
#endif
	return 1;
} 

