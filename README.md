Taber Storm Fitzgerald
Thomas Russel Carrel
Michael Taylor
Mark Moniz

AI Project

Makefile

Q: How do you use your Makefile?

A: I added instructions to the Makefile.


Remember to check issues for other items of note.

[Documentation](http://www.ecst.csuchico.edu/~tcarrel/580/p2/)
I'll update this as your guy's contributions come in, TC.

  We're using SFML to parse the images.  Michael has provided the object file in
addition to the code to make compilation a little bit easier if you don't have
SFML installed.  The documentation to installed SFML on you system is here 
under [Getting Started](http://www.sfml-dev.org/tutorials/2.3/).

Instructions for generating test data:
1. generateImages.html has the browser generate png's it is recomended to use chrome and to redirect your download destination to dataSet/png once done click download
2. run convert.sh while in dataSet/png to create the bmp's


Instructions for generating your initial un-trained Neural Net layout:
1. Run the node_generator.rb script located in the scripts/ directory.
2. Enter as prompted
	- Filename: The name of the file to be saved.
	- Input Nodes: The number of nodes in the input layer.
	- Hidden Nodes: The number of nodes in the _first_ hidden layer.
	- Reduction Step: This should be and integer that when dividing the number of nodes in the input layer by it approximately results in the number of nodes in the first hidden layer.  The script repeatedly divides by this value to reduce the size of each layer.  It is possible to create scripts to generate different network layouts, read save_file_format.txt for information on file specifications.
3. There is an error in the script, so it is necessary to open the generated file and edit it in your favorite text editor.  After opening it, cound the number of percent-signs (%) you find in the file and replace the value on line two with this number.
