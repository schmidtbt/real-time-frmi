# =============================================================================
#
#    Makefile for Project ICODE
# 
# =============================================================================

CXX     = g++


FLAGS   = -O3 -fopenmp

programs = temp

temp : test.o
	$(CXX) $(FLAGS) -o $@ $^

% : %.cpp
	$(CXX) $(FLAGS) -o $@ $^

%.o  : %.cpp
	$(CXX) -c $(FLAGS) -o $@ $<
