/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: govorkov
 *
 * Created on November 8, 2017, 5:26 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <iostream>
#include "ResistorList.h"

using namespace std;

//class node declaration
class Node {

private: 
    ResistorList resList; //stores all resistors
    int ID;
    double voltageUnknown;
    int set;
    Node * next;
    
public:
    
    //constructors and destructor
    Node();
    Node(int id);
    ~Node();
    
    //"get" function returning private value of the class
    Node * getNext();
    int getID();
    double getV();
    
    //set/unset voltage functions
     void setV(double v);   
     void unsetV();   
    
    //adds resistor to the node
    void addResistor(string name,double resistance, int n1, int n2);
    //prints node
    void printNode();
    
    //NodeList and Node are two very closely related classes while NodeList gives structure to Nodes
    friend class NodeList;   
};



#endif	/* NODE_H */
