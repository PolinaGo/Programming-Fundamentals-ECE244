/* 
 * File:   Node.cpp
 * Author: Govorkova Polina
 * 
 * Created on November 8, 2017, 5:26 PM
 */

#include "Node.h"

 //default constructor
Node::Node() {
    set = 0;
    voltageUnknown = 0;
    ID = 0;
    next = NULL;
}

//constructor given node id
Node::Node(int id) {
    set = 0;
    voltageUnknown = 0;
    ID = id;
    next = NULL;
}

//default destructor
Node::~Node() {
}

//"get" functions that return private values of a resistor
Node * Node :: getNext() {
    return next;
}
double Node :: getV() {
    return voltageUnknown;
}
int Node :: getID() {
        return ID;
}
//sets voltage
void Node :: setV(double v) {
    set = 1;
    voltageUnknown = v;
}

//unsets voltage
void Node :: unsetV() {
    set = 0;
    voltageUnknown = 0;
}

//adds resistor to the following node
void Node :: addResistor(string name,double resistance, int n1, int n2) {
    resList.count = resList.count +1;
    resList.addResistor(name, resistance, n1, n2);
}

//prints given node
void Node :: printNode() {
    cout << "Connections at node " << ID << ": " << resList.count << " resistor(s)" << endl;
            resList.printResistorList();
}