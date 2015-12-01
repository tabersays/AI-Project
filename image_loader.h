#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__

#include<SFML/Graphics.hpp> // The library that loads images.
using sf::Image;
using sf::Vector2u;
using sf::Color;

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<iostream>          // For cerr and testing.
using std::cerr;
using std::endl;
using std::cout;

#include<cmath>             // For ceiling function for debug.
using std::ceil;
using std::floor;

#include<iomanip>           // For debug output formatting.
using std::setw;
using std::setbase;
using std::setfill;

#include"typedefs.h"


class Image_Loader
{
    public:
        Image_Loader( string );
        ~Image_Loader( void );

        void operator()( string );
        LD expected( void );

        void print_debug( void );

        unsigned size( void )
        { return inputs_.size(); }

        const LD& operator[]( unsigned a )
        { return inputs_[a]; }
        const LD& operator[]( int a )
        { return inputs_[a]; }


    private:
        Image_Loader() {} //Force use of the other ctor.

        bool image_to_vector_bool( void );
        void make_inputs( void );

        vector<LD>                  inputs_;
        vector<short>               trans_;
        vector<bool>                pixels_;
        string                      image_name_;
        unsigned                    x_; ///< Image x-dimension.
        unsigned                    y_; ///< Image y-dimension.

        unsigned                    rows_;
        unsigned                    cols_;

};

#endif
