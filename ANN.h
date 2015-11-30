


#ifndef __ANN_H__
#define __ANN_H__

#include<cassert>

#include<cmath>
using std::round;

#include<vector>
using std::vector;

#include<iostream>
using std::cin;
using std::cout;
using std::cerr;
//using 

#include"image_loader.h"
#include"node.h"

class ANN
{
    public:
        ANN();

    private:
        Image_Loader input_;

        //  A dynamically allocated array of vector<Node>s might be
        //syntactically easier.
        vector<vector<Node>> hidden_;

        
        vector<Node> output_;
};

#endif
