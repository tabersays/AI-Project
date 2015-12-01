/**
 *   Definitions for the ANN object.
 *
 *   @file ANN.cpp
 *
 *   @author Michael Taylor
 *   @author Matt ?
 *   @author Thomas Russel Carrel
 */



#include"ANN.h"

/** ANN ctor
 * @param file The (un)trained ANN to load.
 */
ANN::ANN( char* file )
{
    load(file);
}

/** Loads a saved ANN.
 * @param file The name (and optionally, path) to load.
 */
bool ANN::load( char* file )
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

/** Used to save a trained ANN and backup during training.
 * The file name is predetermined.
 */
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
