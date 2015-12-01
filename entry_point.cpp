/**
 * Entry point for the ANN.
 *
 * @file entry_point.cpp
 *
 *
 */


#include<iostream>
using std::cerr;
using std::endl;

#include"ANN.h"
#include"directory.h"

bool run_net( )// ANN& network )
{

    return false;
}

bool train_net( )//ANN& network )
{

    return false;
}

int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        cerr
            << "\tUsage:" << endl
            << "\t\t" << argv[0] << " <filename> [optional]<directory>" << endl
            << "\t\t\t<filename>\tThe saved ANN configuration file." << endl
            << "\t\t\t<directory>\tThe directory containing training data.\n"
            << endl;
        return 1;
    }
    
    ANN network( argv[1] );

    switch( argc )
    {
        case 2:
//            return run_net( network );
            cerr << 2; return 0;
        case 3:
//            return train_net( network );
            cerr << 3; return 0;
        default:
            cerr << "\tToo many arguments.\n" << endl;
            return 1;
    }
}
