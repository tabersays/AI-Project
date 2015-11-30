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
        << endl << "Array access operator:" << endl;
    for( unsigned i = 0; i < image.size(); i++ )
        cerr << image[i] << " ";

    cerr << endl;

    return 0;
}
