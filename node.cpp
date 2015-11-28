/**
 * Node class definitions.
 *
 * @author Thomas R. Carrel
 * @file Node.cpp
 */
#include"node.h"

/** Node ctor.
 * @param w, The dummy weight associated with this node.
 */
Node::Node( long double w ) : w_(w)
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
    assert( data.size() == weights_.size() );

    long double output = w_;
    int size = data.size();

    for( int ii = 0; ii < size; ii++ )
    {
        output += data[ii] * weights_[ii];
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
 *
 *   A node is represented as a single line of numerical values seperated by
 * spaces.  The first value in the line is the dummy weight associated with
 * the node, followed by space-delineated values for the weights for each edge
 * into the node from the previous layer.  The number of entries after the
 * dummy weight should be equal to the number of nodes in the previous layer,
 * this is unfortunately difficult to test during loading.
 */
ostream& operator<<( ostream& out, Node node )
{
    out << node.w_ << " ";
    unsigned i = node.weights_.size();
    for( unsigned ii = 0; ii < i; ii++ )
    {
        out << node.weights_[ii];
        if( ii != i )
            out << " ";
    }
    out << "@\n";

    return out;
}

/**
 * Reads in the saved weights corresponding to a single node.
 */
istream& operator>>( istream& in, Node node )
{
    if( !in.good() ) //EOF? File did not open, etc...
        return in;

    in >> node.w_;
    long double n = 0;

    while( in.peek() != '@' )
    {
        in >> n;
        node.weights_.push_back(n);
    }
    return in;
}
