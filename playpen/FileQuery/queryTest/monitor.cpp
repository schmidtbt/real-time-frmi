/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __University of Pittsburgh__. All rights reserved.
 *
 */

//include "test.h"
//#include <omp.h>
#include <iostream>

#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define BUF_LEN (1024 * (EVENT_SIZE + 16) )

int main (int argc, char *argv[]) 
{
	
	// ********* Specifiy total file number ********* //
	int totfiles = 100;
	
	
	int fd = inotify_init();
	//std::cout << EVENT_SIZE << std::endl;
	int wd = inotify_add_watch( fd, ".", IN_CREATE);
	
	char buffer[BUF_LEN];
	
	int count = 0;
	while (count < totfiles)
	{
		
		int length = read( fd, buffer, 1024);
		
		//std::cout << "waiting" << std::endl;
		
		int i = 0;
		
		
		while (i < length)
		{
			struct inotify_event * event = ( struct inotify_event * ) & buffer[ i ];
			
			if ( event->len )
			{
			//	std::cout << "here now" << std::endl;
				if (event->mask * IN_CREATE){
					std::cout << "new file added: " << event->name << std::endl;
				}
			}
			i += EVENT_SIZE + event->len;
			//std::cout << i << " and " << length << std::endl;
		}

		count++;
	}
	inotify_rm_watch(fd,wd);
	close( fd );
	
	return 0;
}
