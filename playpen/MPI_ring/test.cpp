/*
 *		Ring test
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
 Ring testing
 
 Send a message from one node to the next and back to the master
 */

//include "test.h"
#include <iostream> 
#include <mpi.h> 
#include <math.h>

using namespace MPI; 

int main(int argc, char* argv[]) { 
	
	//Initialize MPI
	int myid, numprocs;
	Init(argc,argv); 
	myid=COMM_WORLD.Get_rank(); 
	numprocs=COMM_WORLD.Get_size(); 
	
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
			COMM_WORLD.Send( &sendval, 1, INT, master+1, 1);
			
			
			
			/* //this is the master
			 for( int i = 1; i <= 8; i++)
			 {
			 COMM_WORLD.Send( &i, 1, INT, i, 1);
			 std::cout << "Message Sent" << std::endl;
			 } */
		}
		
		//now in a slave
		{
			std::cout << system( "hostname" ) << std::endl;
			std::cout << "Node " << myid << " reporting" << std::endl;
			//receive value k from node j
			/*for( int r = 1; r <= 9; r++ ){
			 if(myid = r)
			 {*/
			//std::cout << myid << std::endl;
			
			if( myid == master){ // Returned to master -- ring complete
				COMM_WORLD.Recv (&k, 1, INT, numprocs-1, 1, status);
				std::cout << "Ring Complete" << std::endl;
			}
			else if(myid == numprocs-1) // end of ring, pass to master
			{
				COMM_WORLD.Recv (&k, 1, INT, myid-1, 1, status);
				std::cout << "Message Received... Passing" << std::endl;
				COMM_WORLD.Send( &k, 1, INT, master, 1 );
			}
			else // middle of ring, keep passing
			{
				COMM_WORLD.Recv (&k, 1, INT, myid-1, 1, status);
				std::cout << "Message Received... Passing" << std::endl;
				COMM_WORLD.Send( &k, 1, INT, myid+1, 1 );
			}
		}

		break;
	}
	double time = Wtime();
	std::cout << "Time: " << time - wtime << " on node: " << myid << std::endl;
	
	
	
	
	
	//Done
	Finalize();
	return 1;
} 
