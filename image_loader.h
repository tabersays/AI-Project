#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__

#include<SFML/Graphics.hpp> // The library that loads images.
#include<string>
#include<vector>
#include<iostream> // For cerr and testing.

using std::cerr;
using std::endl;
using std::cout;
using std::string;
using std::vector;

using sf::Image;
using sf::Vector2u;
using sf::Color;

class Image_Loader
{
    public:
        Image_Loader( string );

    private:
        bool image_to_vector_bool( void );

        vector<bool>    pixels_;
        string          image_name_;
};

#endif
