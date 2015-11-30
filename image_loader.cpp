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
    pixels_.clear();

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
    if( !image_to_vector_bool() )
        throw -1;

    rows_ = ceil( x_ / 4.0 );
    cols_ = ceil( y_ / 4.0 );

    make_inputs();
}

/**Converts 4x4 squares of binary pixels into unsigned short ints
*/
void Image_Loader::make_inputs( void )
{
    inputs_.clear();

    for( unsigned y = 0; y < y_; y += 4 )
    {
        for( unsigned x = 0; x < x_; x += 4 )
        {

            unsigned short val  = 0;
            unsigned short mask = 0x8000;
            for( unsigned yy = y; yy < (y + 4); yy++ )
            {
                //                if( row < y_ )
                //                {
                for( unsigned offset = x; offset < (x + 4); offset++ )
                {
                    if( pixels_[(yy * x_) + offset] )
                        val |= mask;

                    mask = mask >> 1;
                }
                //                }
            }
            inputs_.push_back(val);
        }
    }
}

/** Ctor
 * @param i The file name of the image to be loaded at object creation.
 * During training, the first character of the file name should be the same
 * as the character in the image.
 */
Image_Loader::Image_Loader( string i ) : image_name_(i)
{
    this->operator()(i);
}

/** For training purposes, gets the expected output of the neural net.
 * This is just the ASCII-code of the first character of the image file,
 * which should match the character in the image for proper behaviour.
 */
int Image_Loader::expected( void )
{ 
    return (int) image_name_[0];
}

/** Prints debug information.
*/
void Image_Loader::print_debug( void )
{
    char prompt = 0;

    const string BLK = " ";
    const string WHT = "\033[0;0;47m \033[0m";
    const string RED = "\033[0;0;41m \033[0m";
    string LINE = "";
    for( unsigned ii = 0; ii < x_; ii++ )
    {
        if( !(ii % 4) )
            LINE += RED;
        LINE += RED;
    }
    LINE += RED;

    cerr 
        << "\033[1;33;42m" << string(32,' ')
        << "IMAGE DEBUG DATA" << string(32, ' ') << "\033[0m" << endl
        << "\tLOADED FILE DETAILS:" << endl
        << std::string(80,'=') << endl
        << "\t\tFile name:\t\t" << image_name_ << endl
        << "\t\tExpected output:\t" << expected()
        << "\t(" << (char)expected() << ")" << endl
        << "\tIMAGE DIMENSIONS:" << endl
        << std::string(80,'=') << endl
        << "\t\tDimensions:" << endl
        << "\t\t\t(x, y):\t\t(" << x_ << ", " << y_ << ")" << endl
        << "\t\t" << std::string(64, '-') << endl
        << "\t\tNumber of Pixels:" << endl
        << "\t\t\tcalculated:\t" << x_ * y_ << endl
        << "\t\t\tread (actual):\t" << pixels_.size() << endl
        << std::string(80,'=') << endl
        << "\tNUMBER OF INPUTS:" << endl
        << std::string(80,'=') << endl
        << "\t\tQuantity:" << endl
        << "\t\t\tcalculated:\t\t" << rows_ * cols_ << endl
        << "\t\t\tactual:\t\t\t" << inputs_.size() << endl
        << "\t\t" << string(64, '-') << endl
        << "\t\t\trows:\t\t\t" << rows_ << endl
        << "\t\t\tcolumns:\t\t" << cols_ << endl
        << string(80,'=') << endl
        << string(80,'=') << endl
        << "Do you wish to print the pixels as text? (y,n)" << endl
        << "\tWARNING::\tThis can take lots of space!!\t::WARNING" << endl
        << string(80,'=') << endl;
    std::cin >> prompt;
    cerr << string(80,'=') << endl;

    if( prompt == 'y' || prompt == 'Y' )
    {

        for( unsigned jj = 0; jj < y_; jj++ )
        {
            if( !(jj % 4 ))
                cerr << LINE << endl;
            for( unsigned ii = 0; ii < x_; ii++ )
            {
                if( !(ii % 4) )
                    cerr << RED;

                cerr << "\033[0m" << ((pixels_[(jj*x_) + ii]) ? BLK : WHT );
            }
            cerr << RED << endl;
        }
        cerr << LINE << endl << string(80,'=') << endl;
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
        cerr << endl << "All values are in hexadecimal.";
        for( unsigned i = 0; i < inputs_.size(); i++ )
        {
            if( !(i % cols_) )
                cerr << endl;

            if( inputs_[i] != 0 )
                cerr 
                    << setw(4) << setbase(16) << setfill('0') 
                    << inputs_[i] << " ";
            else
                cerr << ".... ";
        }

        cerr << endl;
    }
    else
    {
        cerr << "\n\tInput layer was not printed" << endl;
    }

    cerr << endl;
}

/// Dtor
Image_Loader::~Image_Loader( void )
{
    pixels_.clear();
    inputs_.clear();
}
