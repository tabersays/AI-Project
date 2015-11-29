#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__

#include<SFML/Graphics.hpp> // The library that loads images.
#include<string>
#include<vector>
#include<iostream>          // For cerr and testing.
#include<cmath>             // For ceiling function for debug.

#include"typedefs.h"

using std::cerr;
using std::endl;
using std::cout;
using std::string;
using std::vector;
using std::ceil;

using sf::Image;
using sf::Vector2u;
using sf::Color;

class Image_Loader
{
    public:
        Image_Loader( string );
        ~Image_Loader( void );

        void operator()( string );
        char expected( void );

        void print_debug( void );

        unsigned size( void )
        { return inputs_.size(); }
        const short& operator[]( int a )
        { return inputs_[a]; }
    private:
        Image_Loader() {} //Force use of the other ctor.

        bool image_to_vector_bool( void );
        void make_inputs( void );

        vector<short>   inputs_;
        vector<bool>    pixels_;
        string          image_name_;
        unsigned        x_; ///< Image x-dimension.
        unsigned        y_; ///< Image y-dimension.
};

#endif
