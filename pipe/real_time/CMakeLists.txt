#Top level Cmake lists
#includes all directories from main
CMAKE_MINIMUM_REQUIRED( VERSION 2.4 )

PROJECT( RT_Pipe )

#ADD_SUBDIRECTORY( Queryinterface )
ADD_SUBDIRECTORY( Loggerinterface )
#ADD_SUBDIRECTORY( ITKinterfeace )
ADD_SUBDIRECTORY( MPIprogram )
