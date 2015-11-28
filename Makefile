#
#   Thomas Russel Carrel
#
#   Makefile
#
#   All of these compile lines are set up to duplicate all output (errors) from
#  g++ and copy it into a file.
#
#   Note, that you must have a directory called Errors/ in order for this file
#  to work.
#

CXX = g++
DEBUG = 0
CXXFLAGS = -g -std=c++11 -Wall -W -pedantic -Werror #-D DEBUG
MAIN = recognize
#  The following flags are used to duplicate compiler/linker errors and copy
# the to a text file for easier reference.
GCCERREXT = gccerr
COPYOUTPUT = 2>&1 | tee ./Errors/$<.$(GCCERREXT)

$(MAIN): .entry_point.o .node.o
	$(CXX) $(CXXFLAGS) .*.o -o $(MAIN) 2>&1 | tee ./Errors/$(MAIN).$(GCCERREXT)

.entry_point.o: entry_point.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.node.o: node.cpp node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

clean:
	rm -f .*.o $(MAIN) ./Errors/* a.out
