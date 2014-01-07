# =============================================================================
#
#    Makefile for SysLog
# 
# =============================================================================

CXX     = mpicxx


FLAGS   = -O3 -fopenmp -I ~/library/MPI/bin/include -I../Logger -I../query -I../ITK_Lib

programs = temp

.PHONY: all clean

all: $(programs)

clean:
	rm -f $(programs) *.o

temp : test.o ../Logger/Log.o ../query/query.o ../ITK_Lib/HelloWorld.o
	$(CXX) $(FLAGS) -o $@ $^

% : %.cpp
	$(CXX) $(FLAGS) -o $@ $^

%.o  : %.cpp
	$(CXX) -c $(FLAGS) -o $@ $<
