
/* 
 * File:   ResistorList.cpp
 * Author: Govorkova Polina
 * 
 * Created on November 8, 2017, 5:41 PM
 */

#include "ResistorList.h"

//default constructor
ResistorList::ResistorList() {
    head = NULL;
    count = 0;
}

//default destructor
ResistorList::~ResistorList() {
}

//returns amount of resistors connected to node
int ResistorList::getCount() {
    return count;
}

//adds resistor to the given node
void ResistorList :: addResistor(string name,double resistance, int n1, int n2) {
    Resistor * plus = new Resistor (name, resistance, n1, n2);
    Resistor * temp = this->head;
    if (temp == NULL) {
        head = plus;
        plus->next = NULL;
    }
    else {
    while (temp->next!=NULL) {
    temp = temp->next;
    }
    temp->next = plus;
    plus->next = NULL;
    }
}

//checks existence of the resistor in the resistor list for the given node
bool ResistorList :: resSearch (string name) {
    bool a = false;
    Resistor * temp = this->head;
    while (temp!=NULL) {
    if (temp->name == name) a = true;
    temp = temp->next;
    }
    return a;
}

//prints resistor list
void ResistorList :: printResistorList() {
    Resistor * temp = this->head;
    while (temp!=NULL) {
        cout << "  ";
        temp->print();
        temp = temp->next;
    }
}

//prints resistor by name
void ResistorList :: printResistor(string name) {
    Resistor * temp = this->head;
    while (temp!=NULL) {
        if (temp->name == name) temp->print();
        temp = temp->next;
    }
}

//modifies resistance of given resistor, returns its old value
double ResistorList :: modify (string name, double resistance) {
    double old;
    Resistor * temp = this->head;
    while (temp!=NULL) {
    if (temp->name == name) { old = temp->resistance; temp->resistance = resistance;}
    temp = temp->next;
    }
    return old;
}

//deletes resistor
void ResistorList :: deleteR (string name) {
    Resistor * temp = this->head;
    Resistor * tempCopy = this->head;
    while (temp->name != name) {
                temp = temp->next;
    }
    if (temp == head) {
        head = temp->next;
        delete temp;
        count = count -1;
    }
    else {
        while (tempCopy->next!= temp) {
            tempCopy = tempCopy->next;
        }
        tempCopy->next = temp->next;
        delete temp;
        count = count -1;
    }
    tempCopy = temp;
}

//deletes the whole list
void ResistorList :: deleteRall () {
    Resistor * temp = this->head;
    while (head != NULL) {
        head = head->next;
        delete temp;
        temp = head;
    }
count = 0;
}

//assistant to solve function, calculates sum of 1/Ri for every ith resistor in the list
double ResistorList :: term2() {
    Resistor * temp = this->head;
    double sum = 0;
    while (temp!= NULL) {
        sum = sum + (1/temp->resistance);
        temp = temp->next;
    }
    return sum;
}