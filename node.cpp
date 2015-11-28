/**
 * Node class definitions.
 *
 * @author Thomas R. Carrel
 * @file Node.cpp
 */
#include"node.h"

/** Node ctor.
 * @param w, The dummy weight associated with this node.  Pass zero, for input
 * nodes.
 */
Node::Node( long double w ) : 
    w_(w), weights_( (w==0) ? NULL : new vector<long double> )
{}

/**
 * Runs the functionality of the individual node.
 * @param data, Data points/values from either input or from previous layer.
 * @param weights, Weight of each edge from the nodes of the previous layer.
 * Should be NULL, on the input layer.
 */
long double Node::operator()( 
        const vector<long double>& data )
{
    assert( data.size() == weights_->size() );

    long double output = w_;
    int size = data.size();

    for( int ii = 0; ii < size; ii++ )
    {
        output += data[ii] * (*weights_)[ii];
    }

    return 1 / ( 1 + exp(-output) );
}

/**
 * The back propogation algorithm for training the ANN.
 */
void train()
{
}

/**
 * Overloaded insertion operator for debugging and for saving.
 */
ostream& operator<<( ostream& out, Node node )
{
    out << node.w_ << " ";
    unsigned i = node.weights_->size();
    for( unsigned ii = 0; ii < i; ii++ )
    {
        out << (*node.weights_)[ii];
        if( ii != i )
            out << " ";
    }

    return out;
}


