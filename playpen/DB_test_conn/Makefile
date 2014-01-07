# =============================================================================
#
#    Makefile for DB Linker
# 
# =============================================================================

CXX     = g++


FLAGS   = -I/usr/include/mysql -I/usr/include/mysql++ -lmysqlpp -I/usr/lib/ $(shell mysql_config --include) $(shell mysql_config --libs) -L/synapse/pkg/mysql++-3.0.9/
LINKER = -lmysqlpp -L/synapse/pkg/mysql++-3.0.9/

programs = temp

temp : test.o 
	$(CXX) $(FLAGS) $(LINKER) -o $@ $^

% : %.cpp
	$(CXX) $(FLAGS) -o $@ $^

%.o  : %.cpp
	$(CXX) -c $(FLAGS) -o $@ $<

