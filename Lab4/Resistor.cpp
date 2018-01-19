
/* 
 * File:   Resistor.cpp
 * Author: Govorkova Polina
 * 
 * Created on November 8, 2017, 5:28 PM
 */

#include "Resistor.h"
#include "Rparser.h"

//constructor
Resistor:: Resistor(string name_, double resistance_, int endpoint1_, int endpoint2_) {
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoint1_;
    endpointNodeIDs[1] = endpoint2_;
    next = NULL;
}

//default destructor
Resistor::~Resistor() {
}

//"get" functions that return private values of a resistor
int Resistor::getEndpoint1() const {
    return endpointNodeIDs[0];
}
int Resistor::getEndpoint2() const {
    return endpointNodeIDs[1];
}
string Resistor::getName() const {
    return name;
}
double Resistor::getResistance() const {
    return resistance;
}
Resistor * Resistor :: getNext() {
    return next;
}

//assigns external resistance value to private
void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

//print of each resistor with given parameters
void Resistor::print(){
    cout << setw(21) << left << name << setw(8) << right << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl; 
}