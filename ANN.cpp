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
            Node* n = new Node(inf);
            layer.push_back( n );

            while( isspace( inf.peek() ) )
                inf.ignore();
        }

        if( layer.size() != 0 )
            hidden_.push_back( layer );

        //  Doing this here will trigger eof() before the next loop iteration,
        //if necessary.
        char dummy = 0;
        while( !inf.eof() && dummy != '%' )
            inf >> dummy;
    }

    for( unsigned i = 0; i < hidden_.size(); i++ )
    {
        vector<LD> W;
        edges_.push_back(W);
    }

    //cerr << layers << " " << hidden_.size() << endl;
    //cerr << "edges " << edges_.size() << endl;

    return layers == hidden_.size();
}

/** Used to save a trained ANN and backup during training.
 * The file name is predetermined.
 */
bool ANN::save(string fname)
{
    ofstream of;
    of.open( fname.c_str() );

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
    return true;
}

LD ANN::run()
{
    //auto inputs( input_->inputs() );

    //    cerr << "size " << inputs.size();
    unsigned last = 0;

    for (unsigned l = 0; l < hidden_.size(); l++)
    {
        edges_[l].clear();
        //        cerr << "l " << l << endl;
        for(unsigned j =0; j < hidden_[l].size(); j++)
        {
            //            cerr << "hl size << " << hidden_[l].size() << " edges " << edges_[l].size() << " ";

            //cerr << l;
            if( l != 0 )
            {
                LD value = hidden_[l][j]->activate( edges_[l-1] );
                assert( !isnan(value) );
                edges_[l].push_back( value );
            }
            else
            {
                LD value = hidden_[l][j]->activate( input_->inputs() );
                assert( !isnan(value) );
                edges_[l].push_back( value );
            }
        }
        last = l;
    }

    return edges_[last][ edges_[last].size() - 1];
}

void ANN::back_propagate( LD output )
{
    auto layer = hidden_.rbegin();
    auto datum = edges_.rbegin();

    vector<LD> *delta_p = NULL;
    vector<LD> *delta_c = new vector<LD>;
    for(unsigned i = 0; i < layer->size(); i++)
    {
        delta_c->push_back(
                (*layer)[i]->train( ALPHA
                    , output
                    , input_->expected() ) );
    }
    datum++;
    layer++;
    vector<LD> weights;

    stack<vector<LD>*> deltas;
    deltas.push(delta_c);


    //                cerr << "HI GRANDMA!!!" << endl;
    auto begin = hidden_.rend();// - 1;
    for(; layer != begin + 1; datum++, layer++)
    {

        //cerr << "!" << flush;

        if( delta_p != NULL)
            delete delta_p;
        delta_p = delta_c;
        delta_c = new vector<LD>;
        deltas.push( delta_c );
        unsigned stop = (layer != begin) ? layer->size() : input_->inputs().size();
        for(unsigned i = 0; i < stop; i++ ) 
        {                       
            //cerr << "&";
            //cerr << " size  " << stop << endl;
            //cerr << " layer " << i << endl;

            weights.clear();
            for( unsigned q = 0; q < (*(layer-1)).size(); q++ )
            {
                weights.push_back( (*(layer-1))[q]->get_weight(q) );
            }
            //         layer++;
            for( unsigned q = 0; q < delta_p->size(); q++ )
            {
                //cerr << "q" << (*delta_p)[q] << endl;
            }

            if( layer != begin ) 
            {
                deltas.top()->push_back(
                        (*layer)[i]->train(
                            (*datum)[i]
                            , *delta_p
                            , weights ));
            }
            else
            {
                //cerr << "OH SHIT" << endl;

                LD output = input_->inputs()[i];
                LD delta  = 0.0;
                LD factor = output * ( 1 - output );
                for( unsigned ii = 0; ii < delta_p->size(); ii++ )
                {
                    delta += (*delta_p)[ii] * weights[ii];
                }
                delta *= factor;
                deltas.top()->push_back(delta);
            }
        }
    }

    for( unsigned i = 0; i < hidden_.size(); i++ )
    {
        //cerr << "|";
        for( unsigned j = 0; j < hidden_[i].size(); j++ )
        {
            //cerr << "+";

            hidden_[i][j]->update_weights( ALPHA, edges_[i], (*deltas.top())[j] );
        }
        //cerr << endl;
        deltas.pop();
    }

    if( delta_p )
        delete delta_p;
    if( delta_c )
        delete delta_c;
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

    return !input_->is_loaded();
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
