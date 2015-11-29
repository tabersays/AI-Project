ImageLoagerTest: main.o
	g++ -Wall -pedantic -g -o ImageLoaderTest main.o -lsfml-graphics

main.o: main.cpp
	g++ -g -std=c++11 -Wall -W -Werror -pedantic -c main.cpp

image_loader.o: image_loader.cpp
	g++ -g -std=c++11 -Wall -W -Werror -pedantic -c image_loader.cpp


clean:
	rm *.o ImageLoaderTest
