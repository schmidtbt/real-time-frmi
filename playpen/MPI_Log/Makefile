# =============================================================================
#
#    Makefile for MPIbroadcast
# 
# =============================================================================

CXX     = mpicxx


FLAGS   = -O3 -fopenmp -I ~/library/MPI/bin/include -I ~/library/boost_1_42_0 -I.

programs = temp

.PHONY: all clean

all: $(programs)

clean:
	rm -f $(programs) *.o

temp : test.o
	$(CXX) $(FLAGS) -o $@ $^

% : %.cpp
	$(CXX) $(FLAGS) -o $@ $^
	
% : %.h
	$(CXX) $(FLAGS) -o $@ $^

%.o  : %.cpp
	$(CXX) -c $(FLAGS) -o $@ $<
