


#ifndef __ANN_H__
#define __ANN_H__

#include"node.h"
#include"image_loader.h"

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

class ANN
{
    public:
        ANN(char*);

    private:
        Image_Loader* input_;

        //  A dynamically allocated array of vector<Node*>s might be

        vector<vector<Node*>> hidden_;
        vector<Node*> output_;
};

#endif
