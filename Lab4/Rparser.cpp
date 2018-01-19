
/* 
 * File:   Rparser.cpp
 * Author: Govorkova Polina
 * 
 * Created on November 8, 2017, 5:41 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

#include "Rparser.h"
#include "NodeList.h"
#include "Resistor.h"

using namespace std;

using namespace std;

//additional basic functions responsible for error message print
void error1_noVoltageSet() {
        cout << "Error: no nodes have their voltage set" << endl;
}

void error2_resNotFound(string name) {
	cout << "Error: resistor " << name << " not found" << endl;
}

void error3(string name) {
	cout << "Error: resistor " << name << " already exists" << endl;
}

void error4(int n1) {
	cout << "Error: node " << n1 << " not found" << endl;
}

//main function of the program, coordinates the rest of the functions
int Rparser (void) {
    
    //declaration of the network
    NodeList * list = new NodeList();
    
     //variables for input information   
    string line, command, second;
    string name;
    int n1, n2;
    double resistance;
    double voltage;
    
    //complementary variable for error check
    bool existence = false;
    
    cout << "> "; //output requirement   
    getline (cin, line); //getting the line from the input

    
    while ( !cin.eof () ) { //while there are more lines to read to do the following
        stringstream lineStream (line), second (line); //make string stream from the line

        lineStream >> command; //read the first word to be command

        if (command == "insertR") {
            lineStream >> name >> resistance >> n1 >> n2;
            existence = list->resSearch(name);
            if (existence) error3(name);
            else {
                //all the requirements are met. Adding resistor
                cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance << " Ohms " << n1 << " -> " << n2 << endl;
                list->addResistor(name, resistance, n1, n2);
            }
        }
        
        else if (command == "modifyR") {
            lineStream >> name >> resistance;
            existence  = list->resSearch(name);
            if (!existence) error2_resNotFound(name);
            else {
                //all the requirements are met. Modifying resistor
                list->modify(name, resistance);
            }
        }
        
        else if (command == "deleteR") {
            if (lineStream.peek()==EOF) {}
            else {
                lineStream >> name;//reading resistor name and checking for errors
                existence = list->resSearch(name);
                if (name == "all") { //ALL case
                    //all the requirements are met. Deleting all resistors
                    cout << "Deleted: all resistors" << endl;// ALL case  
                    list->deleteRall();       
                    list->unsetAndZero(); //setting all the nodes to initial condition : unset, v = 0
                }
                else if (!existence) error2_resNotFound(name); //one resistor case
                else  //all the requirements are met. Deleting resistor
                {
                    cout << "Deleted: resistor " << name << endl;
                    list->deleteResistor(name);
                }
            }
        }
        else if (command == "printR") {
                lineStream >> name;//reading resistor name and checking for errors
                existence = list->resSearch(name);
                if (!existence) error2_resNotFound(name);
                else { //all the requirements are met. Printing resistor
                cout << "Print: " << endl;
                list->printR(name);
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
                    if (name == "all")
                    {
                        //all the requirements are met. Printing all nodes
                        cout << "Print: " << endl;
                        list->printNodes();
                    } //ALL case
                }
                else {
                    existence = list->findNode(n1);
                    if (!existence) error4(n1);
                    //all the requirements are met. Printing node
                    else {
                    cout << "Print: " << endl;
                    list->printNode(n1);
                    }
                }
            }
        }
        else if (command == "setV") {
            lineStream >> n1 >> voltage;
            existence = list->findNode(n1);
            if (!existence) error4(n1);
            else { //all the requirements are met. Setting node voltage
                cout << "Set: node " << n1 << " to " << voltage << " Volts" << endl;
                list->setV(n1, voltage);
            }
        }
        else if (command == "unsetV") {
            lineStream >> n1;
            existence = list->findNode(n1);
            if (!existence) error4(n1);
            else { //all the requirements are met. Unsetting node
                list->unsetV(n1);
                cout << "Unset: the solver will determine the voltage of node " << n1 << endl;
            }
        }
        else if (command == "solve"){
           existence = list->areAllSet();
           if (!existence) error1_noVoltageSet();
           else { //all the requirements are met. Solving the network
               cout << "Solve:" << endl;
               list->solve();
           }
        }
//        else list->printNodeIDS();
        cout << "> "; //format requirement
        existence = false;
        getline (cin, line);
    } // End input loop until EOF.
    
    
    //destruction actions preventing memory leaks
    list->deleteList();
    delete list;
    
    return 0; // successful end if the program
}