/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
Log file testing. 

 */
 
#define DEBUG_MODE 0


//include "test.h"
#include <iostream> 
#include "Log.h"
#include <mpi.h> 
#include <math.h>
#include <string>


using namespace MPI; 

int main(int argc, char* argv[]) { 
	

	//Initialize MPI
	int myid, numprocs;
	Init(argc,argv); 
	myid=COMM_WORLD.Get_rank(); 
	numprocs=COMM_WORLD.Get_size(); 
	
	//Create a Logger
	Logger mylog(myid);
	mylog.begin();
	
		
	MPI::Status status;
	int master = 0;
	int j = 0, k;
	//Ring test.
	double wtime = Wtime();
	while(1)
	{
		
		int sendval = 5;
		if (myid == master)
		{
			//Send a single message to node 1
			mylog.log_event( "sent message" );
			COMM_WORLD.Send( &sendval, 1, INT, master+1, 1);
		}
		
		//now in a slave
		{
			
			//std::cout << "Node " << myid << " reporting" << std::endl;
			if( myid == master){ // Returned to master -- ring complete
				COMM_WORLD.Recv (&k, 1, INT, numprocs-1, 1, status);
				mylog.log_event( "Ring Finished" );
				std::cout << "Ring Complete" << std::endl;
			}
			else if(myid == numprocs-1) // end of ring, pass to master
			{
				mylog.log_event( "Message Received 1" );
				COMM_WORLD.Recv (&k, 1, INT, myid-1, 1, status);
				mylog.log_event( "Message Received 2" );
				//std::cout << "Message Received... Passing" << std::endl;
				COMM_WORLD.Send( &k, 1, INT, master, 1 );
				mylog.log_event( "sent message" );
			}
			else // middle of ring, keep passing
			{
				mylog.log_event( "Message Received" );
				COMM_WORLD.Recv (&k, 1, INT, myid-1, 1, status);
				//std::cout << "Message Received... Passing" << std::endl;
				COMM_WORLD.Send( &k, 1, INT, myid+1, 1 );
				mylog.log_event( "sent message" );
			}
		}

		break;
	}
	double time = Wtime();
	#if DEBUG_MODE==1
	std::cout << "Time: " << time - wtime << " on node: " << myid << std::endl;
	#endif
	
	
	
	
	//Done
	Finalize();
	return 1;
} 
