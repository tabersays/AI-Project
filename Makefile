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
CXXFLAGS = -g -time -std=c++11 -Wall -W -pedantic -Werror #-D DEBUG
MAIN = recognize
#  The following flags are used to duplicate compiler/linker errors and copy
# the to a text file for easier reference.
GCCERREXT = gccerr
SFML_LIB = -lsfml-graphics
COPYOUTPUT = 2>&1 | tee ./Errors/$<.$(GCCERREXT)


#		Additional *.o filenames go here.  V
$(MAIN): .entry_point.o .node.o image_loader.o .ANN.o
	$(CXX) $^ \
		$(CXXFLAGS) $(SFML_LIB) -o $(MAIN) \
		2>&1 | tee ./Errors/$(MAIN).$(GCCERREXT)

# The test program for the image loader, use <make image_test> to compile this.
image_test: .image_test.o image_loader.o
	$(CXX) $^ $(CXXFLAGS) $(SFML_LIB) -o image_test \
		2>&1 | tee ./Errors/$@.$(GCCERREXT)

.image_test.o: image_loader_test.cpp image_loader.h typedefs.h
	$(CXX) $(CXXFLAGS) \
		-c $< -o $@ $(COPYOUTPUT)

# The test program for the nodes, use <make node_test> to compile this.
node_test: .node_test.o .node.o
	$(CXX) $^ $(CXXFLAGS) $(SFML_LIB) -o node_test \
		2>&1 | tee ./Errors/$@.$(GCCERREXT)

.node_test.o: node_test.cpp node.h typedefs.h
	$(CXX) $(CXXFLAGS) \
		-c $< -o $@ $(COPYOUTPUT)

#The name of the *.h file for the main object goes here. V
.entry_point.o: entry_point.cpp
	$(CXX) $(CXXFLAGS) \
		-c $< -o $@ $(COPYOUTPUT)

.node.o: node.cpp node.h typedefs.h
	$(CXX) $(CXXFLAGS) \
		-c $< -o $@ $(COPYOUTPUT)

image_loader.o: image_loader.cpp image_loader.h typedefs.h
	$(CXX) $(CXXFLAGS) \
		-c $< -o $@ $(COPYOUTPUT)

.ANN.o: ANN.cpp ANN.h image_loader.h node.h typedefs.h
	$(CXX) $(CXXFLAGS) \
		-c $< -o $@ $(COPYOUTPUT)

#  Add additional commands for files to be compiled here, just copy/paste the
# previous lines and modify, makes things easy.  Just remember to add the name
# of the *.o file to the line that compiles the executable.  Also, this
# Makefile relys on the *.o files being hidden, so make sure their filename
# begins with a period (.) just like the ones above, this keeps things looking
# clean when browsing your files with ls, for example.

clean:
	rm -f .*.o $(MAIN) image_test node_test ./Errors/* a.out

all: $(MAIN) node_test image_test
