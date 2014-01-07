/*
 *  query.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
 Log file testing. 
 
*/

#include <sys/inotify.h>
#include <sys/types.h>
#include "query.h"
#define DEBUG_MODE 1


query::query( const char* path )
{
	count = 0;
	pathname = path;
	//Initialize inotify
	fd = inotify_init();
	
	//Add inotify watcher
	//wd = inotify_add_watch( fd, pathname, IN_CREATE);
	
#if DEBUG_MODE==1
	std::cout << "Query: Function Established" << std::endl;
#endif
}

// Create a listener. Only one event. 
char query::monitor( void )
{
#if DEBUG_MODE==1
	std::cout << "Query: Creating Query Monitor Object" << std::endl;
#endif
	
	wd = inotify_add_watch( fd, pathname, IN_CREATE);
	
#if DEBUG_MODE==1
	std::cout << "Query: Watch Created for: " << pathname << std::endl;
#endif
	
	int length = read( fd, buffer, 1024);
	int i = 0;
	char temp;
	
	while (i < length)
	{
		struct inotify_event * event = ( struct inotify_event * ) & buffer[ i ];
		if ( event->len )
		{
			//	std::cout << "here now" << std::endl;
			if (event->mask * IN_CREATE){
				
				//Get Name of File Created
				temp = *event->name;
				
				//Add name to vector container
				files.push_back(temp);
				
				
#if DEBUG_MODE==1
				std::cout << "Query: file creation detected: " << temp << std::endl;
#endif

			}
		}
		i += EVENT_SIZE + event->len;
	}


#if DEBUG_MODE==1
	std::cout << "Query: Watch Removed for: " << pathname << std::endl;
#endif

	return temp;
}


void query::dispFiles( void )
{
	std::cout << "Query: Total Number of Events: " << files.size() << std::endl;
	for(int i = 0; i < files.size(); i++)
	{
		std::cout << std::endl;
		std::cout << files[i] << std::endl;
	}
}


query::~query( void )
{
	inotify_rm_watch(fd,wd);
	close( fd );
#if DEBUG_MODE==1
	std::cout << "Query: Successful Exit of Inotify" << std::endl;
#endif
}




