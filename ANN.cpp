



#include"ANN.h"

ANN::ANN( char* file )
{
    load(file);
}

bool ANN::load( char* file)
{
    ifstream inf;
    inf.open( file );
    if(inf.fail())
    {
        return false;
    }
    int entry_nodes = 0;
    int layers = 0;
    inf.getline(file, entry_nodes);
    inf.getline(file, layers);
    while(!inf.eof() )
    {
        vector<Node*> layer;
        while(inf.peek() != '%')
        {
            layer.push_back(new Node(inf));
        }
        hidden_.push_back(layer);
        inf.ignore();
        inf.ignore();
    }
    return true;
}

bool ANN::save()
{
    ofstream of;
    of.open("test_output");

    of << input_->size();
    of << hidden_[0].size();//

    for(std::vector<vector<Node*> >::iterator layer = hidden_.begin();
        layer != hidden_.end();
        layer++)
    {
        for(std::vector<Node*>::iterator node = layer->begin();
            node != layer->end();
            node++)
        {
          of << *node;
        }
        of << "%\n\n";
    }
    return true;
}
