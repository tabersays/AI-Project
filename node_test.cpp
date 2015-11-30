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
        << string(80,'~') << endl
        << "\tFile name:\t" << HW_TEST << endl;

    inf.open(HW_TEST);

    vector<LD> inputs;
    inputs.push_back(0.2);
    inputs.push_back(0.8);
    vector<LD> expected;
    expected.push_back(0.1);
    expected.push_back(0.9);

    cout
        << "\tInputs:\t" << inputs[0] << ", " << inputs[1] << endl;

    vector<Node*> layers[2];

    layers[0].push_back( new Node(inf) );
    layers[1].push_back( new Node(inf) );
    layers[1].push_back( new Node(inf) );
    cout
        << "\tLoaded nodes:" << endl
        << *layers[0][0]
        << *layers[1][0]
        << *layers[1][1] << endl
        << string( 80, '=' ) << endl;

    vector<LD> mid_layer;
    mid_layer.push_back( layers[0][0]->operator()(inputs) );
    cout << "Output from first hidden layer:\n\t\t\t" << mid_layer[0] << endl;

    vector<LD> outputs;
    outputs.push_back( layers[1][0]->operator()(mid_layer) );
    outputs.push_back( layers[1][1]->operator()(mid_layer) );

    cout << "\tOutputs:\t" << outputs[0] << "\t" << outputs[1] << endl;

    vector<LD> mid_layer_deltas;
    mid_layer_deltas.push_back(
            layers[1][0]->train( 0.01, outputs[0], expected[0], mid_layer[0] ) );
    mid_layer_deltas.push_back(
            layers[1][1]->train( 0.01, outputs[1], expected[1], mid_layer[1] ) );

    cout << "\tDeltas:\t\t" << mid_layer_deltas[0] << "\t" << mid_layer_deltas[1] << endl;

    cout << "1st hidden layer delta:\t" <<
        layers[0][0]->train( 0.01, mid_layer[0], mid_layer_deltas, inputs ) << endl;

    cout
        << string( 80, '=' ) << endl
        << "There are rounding errors here:" << endl
        << "\tw3:\t" << *layers[0][0]
        << "\tw4:\t" << *layers[1][0]
        << "\tw5:\t" << *layers[1][1] << endl;

    return 0;
}
