/**
 * Node class definitions.
 *
 * @author Thomas R. Carrel
 * @file Node.cpp
 */

#include"node.h"

/** Node ctor.  Only one really needs to be created but multiple can safely be
 * run concurrently.
 */
Node::Node()
{
}

/**
 * Runs the functionality of the individual node.
 * @param data, Data points/values from either input or from previous layer.
 * @param weights, Weight of each edge from the nodes of the previous layer.
 * Should be NULL, on the input layer.
 */
double Node::operator()( 
        const vector<double>* data,
        const vector<double>* weights )
{
    return (weights)?
        hidden_layer( *data, *weights ):
        input_layer( *data );
}

double Node::input_layer( const vector<double>& data )
{
    double output;

    return output;
}

double Node::hidden_layer(
        const vector<double>& data,
        const vector<double>& weights )
{
    double output;

    return output;
}
