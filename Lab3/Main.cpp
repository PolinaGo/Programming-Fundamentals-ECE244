/* 
 * File:   Main.cpp
 * Author: Govorkova Polina
 * 
 * Created on October 17, 2017, 12:30 PM
 */

#include "Rparser.h"

using namespace std;

//declaration of storage arrays of resistors and nodes
Node * NodeArray;
Resistor **ResistorArray;

int main() {
    
    Rparser(); //runs parser function
    return 0; // returns 0 if program is done correctly
}