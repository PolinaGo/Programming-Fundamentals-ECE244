/* 
 * File:   Parser.cpp
 * Author: Govorkova Polina
 * 
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdio.h>

using namespace std;
#define MAX_NODE_NUMBER 5000 //Defining a constant

//the following is the set of complementary error output functions in order of importance 
void error1() {
	cout << "Error: invalid command" << endl;
}

void error2() {
	cout << "Error: invalid argument" << endl;
}
	
void error3() {
	cout << "Error: negative resistance" << endl;
}

void error4(int& number) {
    	std::cout.precision(2);
	cout << "Error: node " << number << " is out of permitted range 0-5000" << endl;
}

void error5() {
	cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
}

void error6(int& number) {
        std::cout.precision(2);
	cout << "Error: both terminals of resistor connect to node " << number << endl;
}

void error7() {
	cout << "Error: too many arguments" << endl;
}

void error8() {
	cout << "Error: too few arguments" << endl;
}

//main function
int main() {
    
    string line, command; //input line, command for the function
    
    //defining arguments
    string name; //resistor name
    int n1, n2; //nodes
    double resistance; //resistance value
    
    getline (cin, line); //getting the line from the input
    cout << "> "; //output requirement
    
    while ( !cin.eof () ) { //while there are more lines to read to do the following - processing input line by line
        
        stringstream lineStream (line), second (line); //making string stream from the line, making a duplicate 

        lineStream >> command; //reading the first word to be command
        //the following are the potential cases of command input
        if (command == "insertR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) error8();
            else {
                lineStream >> name; //reading resistor name to insert and checking it for the errors
                if (lineStream.fail()) error2();
                else if (name == "all") error5();
                else {
                    lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                    if (lineStream.peek()==EOF) error8();
                    else {
                        lineStream >> resistance; //reading resistance and checking it for the errors
                        if (lineStream.fail()) error2();
                        else if ((lineStream.peek()!=' ')&&(lineStream.peek()!=EOF)) error2();
                        else if (resistance < 0) error3();
                        else {
                            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                            if (lineStream.peek()==EOF) error8();
                            else {
                                lineStream >> n1; //reading nodeid1 and checking for the errors
                                if (lineStream.fail()) error2();
                                else if ((lineStream.peek()!=' ')&&(lineStream.peek()!=EOF)) error2();
                                else if ((n1 < 0) || (n1 > MAX_NODE_NUMBER)) error4(n1);
                                else {
                                    lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                                    if (lineStream.peek()==EOF) error8();
                                    else {
                                    lineStream >> n2;     //reading nodeid2 and checking for the errors   
                                    if (lineStream.fail()) error2();
                                    else if ((lineStream.peek()!=' ')&&(lineStream.peek()!= EOF)) error2();
                                    else if ((n2 < 0) || (n2 > MAX_NODE_NUMBER)) error4(n2);
                                    else if (n1 == n2) error6(n1);
                                    else if (lineStream.peek()!= EOF) 
                                    {
                                        lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
                                        if (lineStream.peek()!=EOF) error7();
                                        else cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance << " Ohms " << n1 << " -> " << n2 << endl;
                                    }
                                    else cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance << " Ohms " << n1 << " -> " << n2 << endl;
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
            if (lineStream.peek()==EOF) error8();
            else {
                lineStream >> name;//reading resistor name to modify and checking for errors
                if (lineStream.fail()) error2();
                else if (name == "all") error5();
                else if (lineStream.eof()) error8();
                else {
                    lineStream >> resistance;//reading resistance to modify and checking for errors
                    if (lineStream.fail()) error2();
                    else if ((lineStream.peek()!=' ')&&(lineStream.peek()!= EOF)) error2();
                    else if (resistance < 0) error3();
                    else {
                        lineStream >> ws;
                        if (lineStream.peek()!= EOF) error7();
                        else cout << "Modified: resistor " << name << " to " << fixed << setprecision(2) << resistance << " Ohms" << endl;
                    }
                }
            }
            lineStream.clear();
        }
        else if (command == "deleteR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) error8();
            else {
                lineStream >> name;//reading resistor name and checking for errors
                lineStream >> ws;
                if (lineStream.fail()) error2();
                else if (lineStream.peek()!=EOF) error7();
                else if (name == "all") cout << "Deleted: all resistors" << endl;// ALL case
                else cout << "Deleted: resistor " << name << endl;
            }
            lineStream.clear();
        }
        else if (command == "printR") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) error8();
            else {
                lineStream >> name;//reading resistor name and checking for errors
                lineStream >> ws;
                if (lineStream.peek()!=EOF) error7();
                else if (name == "all") cout << "Print: all resistors" << endl; //ALL case
                else cout << "Print: resistor " << name << endl;
            }
        lineStream.clear();
        }
        else if (command == "printNode") {
            lineStream >> ws;//erasing white spaces and then checking for existence of other elements in the line 
            if (lineStream.peek()==EOF) error8();
            else {
                lineStream >> n1;//reading nodeID and checking for errors
                if (lineStream.fail()) //check for ALL case
                {
                    second >> command >> name; //reading from the complementary to lineStream line that contains string extention after "printNode"
                    second >> ws;
                    if ((name == "all")&&((second.peek()==EOF)))  cout << "Print: all nodes" << endl; //ALL case
                    else if (name != "all") error2();
                    else error7();
                }
                else if ((lineStream.peek()!=' ')&&(lineStream.peek()!= EOF)) error2();
                else {
                    lineStream >> ws;
                    if ((n1 < 0) || (n1) > MAX_NODE_NUMBER) error4(n1);
                    else if (lineStream.peek()!=EOF) error7();
                    else cout << "Print: node " << n1 << endl;
                }
            }
        lineStream.clear();
        }
        else error1();
        cout << "> "; //format requiremrnt
        getline (cin, line); //reading the new line
    } // End input loop until EOF.
    cout << endl;
    return 0;
}
