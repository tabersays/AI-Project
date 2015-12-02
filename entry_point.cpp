/**
 * Entry point for the ANN.
 *
 * @file entry_point.cpp
 *
 *
 */


#include<fstream>
using std::ifstream;
using std::ofstream;

#include<string>
using std::string;

#include<iostream>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::flush;

#include<cmath>
using std::round;

#include<chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

#include"ANN.h"
#include"directory.h"

int run_net( ANN& network )
{
    string image_file;
    char loop = 0;

    while( loop != 'y' && loop != 'Y' )
    {
        cout
            << "\033[2J"; //Clear the screen.
        cout
            << "Enter mage file name (and path):" << endl 
            << "\t$ " << flush;
        cin >> image_file;
        bool loaded = !network.load_image( image_file );

        while( !loaded )
        {
            cout
                << "Could not open file <" << image_file << ">, please enter "
                << "a different file." << endl << "\t$ " << flush;
            loaded = network.load_image( image_file );
        }
        LD result = network.run();

        cout << "Your image was the letter '" << (char)round(result * 128) << endl;

        cout
            << "Do you wish to try another image? (y/n)" << endl << "\t$ ";
        cin >> loop;
        cout
            << "Entered [" << loop << "]." << endl;
    }

    return 0;
}

int train_net( ANN& network, string name, string file )
{
    Directory dir(name);
    ofstream number;

    string save_file = file + "_new";

    //timing
    high_resolution_clock::time_point begin;
    high_resolution_clock::time_point end;
    duration<double> dur;

    cout << "File index to start at, should be 0 unless crash?" << endl;
    unsigned file_index = 0;
    cin >> file_index;
    cout << "Number of training steps, 0 to go through the entire directory."
        << endl;
    unsigned last_step = 0;
    cin >> last_step;

    // Set step to size of oyr training set.
    if( last_step != 0 )
        last_step += file_index;
    else
        last_step = dir.file().size();


    ofstream training_progress;
    training_progress.open( "ann_training_step" );

    if( !training_progress.is_open() )
        return 1;

    for(unsigned i = file_index; i < last_step; ++i)
    {
        number.open("last_file_number");

        begin = high_resolution_clock::now();

        network.load_image( dir.file()[i] );
        LD value = network.run();
        assert( !isnan(value) );
        network.back_propagate( value );
        end = high_resolution_clock::now();

        dur = duration_cast<duration<double>>(end - begin);
        cout
            << "  Training itteration " << i 
            << " took " << dur.count() << " seconds." << endl;

        network.save(save_file);

        number << i << flush;
        number.close();
    }
    return 0;
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

    ANN network;
    if( !network.load( argv[1] ) )
    {
        cerr << "Could not load file <" << argv[1] << ">.\n" << endl;
        return 1;
    }

    // Cannot create variables within a switch statement.
    string dir;
    if( argc == 3 )
        dir = argv[2];

    switch( argc )
    {
        case 2:
            return run_net( network );
        case 3:
            return train_net( network, dir, argv[1] );
        default:
            cerr << "\tToo many arguments.\n" << endl;
            return 1;
    }
}
