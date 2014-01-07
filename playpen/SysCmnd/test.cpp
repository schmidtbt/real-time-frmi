/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 This code is used to test system commands using MPI. 
 
 Here we execute simple local commands for each node. 
 */

//include "test.h"
#include <iostream> 
#include <mpi.h> 
#include <math.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace MPI; 

int main(int argc, char* argv[]) { 
	
	//Initialize MPI
	int myid, numprocs;
	Init(argc,argv); 
	myid=COMM_WORLD.Get_rank(); 
	numprocs=COMM_WORLD.Get_size(); 
	
	std::string sleeping = "sleep ";
	std::stringstream out;
	out << myid;
	sleeping += out.str();
	
	int i = system( sleeping.c_str() );
	int j = system( "ls" );
	std::cout << myid << std::endl;
	
	
	//Done
	Finalize();
	return 1;
} 
