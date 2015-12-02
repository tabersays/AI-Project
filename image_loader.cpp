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
 */
bool Image_Loader::image_to_vector_bool( void )
{
    pixels_.clear();

    // Load the image.
    sf::Image image;
    change_state(image.loadFromFile(image_name_));
    // Return an error and quit if invalid image is loaded.
    if(!image_load_state_)
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
void Image_Loader::new_image( string filename )
{
    image_name_ = filename;
    if( !image_to_vector_bool() )
        throw -1;

    rows_ = ceil( y_ / 4.0 );
    cols_ = ceil( x_ / 4.0 );

    make_inputs();
}

/**Converts 4x4 squares of binary pixels into unsigned short ints
*/
void Image_Loader::make_inputs( void )
{
    trans_.clear();
    inputs_.clear();

    for( unsigned y = 0; y < y_; y += 4 )
    {
        for( unsigned x = 0; x < x_; x += 4 )
        {
            short val  = 0;
            unsigned short mask = 0x8000;
            for( unsigned yy = y; yy < (y + 4); yy++ )
            {
                for( unsigned offset = x; offset < (x + 4); offset++ )
                {
                    if( pixels_[(yy * x_) + offset] )
                        val |= mask;

                    mask = mask >> 1;
                }
            }
            trans_.push_back(( val != 0) ? val : 1 );
        }
    }

    for( unsigned ii = 0; ii < trans_.size(); ii++ )
    {
        assert( !isnan( trans_[ii] / ((LD) 0x7fff) ) );
        inputs_.push_back( trans_[ii] / ((LD) 0x7fff) );
    }
}

/** Ctor
 * @param i The file name of the image to be loaded at object creation.
 * During training, the first character of the file name should be the same
 * as the character in the image.
 */
Image_Loader::Image_Loader( string i ) : image_name_(i)
{
    new_image(i);
}

/** For training purposes, gets the expected output of the neural net.
 * This is just the ASCII-code of the first character of the image file,
 * which should match the character in the image for proper behaviour.
 */
LD Image_Loader::expected( void )
{
    LD val = (int) image_name_[0];
    return val / 0x7fff;
}

/** Prints debug information.
*/
void Image_Loader::print_debug( void )
{
    char prompt = 0;

    const string BLK = ".";
    const string WHT = "\033[0;30;47m.\033[0m";
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
        << "\t(" << (char)(expected() * 0x7fff) << ")" << endl

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
        << "\t\t\tactual:\t\t\t" << trans_.size() << endl
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

        for( unsigned i = 0; i < rows_; i++ )
        {
            cerr << endl << (i % 10);
            for( unsigned j = 0; j < cols_; j++ )
            {
                int index = (i * cols_) + j;

                if( trans_[index] != 0 )
                    cerr
                        << setw(4) << setbase(16) << setfill('0')
                        << trans_[index];
                else
                    cerr << "....";

                cerr << " ";
            }
        }
        cerr << endl << " ";
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
    trans_.clear();
}
