/**
 * Node class definitions.
 *
 * @author Thomas R. Carrel
 * @author Mark Moniz
 * @file node.cpp
 */
#include"node.h"

using namespace std;

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
LD Node::activate( const vector<LD>& data )
{
//    cerr << "dat " << data.size() << "\twght " << weights_.size() << endl;
//    cerr << "w0 " << w_ << "\tw1 " << weights_[0] << endl;

    assert( data.size() == weights_.size() );

    LD output = w_;
    int size = data.size();

    for( int ii = 0; ii < size; ii++ )
    {
//        cerr << ".";
        assert( data[ii] != 0 );
        LD w = (!isnan(weights_[ii]) ? weights_[ii] : -0.000011);
        output += data[ii] * w;
    }

    /*
    LD final_output = (LD)1.0;
    LD denom = ( (LD)1.0 + (LD)exp(-output) );
    //    cerr << output;
    assert( denom != 0 );
    //    assert( !isnan(denom) );
    //    assert( !isnan( final_output / denom ) );
    */
    //return final_output / denom;

    return 1 / (1 + abs(output) );
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
LD Node::train( LD /*alpha*/, LD output, LD expected ) 
{
    return output * ( 1 - output ) * (expected - output);

    //  Dummy input is always equal to 1 and is, therefore, implicit in this
    //calculation.
    /*
       w_ += alpha * delta;

       for( unsigned i = 0; i < weights_.size(); i++ )
       {       
       weights_[i] += alpha * delta * input[i];
       }

       return delta;
       */
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
LD Node::train( LD output, vector<LD>& y, vector<LD>& weights )
{
    //cerr << "y " << y.size() << " weights " << weights.size() << endl;
    assert( y.size() == weights.size() );
    assert( !isnan(output) );

    LD delta  = 0.0;//w_;
    LD factor = output * ( 1 - output );
    for( unsigned ii = 0; ii < y.size(); ii++ )
    {
        delta += y[ii] * weights[ii];
    }
    delta *= factor;

    assert( !isnan(delta) );

    return delta;
}


void Node::update_weights( LD alpha, vector<LD>& inputs, LD delta )
{
    w_ += alpha * delta;
    for( unsigned ii = 0; ii < weights_.size(); ii++ )
    {
        //       assert( !isnan( inputs[ii] ) ); //update_weights
        LD x = (isnan(inputs[ii]) ? -0.000101010 : inputs[ii]);
        //        LD x = inputs[ii];
        weights_[ii] += ( alpha * x * delta );
        //        assert( !isnan( weights_[ii] ) ); //update_weights
    }
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
    out << setprecision(PREC) << node.w_ << " ";
    unsigned i = node.weights_.size();
    for( unsigned ii = 0; ii < i; ii++ )
    {
        LD w = isnan(node.weights_[ii]) ? 0.00001 : node.weights_[ii];
        out << setprecision(PREC) << w;
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
        /*
        if( n != 0 )
            cerr << n << "-";
        assert( n != 0 );
        */

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
