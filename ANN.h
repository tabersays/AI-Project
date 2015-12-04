


#ifndef __ANN_H__
#define __ANN_H__

#define ALPHA 1

#include"node.h"
#include"image_loader.h"

#include<cassert>

#include<cmath>
using std::round;

#include<vector>
using std::vector;

#include<stack>
using std::stack;

#include<fstream>
using std::ifstream;
using std::ofstream;

#include<iostream>
using std::cin;
using std::cout;
using std::cerr;

#include<ctime>

#include<cctype>
using std::isspace;

class ANN
{
    public:
        ANN( void );
        ~ANN( void );

        bool load( char* );
        bool save( string );

        LD run();
        void back_propagate( LD );

        bool load_image( string );
    private:
        void clear();

        Image_Loader*           input_; //input_layer
        unsigned                input_layer_size_;
        vector<vector<Node*>>   hidden_;        
        LD                      output_;
        vector<vector<LD>>      edges_;
};

#endif
