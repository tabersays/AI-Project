/**
 *   Function definitions for the Image_Loader object.
 *
 *
 * @author Michael Taylor
 * @author Thomas Russel Carrel
 */

#include"image_loader.h"

/**
 * image_to_vector_bool
 *
 * Converts an image into a vector<bool> to represent if a pixel is
 * filled in or left blank.
 *
 * @param image_name_ A string of the name and file path realative to the
 *  current directory of the image file.
 *
 * @return A vector of boolean values that represent a blank or filled in
 *  pixel.
 *   1 = filled
 *   0 = empty
 */
bool Image_Loader::image_to_vector_bool( void )
{
    // Load the image.
    sf::Image image;
    // Return an error and quit if invalid image is loaded.
    if(!image.loadFromFile(image_name_))
    {
        cerr << "ERROR: Could not load image <" <<
            image_name_ << ">. Try .png file type." << endl;
        return false;
    }

    // Process the image.
    Vector2u image_size = image.getSize(); // Holds the x and y of an image.
    x_ = image_size.x;
    y_ = image_size.y;

    Color sample; // Holds the color of each pixel.
    for(unsigned y = 0; y < y_; ++y)
    {
        for(unsigned x = 0; x < x_; ++x)
        {
            sample = image.getPixel(x,y);

            // RGB seems to return 0 so i added alpha.
            unsigned shit = sample.r + sample.g + sample.b + sample.a;
            pixels_.push_back(bool(shit)); // True if any color.
        }
    }
    return true;
}

/**Loads a new image into the object.
*/
void Image_Loader::operator()( string filename )
{
    image_name_ = filename;
    pixels_.clear();
    inputs_.clear();
    if( !image_to_vector_bool() )
        throw -1;
}

/// Dtor
Image_Loader::~Image_Loader( void )
{
    pixels_.clear();
    inputs_.clear();
}

/** Ctor
 * @param i The file name of the image to be loaded at object creation.
 * During training, the first character of the file name should be the same
 * as the character in the image.
 */
Image_Loader::Image_Loader( string i ) : image_name_(i)
{
    if( !image_to_vector_bool() )
        throw -1;
}

/**
*/
void Image_Loader::make_inputs( void )
{
}

/** For training purposes, gets the expected output of the neural net.
 * This is just the ASCII-code of the first character of the image file,
 * which should match the character in the image for proper behaviour.
 */
char Image_Loader::expected( void )
{ 
    return image_name_[0];
}

/** Prints debug information.
*/
void Image_Loader::print_debug( void )
{
    char prompt = 0;
    cerr
        << "\tLOADED FILE DETAILS:" << endl
        << std::string(80,'=') << endl
        << "\t\tFile name:\t\t" << image_name_ << endl
        << "\t\tExpected output:\t" << expected()
        << "\t(" << (int)expected() << ")" << endl
        << "\tIMAGE DIMENSIONS:" << endl
        << std::string(80,'=') << endl
        << "\t\tDimensions:" << endl
        << "\t\t\t(x, y):\t\t(" << x_ << ", " << y_ << ")" << endl
        << "\t" << std::string(72, '-') << endl
        << "\t\tNumber of Pixels:" << endl
        << "\t\t\tcalculated:\t" << x_ * y_ << endl
        << "\t\t\tread (actual):\t" << pixels_.size() << endl
        << std::string(80,'=') << endl
        << "\tNUMBER OF INPUTS:" << endl
        << std::string(80,'=') << endl
        << "\t\tcalculated:\t\t";

    int inputs_c = ceil( x_ / 4 ) * ceil( y_ / 4 );
    cerr
        << inputs_c << endl
        << "\t\tactual:\t\t\t" << inputs_.size() << endl
        << string(80,'=') << endl
        << string(80,'=') << endl
        << "Do you wish to print the pixels as text? (y,n)" << endl
        << "\tWARNING::\t This takes lots of space!!\t::WARNING" << endl
        << string(80,'=') << endl;
    std::cin >> prompt;
    cerr << string(80,'=');

    if( prompt == 'y' || prompt == 'Y' )
    {
        for( unsigned ii = 0; ii < pixels_.size(); ii++ )
        {
            if( !(ii % x_ ) )
                cerr << endl;
            cerr << ((pixels_[ii]) ? "X" : ".");

        }
        cerr << endl << string(80,'=') << endl;
    }
    else
    {
        cerr << "\n\tPixels were not printed" << endl;
    }
    prompt = 0;

    cerr
        << "Do you wish to print data values from the input layer?" << endl
        << string(80,'=') << endl;
    std::cin >> prompt;
    cerr << string(80,'=');

    if( prompt == 'y' || prompt == 'Y' )
    {
        if( !(ii % (y_ / 4)) )
            cerr << endl;

        for( unsigned ii = 0; ii < inputs_.size(); ii++ )
            cerr << inputs_[i] << " "
    }
    else
    {
       cerr << "\n\tInput layer was not printed" << endl;
    }

    cerr << endl;
}
