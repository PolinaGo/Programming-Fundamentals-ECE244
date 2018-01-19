/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Resistor.cpp
 * Author: govorkov
 * 
 * Created on October 17, 2017, 12:37 PM
 */

#include "Resistor.h"
#include "Rparser.h"

//declaration of basic functions associated with resistor
Resistor:: Resistor(int rIndex_, string name_, double resistance_, int endpoint1_, int endpoint2_) {
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoint1_;
    endpointNodeIDs[1] = endpoint2_;
    rindex = rIndex_;
}

Resistor::~Resistor() {
}

//"get" functions that return private values of a resistor
int Resistor::getIndex() const {
    return rindex;
}
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

//assigns external resistance value to private
void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

//print of each resistor with given parameters
void Resistor::print(){
    cout << left << setw(20) << left <<name << setw(8) << right << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl; 
}