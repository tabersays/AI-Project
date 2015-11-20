/**
 * Node class declaration.
 *
 * @author Thomas R. Carrel
 * @file Node.h
 */

#ifndef __NODE_H__
#define __NODE_H__

#include<vector>

using std::vector;

class Node
{
    public:
        Node();

        double operator()( const vector<double>&, const vector<double>& );
    private:
        double input_layer( const vector<double>& );
        double hidden_layer( const vector<double>&, const vector<double>& );
};
#endif
