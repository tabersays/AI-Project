/**
 * Entry point for the ANN.
 *
 * @file entry_point.cpp
 *
 *
 */


#include<fstream>
#include<string>
#include<iostream>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;

using namespace std;

#include"ANN.h"
#include"directory.h"

bool run_net( )// ANN& network )
{

  return false;
}

bool train_net( ANN& network, string name )
{
  Directory dir(name);
  cout << "File index to start at, should be 0 unless crash?" << endl;
  unsigned file_index = 0;
  cin >> file_index;
  cout << "Number of training steps, 0 to go through the entire directory."
    << endl;
  unsigned step = 0;
  cin >> step;

  // Set step to size of oyr training set.
  if(step == 0)
    step = dir.file().size();


  ofstream training_progress;
  training_progress.open( "ann_training_step" );

  if( !training_progress.is_open() )
    return false;

  for(unsigned i = 0; i < step; --i)
  {

    while( dir.file().size() )// Number of training iterations
    {


    }
  }
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
      string dir = argv[2];
      return run_net( network, dir );
    case 3:
      //            return train_net( network );
      cerr << 3; return 0;
    default:
      cerr << "\tToo many arguments.\n" << endl;
      return 1;
  }
}
