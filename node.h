/**
 * Node class declaration.
 *
 * @author Thomas R. Carrel
 * @file Node.h
 */

#ifndef __NODE_H__
#define __NODE_H__

#include<cassert>
#include<iostream>
#include<cmath>

#include<vector>

using std::vector;
using std::exp;
using std::ostream;
using std::istream;

/** All nodes are in either the hidden or output layers, nodes in the input
 * layer will simply be the result of a single image processing function/object
 * generating a vector of numerical inputs for the subsequent layers.
 */
class Node
{
    public:
        Node( long double );
        ~Node();

        long double operator()( 
                const vector<long double>& );

        void train();

        friend ostream& operator<<( ostream&, Node );
        friend istream& operator>>( istream&, Node );
    private:
        long double w_; ///>The dummy weight associated with this node.
        vector<long double> weights_; /**> The weights of all the connection
                                        from the nodes in the previous layer
                                        of the ANN. **/
};

/** For loading a node from file.*/
istream& operator>>( istream&, Node );
/** For outputing a node to the screen or to a file. */
ostream& operator<<( ostream&, Node );

#endif
