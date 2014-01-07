#test Cmakelists


INCLUDE_DIRECTORIES( ../Loggerinterface/ )

ADD_EXECUTABLE( RT_Pipe test)

TARGET_LINK_LIBRARIES( RT_Pipe LOG )
