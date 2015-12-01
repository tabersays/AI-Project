/**
 * Node class definitions.
 *
 * @author Thomas R. Carrel
 * @file node.cpp
 */
#include"node.h"

/** Node ctor.
 * @param w The dummy weight associated with this node.
 */
Node::Node( LD w ) : w_(w)
{}

Node::Node( istream& infile ) 
{
    if( load(infile) )
        return;

    //Load failed.
    w_ = 1;
}

/**
 * Runs the functionality of the individual node.
 * @param data Data points/values from the previous layer.
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
 * @param alpha The alpha value used to adjust weights.
 * @param output This is the value that was output from the pervious run from
 * the training data.
 * @param expected This is the value that was expected from the output layer.
 * @param input The inputs that were given with the recognition of the previous
 * training input.
 */
LD Node::train( LD alpha, LD output, LD expected, vector<LD>& input ) 
{
    LD delta =  output * ( 1 - output ) * (expected - output);

    //  Dummy input is always equal to 1 and is, therefore, implicit in this
    //calculation.
    w_ += alpha * delta;

    for( unsigned i = 0; i < weights_.size(); i++ )
    {       
        weights_[i] += alpha * delta * input[i];
    }

    return delta;
}


/**
 * The back propogation algorithm for training the ANN.  There are two versions
 * of this function.  This one is overloaded to train the hidden layers.
 *
 * @param alpha The alpha value used to adjust weights.
 * @param output This is the value that was output for the pervious run from
 * the training data.
 * @param y A vector containing the deltas passed from training subsequent layers
 * of the ANN.
 * @param inputs The vector of inputs that were previously passed in for
 * recognition.
 */
LD Node::train( LD alpha, LD output, vector<LD>& y, vector<LD>& inputs )
{
    assert( y.size() == weights_.size() );

    LD delta  = 0.0;//w_;
    LD factor = output * ( 1 - output );
    for( unsigned ii = 0; ii < y.size(); ii++ )
    {
        delta += y[ii] * weights_[ii];
    }
    delta *= factor;

    w_ += alpha * delta;
    for( unsigned ii = 0; ii < weights_.size(); ii++ )
    {
        weights_[ii] += ( alpha * inputs[ii] * delta );
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
        if( ii != (i - 1) )
            out << " ";
    }
    out << "@\n";

    return out;
}

/**
 * Reads in the saved weights corresponding to a single node.
 */
bool Node::load( istream& in )
{
    weights_.clear();

    if( !in.good() ) //EOF? File did not open, etc...
        return false;

    in >> w_;
    LD n = 0;

    while( in.peek() != '@' )
    {
        in >> n;
        weights_.push_back(n);
    }
    in.ignore();
    return true;
}

/** Destructor, empties the weights vector.
 */
Node::~Node(void)
{
    weights_.clear();
}
