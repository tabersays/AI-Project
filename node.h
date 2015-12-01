/**
 * Node class declaration.
 *
 * @author Thomas R. Carrel
 * @file node.h
 */

#ifndef __NODE_H__
#define __NODE_H__

#include<cassert>

#include<iostream>
using std::ostream;
using std::istream;

#include<cmath>
using std::exp;

#include<vector>
using std::vector;

#include"typedefs.h"

/** All nodes are in either the hidden or output layers, nodes in the input
 * layer will simply be the result of a single image processing function/object
 * generating a vector of numerical inputs for the subsequent layers.
 */
class Node
{
    public:
        Node( LD );
        Node( istream& );
        ~Node( void );

        LD operator()( const vector<LD>& );

        LD train( LD, LD, LD, vector<LD>& );
        LD train( LD, LD, vector<LD>&, vector<LD>& );

        bool load( istream& );

        friend ostream& operator<<( ostream&, Node );
    private:
        LD w_; ///>The dummy weight associated with this node.
        vector<LD> weights_; /**> The weights of all the connection
                                        from the nodes in the previous layer
                                        of the ANN. **/
};

/** For outputing a node to the screen or to a file. */
ostream& operator<<( ostream&, Node );

#endif
