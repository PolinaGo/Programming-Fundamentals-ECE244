/* 
 * File:   Rparser.cpp
 * Author: Govorkova Polina
 * 
 * Created on October 17, 2017, 12:37 PM
 */

#include "Resistor.h"
#include "Node.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

#include "Rparser.h"

using namespace std;
#define MIN_NODE_NUMBER 0
#define MIN_RES_NUMBER 0

//additional basic functions responsible for error message print
void error1_maxVal() {
	cout << "Error: maxVal arguments must be greater than 0" << endl;
}
	
void error2_resNotFound(string name) {
	cout << "Error: resistor " << name << " not found" << endl;
}

void error3_notInRange(int number, int maxNode) {
    	std::cout.precision(2);
	cout << "Error: node " << number << " is out of permitted range 0-" << (maxNode-1) << endl;
}

void error4_resFull() {
	cout << "Error: resistor array is full" << endl;
}

void error5_nodeFull() {
	cout << "Error: node is full" << endl;
}

void error6(string name) {
	cout << "Error: resistor " << name << " already exists" << endl;
}

void error7(int n1) {
	cout << "Error: both terminals of resistor connect to node " << n1 << endl;
}

//function that searches for resistor information by its name
int resSearch(string name, int resCount) {
    int index = -1;
    for (int i=0; i<resCount; i++)
    {
        if (ResistorArray[i]->getName() == name) index = i;
    }
    return index;
}

