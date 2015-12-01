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

ANN::ANN() : input_(NULL) {}

/** Loads a saved ANN.
 * @param file The name (and optionally, path) to load.
 */
bool ANN::load( char* file )
{
    ifstream inf;
    inf.open( file );

    if( inf.fail() )
    {
        return false;
    }

    int entry_nodes = 0;
    unsigned layers = 0;
    inf >> entry_nodes;
    inf >> layers;

    while( !inf.eof() )
    {
        //Ignore leading whitespace (newline)
        while( isspace( inf.peek() ) )
            inf.ignore();

        vector<Node*> layer;
        while( !inf.eof() && inf.peek() != '%' )
        {
            //            cerr << inf.peek();
            Node* n = new Node(inf);
            layer.push_back( n );

            while( isspace( inf.peek() ) )
                inf.ignore();
        }


        hidden_.push_back( layer );
        vector<LD> W;
        edges_.push_back(W);

        char dummy = 0;
        while( !inf.eof() && dummy != '%' )
            inf >> dummy;
    }

    unsigned o_layer = hidden_.size() - 1;
    output_ = hidden_[o_layer];
    for( unsigned i = 0; i < hidden_[o_layer].size(); i++ )
        hidden_[o_layer][i] = NULL;
    hidden_.pop_back();

    return layers == hidden_.size();// + 1;
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

/**
 * ANN dtor
 *
 * THIS IS UNTEST SO ANY SEG FAULTS ARE LIKELY TO BE FROM HERE.
 */
ANN::~ANN( void )
{
    if( input_ )
        delete input_;

    for( unsigned k = 0; k < hidden_.size(); k++ )
    {
        for( unsigned l = 0; l < hidden_[k].size(); l++ )
        {
            if( hidden_[k][l] )
                delete hidden_[k][l];
        }
        hidden_[k].clear();
    }

    for( unsigned m = 0; m < output_.size(); m++ )
        if( output_[m] )
            delete output_[m];
    output_.clear();
}
