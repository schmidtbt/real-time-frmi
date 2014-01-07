/*
 *  query.h
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 
Log file testing. 

 */


// Inotify parameters
#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define BUF_LEN (1024 * (EVENT_SIZE + 16) )

#include <iostream>
#include <sys/inotify.h>

#include <sys/types.h>
#include <vector>

class query
{
	private:
		int fd;
		int wd;
		int count;
		const char* pathname;
		
		char buffer[BUF_LEN];
	public:
		std::vector<char> files;	//All files seen thusfar (check against directory post-hoc)
		query( const char* path );	//initlaize inotify
		~query( void );
		char monitor( void );							// return new file name
		int returnCount( void ){ return count; }
		void dispFiles( void );
};
