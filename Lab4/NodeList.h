/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: govorkov
 *
 * Created on November 8, 2017, 5:41 PM
 */

#ifndef NODELIST_H
#define NODELIST_H

#include <iostream>
#include "Node.h"

//class declaration
class NodeList {
private:
    Node * head;
    
public:
    
    //constructor and destructor
    NodeList();
    ~NodeList();
    
    //adds resistor to network
    void addResistor (string name, double resistance, int n1, int n2);   

    //deletes the whole network
    void deleteList();
    //deletes resistor
    void deleteResistor(string name);   
    //deletes all resistors, saves nodes
    void deleteRall(); 
    //sets all nodes to initial condition: unset, v=0
    void unsetAndZero (); 
    
    //checks existence of node and resistor respectively
    bool findNode(int n);
    bool resSearch(string name);    
    
    //prints node
    void printNode(int n);
    //prints all nodes
    void printNodes();

//    void printNodeIDS();

    //prints info about resistor
    void printR(string name);
    
    //sets and unsets voltage
    void setV(int n, double voltage);
    void unsetV(int n);
    
    //modifies resistor
    void modify(string name, double resistance);
    
    //solves the network
    void solve();
   
    //functions assistant to solve command
    bool areAllSet(); //checks if there is voltage source
    double term11 (Node * temp); //sum of Vi/Ri for given node
    void setTo0 (); //changes all unset voltages to 0

    //get voltage of given node
    double getVoltage (int n);
};

#endif /* NODELIST_H */

