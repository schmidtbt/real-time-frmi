/*
 *  MPI/LOG/QUERY Merger
 *  
 *
 *  Created by Benjamin Schmidt on 5/27/10.
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
#include "HelloWorld.cxx"

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
	
	//toy values
	int sendval = 5, j = 0, k, cont = 1;
	
	char temp;
	if (myid == master)
	{
		system( "sleep 3" );
		query dirmon( "." );	//create query object
		
		//A loop over number of files anticipated
		for(int i = 1; i < 5; i++)
		{
			temp = dirmon.monitor();
			if(i == 4)
			{
				COMM_WORLD.Bcast(&cont, 1, INT, 0);
				std::cout << "Broadcast new value for cont to everyone" << std::endl;
			}
			COMM_WORLD.Send( &sendval, 1, INT, master+1, 1);
			mylog.log_event( "File creation event detected" );
			//std::cout << temp << std::endl;
		}
		
		//Now log the vector of files
		mylog.log_event( dirmon.files );
	}
	
	//Ring Structures
	{
		std::cout << "Node " << myid << ": Reporting" << std::endl;
		while(cont == 1)
		{
			std::cout << "Node " << myid << ": " << cont << std::endl;
			if( myid == master) // Returned to master -- ring complete
			{ 
				COMM_WORLD.Recv (&k, 1, INT, numprocs-1, 1, status);
				std::cout << "Node " << myid << ": Ring Complete" << std::endl;
			}
			else if(myid == numprocs-1) // end of ring, pass to master
			{
				COMM_WORLD.Recv (&k, 1, INT, myid-1, 1, status);
				std::cout << "Node " << myid << ": Message Received... Passing" << std::endl;
				COMM_WORLD.Send( &k, 1, INT, master, 1 );
			}
			else // middle of ring, keep passing
			{
				COMM_WORLD.Recv (&k, 1, INT, myid-1, 1, status);
				std::cout << "Node " << myid << ": Message Received... Passing" << std::endl;
				COMM_WORLD.Send( &k, 1, INT, myid+1, 1 );
			}
		}
	}
	
	
	double time = Wtime();
	//Done
	Finalize();
#if DEBUG_MODE==1
	std::cout << "Time: " << time - wtime << " on node: " << myid << std::endl;
#endif
	return 1;
} 

