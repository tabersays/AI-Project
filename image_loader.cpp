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
    Color sample; // Holds the color of each pixel.
    for(unsigned int x = 0; x < image_size.x; ++x)
    {
        for(unsigned int y = 0; y < image_size.y; ++y)
        {
            sample = image.getPixel(x,y);

            // RGB seems to return 0 so i added alpha.
            unsigned int shit = sample.r + sample.g + sample.b + sample.a;
            pixels_.push_back(bool(shit)); // True if any color.
        }
    }
    return true;
}

/** Ctor
*/
Image_Loader::Image_Loader( string i ) : image_name_(i)
{
    if( !image_to_vector_bool() )
        throw -1;
}
