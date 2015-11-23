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
        const vector<long double>& data,
        const vector<long double>& weights )
{
    assert( data.size() == weights.size() );

    long double output = w_;
    int size = data.size();

    for( int ii = 0; ii < size; ii++ )
    {
        output += data[ii] * weights[ii];
    }

    return 1 / ( 1 + exp(-output) );
}


/**
 * Overloaded insertion operator for debugging and for saving.
 */
ostream& operator<<( ostream& out, Node node )
{
    out << node.w_;

    return out;
}
