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

class Node
{
    public:
        Node( long double );
        ~Node();

        long double operator()( 
                const vector<long double>& );

        void train();

        friend ostream& operator<<( ostream&, Node );
    private:
        long double w_; ///>The dummy weight associated with this node.
        vector<long double>* weights_; /**> The weights of all the connection
                                         from the nodes in the previous layer
                                         of the ANN. **/
};

ostream& operator>>( ostream&, Node );
ostream& operator<<( ostream&, Node );

#endif
