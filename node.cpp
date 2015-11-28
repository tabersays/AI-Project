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
Node::Node( LD w ) : w_(w)
{}

/**
 * Runs the functionality of the individual node.
 * @param data, Data points/values from the previous layer.
 */
LD Node::operator()( const vector<LD>& data )
{
    assert( data.size() == weights_.size() );

    LD output = w_;
    int size = data.size();

    for( int ii = 0; ii < size; ii++ )
    {
        output += data[ii] * weights_[ii];
    }

    return 1 / ( 1 + exp(-output) );
}

/**
 * The back propogation algorithm for training the ANN.  There are two versions
 * of this function.  This one trains the output layer.
 *
 * @param alpha, The alpha value used to adjust weights.
 * @param output, This is the value that was output for the pervious run from
 * the training data.
 * @param expected, This is the value that was expected from the output layer.
 */
LD Node::train( LD alpha, LD output, LD expected ) 
{
    LD delta =  output * ( 1 - output ) * (expected - output);

    //  Dummy weight is always equal to 1 and is, therefore, implicit in this
    //calculation.
    w_ = w_ + (alpha * delta);

    return delta;
}


/**
 * The back propogation algorithm for training the ANN.  There are two versions
 * of this function.  This one is overloaded to train the hidden layers.
 *
 * @param alpha, The alpha value used to adjust weights.
 * @param output, This is the value that was output for the pervious run from
 * the training data.
 * @param y, A vector contain the values pass from training subsequent layers
 * of the ANN.
 */
LD Node::train( LD alpha, LD output, vector<LD>& y )
{
    assert( y.size() == weights_.size() );

    LD factor = output * ( 1 - output );
    LD delta;

    for( unsigned ii = 0; ii < y.size(); ii++ )
    {
        delta += y[ii] * weights_[ii];
    }
    delta *= factor;

    for( unsigned ii = 0; ii < weights_.size(); ii++ )
    {
        weights_[ii] += ( alpha * output * delta );
    }
   
    return delta;
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
    LD n = 0;

    while( in.peek() != '@' )
    {
        in >> n;
        node.weights_.push_back(n);
    }
    in.ignore();
    return in;
}
