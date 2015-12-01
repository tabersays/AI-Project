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

    unsigned layers = 0;
    inf >> input_layer_size_;
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

        if( layer.size() != 0 )
            hidden_.push_back( layer );
        vector<LD> W;
        edges_.push_back(W);

        //  Doing this here will trigger eof() before the next loop iteration,
        //if necessary.
        char dummy = 0;
        while( !inf.eof() && dummy != '%' )
            inf >> dummy;
    }

    cerr << layers << " " << hidden_.size() << endl;

    return layers == hidden_.size();
}

/** Used to save a trained ANN and backup during training.
 * The file name is predetermined.
 */
bool ANN::save()
{
    ofstream of;
    of.open("test_output");

    char per = '%';

    // Size of the input layer.
    if( input_ )
        of << input_->size(); 
    else
        of << input_layer_size_;
    of << endl;

    of << hidden_.size() << endl; // Number of layers.

    for( auto i = hidden_.begin(); i != hidden_.end(); i++ )
    {
        for( auto j = i->begin(); j != i->end(); j++ )
        {
            of << **j;
        }
        of << per << endl;
    }
    /*
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
        of << per << endl;
    }
    */
    return true;
}

LD ANN::run()
{
  return 0.0;
}

void ANN::back_propagate( LD )
{
}

bool ANN::load_image( string filename )
{
    if( input_ )
    {
        input_->new_image( filename );
    }
    else
    {
        input_ = new Image_Loader( filename );
    }

    return !input_.is_loaded();
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
    hidden_.clear();
}
