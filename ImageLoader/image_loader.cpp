#include<SFML/Graphics.hpp> // The library that loads images.
#include<string>
#include<vector>
#include<iostream> // For cerr and testing.
#include<stdlib.h> // For exit(EXIT_FAILURE);

using std::cerr;
using std::endl;
using std::cout;
using std::string;
using std::vector;

using namespace std;

/**
 * image_to_vector_bool
 *
 * Converts an image into a vector<bool> to represent if a pixel is
 * filled in or left blank.
 *
 * @param image_name A string of the name and file path realative to the
 *  current directory of the image file.
 *
 * @return A vector of boolean values that represent a blank or filled in
 *  pixel.
 *   1 = filled
 *   0 = empty
 */

vector<bool> image_to_vector_bool(string image_name)
{
  // Load the image.
  sf::Image image;
  // Return an error and quit if invalid image is loaded.
  if(!image.loadFromFile(image_name))
  {
    cerr << "ERROR: Could not load image " << image_name << ". Try .png file type." << endl;
    exit(EXIT_FAILURE);
  }

  // Process the image.
  vector<bool> pixel_vector;
  sf::Vector2u image_size = image.getSize(); // Holds the x and y of an image.
  sf::Color sample; // Holds the color of each pixel.
  for(unsigned int x = 0; x < image_size.x; ++x)
  {
    for(unsigned int y = 0; y < image_size.y; ++y)
    {
      sample = image.getPixel(x,y);
      // RGB seems to return 0 so i added alpha.
      unsigned int shit = sample.r + sample.g + sample.b + sample.a;
      pixel_vector.push_back(bool(shit)); // True if any color.
    }
  }
  return pixel_vector;
}
