/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: govorkov
 *
 * Created on November 8, 2017, 5:41 PM
 */

#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include "Resistor.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

//class declaration
class ResistorList {
private:
    Resistor * head;
    int count;
    
public:

    //constructor and destructor
    ResistorList();
    ~ResistorList();

    //"get" function returning private value of the class
    int getCount ();
    
    //adds resistor to the list
    void addResistor(string name,double resistance, int n1, int n2);

    //searches list for existence of resistor
    bool resSearch(string name);
    
    //modifies resistance
    double modify (string name, double resistance);
    
    //prints individual resistor and the whole list
    void printResistor (string name);
    void printResistorList();

    //assistant to NodeList solve function, calculates term 2, sum of Vi/Ri
    double term2();
    
    //deletes individual resistor and resistor list
    void deleteR (string name);   
    void deleteRall ();  
    
    //Resistor list and node are two very closely related classes while Resistor list type variable is one of the primary private components of node
    friend class Node;
    //to allow quick access to data contained in ResistorList and Resistor
    friend class NodeList;
};



#endif /* RESISTORLIST_H */

