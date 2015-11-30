


#ifndef __ANN_H__
#define __ANN_H__

#include"image_loader.h"
#include"node.h"

class ANN
{
    public:
        ANN();

    private:
        Image_Loader input_;
        vector<vector<Node>> hidden_;
        vector<Node> output_;
};

#endif
