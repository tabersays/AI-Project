#include<iostream>
#include"image_loader.cpp"
#include<vector>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 1)
  {
    cerr << "Need an image name to process." << endl;
    return 1;
  }

  vector<bool> image_vector = image_to_vector_bool(string(argv[1]));
  for(unsigned int i = 0; i < image_vector.size(); ++i)
    cout << image_vector[i];
  return 0;
}
