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

        //      void back_propograte( const vector<long double>* );
        long double operator()( 
                const vector<long double>&,
                const vector<long double>& );

        friend ostream& operator<<( ostream&, Node );
    private:
        long double w_;
};

ostream& operator<<( ostream&, Node );

#endif
