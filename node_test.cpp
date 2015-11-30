/**
 *
 * Compile with the command <make node_test>
 */
#include<iostream>
#include<fstream>
#include<vector>

#include"node.h"
#include"typedefs.h"

using namespace std;

const string TESTFILE = ".load_test_node";
const string HW_TEST = ".node_hw_test";

int main()
{
    cout 
        << "\nGeneric load-from-file test.  File name: " 
        << TESTFILE << endl
        << string( 80, '=' ) << endl
        << "\t\tExpected output be:" << endl
        << "1.001 1.11 9.09 -1.101 2 0.223@" << endl
        << string( 45, '_' ) << endl
        << "\t\tActual output:" << endl;

    ifstream inf;
    inf.open( TESTFILE.c_str() );

    Node* node = new Node(inf);

    cout << *node;

    inf.close();
    delete node;
    cout
        << string( 80, '=' ) << endl
        << "Test run of neural net based on homework sample:" << endl
        << string(80,'~') << endl;

    vector<int> inputs;
    inputs.push_back(


    return 0;
}