//main function of the program, coordinates the rest of the functions
int Rparser (void) {
    
     //variables for input information   
    string line, command, second;
    string name;
    int n1, n2;
    double resistance;
    
    int resCheck=0; //current amount of resistors in network
    
    int maxNode, maxRes; //manually set boundaries
    maxNode = 0;
    maxRes  = 0;
    
    cout << "> "; //output requirement   
    getline (cin, line); //getting the line from the input

    
    while ( !cin.eof () ) { //while there are more lines to read to do the following
        stringstream lineStream (line), second (line); //make string stream from the line

        lineStream >> command; //read the first word to be command

        if (command == "insertR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) {}
            else {
                lineStream >> name; //reading resistor name to insert and checking it for the errors
                if (lineStream.fail()) {}
                else if (name == "all") {}
                else {
                    lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                    if (lineStream.peek()==EOF) {}
                    else {
                        lineStream >> resistance; //reading resistance and checking it for the errors
                        if (lineStream.fail()) {}
                        else if ((lineStream.peek()!=' ')&&(lineStream.peek()!=EOF)) {}
                        else if (resistance < 0) {}
                        else {
                            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                            if (lineStream.peek()==EOF) {}
                            else {
                                lineStream >> n1; //reading nodeid1 and checking for the errors
                                if (lineStream.fail()) {}
                                else if ((lineStream.peek()!=' ')&&(lineStream.peek()!=EOF)) {}
                                else if ((n1 < 0) || (n1 > maxNode-1)) error3_notInRange(n1, maxNode);
                                else {
                                    lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                                    if (lineStream.peek()==EOF) {}
                                    else {
                                    lineStream >> n2;     //reading nodeid2 and checking for the errors   
                                    if (lineStream.fail()) {}
                                    else if ((lineStream.peek()!=' ')&&(lineStream.peek()!= EOF)) {}
                                    else if ((n2 < 0) || (n2 > maxNode-1)) error3_notInRange(n2, maxNode);
                                    else if (resCheck == maxRes) error4_resFull();
                                    else if (NodeArray[n1].canAddResistor()!=true) error5_nodeFull();
                                    else if (NodeArray[n2].canAddResistor()!=true) error5_nodeFull();
                                    else if (resSearch(name, resCheck) != -1) error6(name);
                                    else if (n1 == n2) error7(n1);
                                    else 
                                    {
                                        lineStream >> ws;
                                        if (lineStream.peek()!= EOF) {}
                                        else {
                                            //all the requirements are met. Adding resistor
                                            cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance << " Ohms " << n1 << " -> " << n2 << endl;
                                            ResistorArray[resCheck] = new Resistor(resCheck, name, resistance, n1, n2);
                                            //Adding resistor information to node storage
                                            NodeArray[n1].addResistor(resCheck);
                                            NodeArray[n2].addResistor(resCheck);
                                            resCheck = resCheck + 1;
                                        }
                                    }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lineStream.clear();//erasing the flags
        }
        else if (command == "modifyR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) {}
            else {
                lineStream >> name;//reading resistor name to modify and checking for errors
                if (lineStream.fail()) {}
                else if (name == "all") {}
                else if (lineStream.eof()) {}
                else {
                    lineStream >> resistance;//reading resistance to modify and checking for errors
                    if (lineStream.fail()) {}
                    else if ((lineStream.peek()!=' ')&&(lineStream.peek()!= EOF)) {}
                    else if (resistance < 0) {}
                    else {
                        lineStream >> ws;
                        if (lineStream.peek()!= EOF) {}
                        else {
                            int t = resSearch(name, resCheck);
                            if (t==-1) error2_resNotFound(name);
                            else
                            {
                                //all the requirements are met. Modifying resistor
                                cout << "Modified: resistor " << name << " from " << fixed << setprecision(2) << ResistorArray[t]->getResistance() << " Ohms to " << fixed << setprecision(2) << resistance << " Ohms" << endl;
                                ResistorArray[t]->setResistance(resistance); //changing resistor resistance
                            }
                        }
                    }
                }
            }
            lineStream.clear();
        }
        else if (command == "deleteR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) {}
            else {
                lineStream >> name;//reading resistor name and checking for errors
                lineStream >> ws;
                if (lineStream.fail()) {}
                else if (lineStream.peek()!=EOF) {}
                else if (name == "all") 
                {
                    //all the requirements are met. Deleting all resistors
                    cout << "Deleted: all resistors" << endl;// ALL case  
                    for (int i=0; i < resCheck; i++) { //deleting information stored in each element
                        delete ResistorArray[i];                          
                    }
                    delete [] ResistorArray; //deleting current resistor array
                    ResistorArray = new Resistor* [maxRes]; //creating new empty resistor array
                    delete [] NodeArray; //deleting current node array
                    NodeArray = new Node [maxNode]; //creating new empty node array 
                    resCheck = 0;
                }
            lineStream.clear();
            }
        }
        else if (command == "printR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) {}
            else {
                lineStream >> name;//reading resistor name and checking for errors
                lineStream >> ws;
                cout << "Print: " << endl;
                if (lineStream.peek()!=EOF) {}
                else if (name == "all") 
                {
                    //printing all resistors
                    for (int i=0; i<resCheck; i++)
                    {
                        ResistorArray[i]->print();
                    }
                }
                else 
                {
                    //searching for resistor and then printing information about it
                    int k = resSearch(name, resCheck);
                    if (k==-1) error2_resNotFound(name);
                    else ResistorArray[k]->print();
                }
            }
        }
        else if (command == "printNode") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) {}
            else {
                lineStream >> n1;//reading nodeID and checking for errors
                if (lineStream.fail()) //check for ALL case
                {
                    second >> command >> name; //reading from the complementary to lineStream line that contains string extention after "printNode"
                    second >> ws;
                    if ((name == "all")&&((second.peek()==EOF)))
                    {
                        //all the requirements are met. Printing all nodes
                        cout << "Print: " << endl;
                        for (int i = 0; i < maxNode; i++)
                        {
                            NodeArray[i].print(i);
                        }
                    } //ALL case
                    else {};
                }
                else if ((lineStream.peek()!=' ')&&(lineStream.peek()!= EOF)) {}
                else {
                    lineStream >> ws;
                    if ((n1 < 0) || (n1) > maxNode-1) error3_notInRange(n1, maxNode);
                    else if (lineStream.peek()!=EOF) {}
                    else 
                    {
                        //all the requirements are met. Printing Node
                        cout << "Print: " << endl;
                        NodeArray[n1].print(n1);
                    }
                }
            }
        lineStream.clear();
        }
        
        else if (command == "maxVal" ) {
            lineStream >> n1;
            if (n1<=0) error1_maxVal();
            else {
                lineStream >> n2;
                lineStream >> ws;
                if (lineStream.peek()!=EOF) {}
                else {
                    if (!(maxNode==0)) { //if there is already an existing network, delete it first
                        delete [] NodeArray;
                    for (int i=0; i < resCheck; i++) {
                        delete ResistorArray[i];                             
                    }
                    }
                    delete [] ResistorArray;
                    maxRes = n2;
                    maxNode = n1+1;
                    
                    //creating new network
                    NodeArray = new Node[maxNode]; 
                    ResistorArray = new Resistor* [maxRes]; 
                    
                    resCheck = 0;
                    
                    cout << "New network: max node number is " << n1 << "; max resistors is " << n2 << endl; 
                }
            }
        } //maxVal
        cout << "> "; //format requirement
        getline (cin, line);
    } // End input loop until EOF.
    
    return 0;
}