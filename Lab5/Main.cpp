/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Main.cpp
 * Author: Govorkova Polina
 *
 * Created on November 16, 2017, 4:51 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

#include "TreeDB.h"
#include "DBentry.h"

using namespace std;

//additional basic functions responsible for error message print
void error1() {
    cout << "Error: entry already exists" << endl;
}
void error2() {
    cout << "Error: entry does not exist" << endl;
}

//main function that runs parser and executes according to requirements
int main() {

//Declaration of the new Binary Tree structure
    TreeDB * tree = new TreeDB();

//Declaration of inputs and helpful parameters
    bool existence;
    string name;
    int index;
    string status;
    bool active = false;
    string line, command; //input line, command for the function
    cout << "> "; //output requirement  
    getline (cin, line); //getting the line from the input

    while ( !cin.eof () ) { //while there are more lines to read to do the following

        stringstream lineStream (line); //make srtingStream from the line

        lineStream >> command; //read the first word to be command

        if (command == "insert") {//insert command - reads user input, inserts new node into the tree if the entry doesn't exist already
            
            lineStream >> name >> index >> status;
            if (status == "active") active = true; 
            
            existence = tree->find(name, -5);
            if (!existence) { //check for existence
                existence = tree->insert(name, index, active);
                cout << "Success" << endl;
            }
            else {
                error1(); //error case
            }      
        }
        else if (command == "find") {//find command - searches the tree for a given name, print information about it if found
            lineStream >> name;            
            existence = tree->find(name, 0); //check for existence, prints if found
            if (!existence) error2(); //error case
        }
        else if (command == "remove") {//remove command - removes a node with given name if found
            lineStream >> name;
            existence = tree->find(name, -5);
            if (!existence) error2(); //error case
            else {
                existence = tree->remove(name);
            }
        }
        else if (command == "printall") {//command prints all the nodes from smallest to largest
            index = tree->printProbes("nothing", 0);
        }
        else if (command == "printprobes") {//command prints amount of probes examined while searching for given node if exists
            lineStream >> name;
            existence = tree->find(name, -5);
            if (!existence) error2(); //error case
            else {
                index = tree->printProbes(name, 1);
                cout << index << endl;
            }
        }
        else if (command == "removeall") {//command that empties the tree
            tree->clear();
            cout << "Success" << endl;
        }
        else if (command == "countactive") {//command that counts active nodes
            tree->countActive();
        }
        else if (command == "updatestatus") {//command that allows to update status to of a given node if exists
            lineStream >> name >> status;
            if (status == "active") existence = tree->find(name, 1);
            else existence = tree->find(name, -1);
            if (!existence) error2(); //error case       
        }
        //setting helpful parameters to initial conditions for new user input
        active = false;
        existence = false;
        cout << "> "; //format requirement
        getline (cin, line);
    } // End input loop until EOF.

    //deletes existing binary tree before the end of the program
    tree->clear();
    delete tree;
    tree = NULL;
return 0; //returns zero as the successful end of execution
}