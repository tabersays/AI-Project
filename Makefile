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

$(MAIN): .entry_point.o .node.o #Additional *.o filenames go here.
	$(CXX) $(CXXFLAGS) .*.o -o $(MAIN) 2>&1 | tee ./Errors/$(MAIN).$(GCCERREXT)

.entry_point.o: entry_point.cpp #The name of the *.h file for the main object goes here.
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.node.o: node.cpp node.h typedefs.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

#  Add additional commands for files to be compiled here, just copy/paste the
# previous lines and modify, makes things easy.  Just remember to add the name
# of the *.o file to the line that compiles the executable.  Also, this
# Makefile relys on the *.o files being hidden, so make sure their filename
# begins with a period (.) just like the ones above, this keeps things looking
# clean when browsing your files with ls, for example.

clean:
	rm -f .*.o $(MAIN) ./Errors/* a.out
