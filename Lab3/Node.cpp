/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.cpp
 * Author: govorkov
 * 
 * Created on October 17, 2017, 12:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

#include "Node.h"
#include "Rparser.h"

//declaration of basic functions associated with Node
Node:: Node(){
} 

Node::~Node(){
}

//functions that use private values of nodes

bool Node::canAddResistor() //check whether resistor can be added
{
    bool check;
    if (numRes < 5) check = true;
    else check = false;
    return check;
}

void Node::addResistor(int rIndex) //resistor adding
{
    resIDArray[numRes] = rIndex;
    numRes = numRes + 1;
}

void Node::print(int nodeIndex) //printing resistor array corresponding to certain node
{
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl;
    for (int i = 0; i < numRes; i++)
    {
        cout << "  ";
        (*ResistorArray[resIDArray[i]]).print();
       
    }

}

int Node::numres() const //returning internal variable - number of resistors currently attached to node
{
    return numRes;
}

/*void Node::del()
{
    for (int i=0; i < numRes; i++)
    {
        resIDArray[i]=-1;
    }
    numRes = 0;
}
*/

