# =============================================================================
#
#    Makefile for Monitor
# 
# =============================================================================

CXX     = g++


FLAGS   = -O3 -fopenmp

programs = monitor

.PHONY: all clean

all: $(programs)

clean:
	rm -f $(programs) *.o

../monitor : monitor.o
	$(CXX) $(FLAGS) -o $@ $^

% : %.cpp
	$(CXX) $(FLAGS) -o $@ $^

%.o  : %.cpp
	$(CXX) -c $(FLAGS) -o $@ $<
