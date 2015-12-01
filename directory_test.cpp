

#include"directory.h"

#include<iostream>
using namespace std;


int main( int argc, char* argv[] )
{
    string name;
    if( argc == 2 )
        name = argv[1];
    else
        name = "./";

    Directory dir(name.c_str());

    for( unsigned i = 0; i < dir.file().size(); i++ )
        cout << dir.file()[i] << endl;

    return 0;
}
