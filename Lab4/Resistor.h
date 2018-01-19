/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Resistor.h
 * Author: govorkov
 *
 * Created on November 8, 2017, 5:28 PM
 */

#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

//class resistor declaration
struct Resistor 
{
    
private:
   double resistance=0.0; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   Resistor * next; 
   
public:

   Resistor(string name_,double resistance_,int endpoint1_, int endpoint2_);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects
   
   ~Resistor();

    //"get" function returning private value of the class
    int getEndpoint1() const;    
    int getEndpoint2() const;    
    string getName() const;
    double getResistance() const;
    Resistor * getNext();
    
    void setResistance(double resistance_); // set the value of resistance
    void print(); //prints resistor
    
    //Resistor list and Resistor are two very closely related classes while Resistor list gives structure to Resistors
    friend class ResistorList;
};


ostream& operator << (ostream&, const Resistor&);

#endif