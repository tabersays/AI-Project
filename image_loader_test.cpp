#include"image_loader.h"

#include<iostream>
#include<iomanip>

using namespace std;

int main(int argc, char* argv[] )
{
    if( argc != 2 )
    {
        cerr
            << "Usage:\n"
            << "\t" << argv[0] << " <filename>" << endl
            << endl;
        return 1;
    }

    Image_Loader image( argv[1] );
    image.print_debug();

    cerr
        << string( 80, '=' )
        << endl << "Test array access (y/n)?\t";
    char prompt;
    cin >> prompt;

    if( prompt == 'y' || prompt == 'Y' )
    {
        cerr
            << string( 80, '=' )
            << endl << "Array access operator (zero values are skipped):" << endl;

        for( unsigned i = 0; i < image.size(); i++ )
            if( image[i] != 0 )
                cerr << setw(4) << i << "\t" << setw(8) << image[i] << endl;
    }

    cerr << endl;

    return 0;
}
