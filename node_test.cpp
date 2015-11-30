/**
 *
 * Compile with the command <make node_test>
 */
#include"node.h"

#include<iostream>
#include<fstream>

using namespace std;

const string TESTFILE = "load_test_node";

int main()
{
    ifstream inf;
    inf.open( TESTFILE.c_str() );

    Node node(inf);

//    node.load(inf);

    cout << node << endl;

    inf.close();
    return 0;
}
