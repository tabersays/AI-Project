#include"image_loader.h"

#include<iostream>

using namespace std;

int main()
{
    Image_Loader image("a_test.png");

    image.print_debug();

    return 0;
}
